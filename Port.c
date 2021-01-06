 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.c
 *
 * Description: Source file for TM4C123GH6PM Microcontroller - Port Driver.
 *
 * Author: Ahmed Badra
 ******************************************************************************/

#include "Port.h"
#include "Port_Regs.h"

#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 || (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 || (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Det.h does not match the expected version"
#endif

#endif
   
//STATIC const Dio_ConfigChannel * Dio_PortChannels = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;

static volatile uint32 * getPortBasePtr(Port_PinType PortPinId)
{
  /* calculating the PortId from the Port-Pin index */
  uint8 PortId = PortPinId / NUM_OF_PORT_SINGLE_PORT;
  
  /* according to PortId, the function will return the appropriate Base address */
  switch(PortId)
    {
        case  0: return (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
	case  1: return (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
	case  2: return (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
	case  3: return (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
        case  4: return (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
        case  5: return (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
    }
  
  /* if there's no such Port-Pin index in the MCU */
  return NULL_PTR;
}

static uint8 getPortId(Port_PinType PortPinId)
{
  return PortPinId / NUM_OF_PORT_SINGLE_PORT;
}

static uint8 getPinId(Port_PinType PortPinId)
{
  return PortPinId % NUM_OF_PORT_SINGLE_PORT;
}

/************************************************************************************
* Service Name: Port_Init
* Service ID[hex]: 0x00
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): ConfigPtr - Pointer to configuration set.
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Initializes the Port Driver module.
************************************************************************************/
void Port_Init( const Port_ConfigType* ConfigPtr )
{
  #if (DIO_DEV_ERROR_DETECT == STD_ON)

  /* check if the input configuration pointer is not a NULL_PTR */
  if (NULL_PTR == ConfigPtr)
  {
          Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
               PORT_E_PARAM_CONFIG);
  }
  else
  {
    /* Do Nothing */
  }

  #endif
  Port_Status = PORT_INITIALIZED;
  uint8 Port_Pin_Index = 0;
  
  while(Port_Pin_Index < PORT_ALL_PINS_NUMBER)
  {
    /* if the configuration ptr is Null, head On to next Port-Pin Index */
    if(Port_pinConfigurationSet.Pins[Port_Pin_Index] == NULL_PTR)
    {
      /* Do Nothing.... */
    }
    /* if the configuration ptr is set to specific config, Configure the Pin */
    else
    {
      /* get the pin number (PinId) and the Port number (PortId) */
      uint8 PinId = getPinId(Port_Pin_Index);
      uint8 PortId = getPortId(Port_Pin_Index);
      volatile uint32 delay = 0;
      
      /* get the configuration struct for this specific Port-Pin */
      Port_ConfigPin PinConfig = *Port_pinConfigurationSet.Pins[Port_Pin_Index];
      
      /* get the Port registed of the selected Pin */
      volatile uint32 * PortGpio_Ptr = getPortBasePtr(Port_Pin_Index);
      
      if(PortGpio_Ptr == NULL_PTR)
      {
        /* report error here (NOT AUTOSAR STANDARD) */
      }
      else
      {
        /* Enable clock for PORT and allow time for clock to start*/
        SYSCTL_REGCGC2_REG |= (1<<PortId);
        delay = SYSCTL_REGCGC2_REG;
    
        if( ((PortId == 3) && (PinId == 7)) || ((PortId == 5) && (PinId == 0)) ) /* PD7 or PF0 */
        {
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_LOCK_REG_OFFSET) = 0x4C4F434B;                     /* Unlock the GPIOCR register */   
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_COMMIT_REG_OFFSET) , PinId);  /* Set the corresponding bit in GPIOCR register to allow changes on this pin */
        }
        else
        {
            /* Do Nothing ... No need to unlock the commit register for this pin */
        }
        
        if(PinConfig.mode == PORT_DIO_MODE)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);      /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);             /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));     /* Clear the PMCx bits for this pin */
            
            if(PinConfig.direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
                
                if(PinConfig.initial_value == STD_HIGH)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PinId);          /* Set the corresponding bit in the GPIODATA register to provide initial value 1 */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DATA_REG_OFFSET) , PinId);        /* Clear the corresponding bit in the GPIODATA register to provide initial value 0 */
                }
            }
            else if(PinConfig.direction == PORT_PIN_IN)
            {
                CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);             /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */
                
                if(PinConfig.resistor == PULL_UP)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId);       /* Set the corresponding bit in the GPIOPUR register to enable the internal pull up pin */
                }
                else if(PinConfig.resistor == PULL_DOWN)
                {
                    SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId);     /* Set the corresponding bit in the GPIOPDR register to enable the internal pull down pin */
                }
                else
                {
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_UP_REG_OFFSET) , PinId);     /* Clear the corresponding bit in the GPIOPUR register to disable the internal pull up pin */
                    CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_PULL_DOWN_REG_OFFSET) , PinId);   /* Clear the corresponding bit in the GPIOPDR register to disable the internal pull down pin */
                }
            }
            else
            {
                /* Do Nothing */
            }
            
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);        /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */

        }
        else if(PinConfig.mode == PORT_ANALOG_MODE)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);    /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
            
            if(PinConfig.direction == PORT_PIN_OUT)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */
            }
            else if(PinConfig.direction == PORT_PIN_IN)
            {
                SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* clear the corresponding bit in the GPIODIR register to configure it as input pin */              
            }
            
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);     /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
            
        }
        else if(PinConfig.mode > PORT_DIO_MODE && PinConfig.mode < PORT_ANALOG_MODE)
        {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);          /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);                   /* enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));         /* Clear the PMCx bits for this pin */
            *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PinConfig.mode << (PinId * 4));      /* Set the PMCx bits for this pin to the selected Alternate function in the configurations */
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);             /* Set the corresponding bit in the GPIODEN register to enable digital functionality on this pin */
            
        }
      }
    }
    Port_Pin_Index++;
  }
}

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/************************************************************************************
* Service Name: Port_SetPinDirection
* Service ID[hex]: 0x01
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number,
*                  Direction - Port Pin Direction
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin direction
************************************************************************************/
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction )
{
  boolean error = FALSE;
  
  /* get the pin number (PinId) and the Port number (PortId) */
  uint8 PinId = getPinId(Pin);
  uint8 PortId = getPortId(Pin);

  /* get the configuration struct for this specific Port-Pin */
  Port_ConfigPin PinConfig = *Port_pinConfigurationSet.Pins[Pin];
  
  /* get the Port registed of the selected Pin */
  volatile uint32 * PortGpio_Ptr = getPortBasePtr(Pin);
  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if the Port driver initialized or Not */
  if(Port_Status != PORT_INITIALIZED)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* No action Required */
  }
  
  /* check if the pin direction is changeable */
  if(PinConfig.direction_change == STD_OFF)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE);
    error = TRUE;    
  }
  else
  {
    /* No action Required */
  }
  
  /* check that this pin is available to be configured, or even EXIST! */
  if(Port_pinConfigurationSet.Pins[Pin] == NULL_PTR)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN);
    error = TRUE;   
  }
  else
  {
    /* No action Required */
  }
  
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
  
  if(error == FALSE)
  {
    if(Direction == PORT_PIN_IN)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

    }
    else if(Direction == PORT_PIN_OUT)
    {
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

    }
  }
}
#endif

/************************************************************************************
* Service Name: Port_RefreshPortDirection
* Service ID[hex]: 0x02
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Refreshes port direction.
************************************************************************************/
void Port_RefreshPortDirection( void )
{
  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if the Port driver initialized or Not */
  if(Port_Status != PORT_INITIALIZED)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT);
  }
  else
 
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
  {
    for(Port_PinType Pin = 0; Pin < PORT_ALL_PINS_NUMBER; Pin++)
    {
      /* if the configuration ptr is Null, head On to next Port-Pin Index */
      if(Port_pinConfigurationSet.Pins[Pin] == NULL_PTR)
      {
        /* Do Nothing.... */
      }
      /* if the configuration ptr is set to specific config, refresh the Pin direction */
      else
      {
        /* get the pin number (PinId) and the Port number (PortId) */
        uint8 PinId = getPinId(Pin);
        uint8 PortId = getPortId(Pin);

        /* get the configuration struct for this specific Port-Pin */
        Port_ConfigPin PinConfig = *Port_pinConfigurationSet.Pins[Pin];
        
        /* get the Port registed of the selected Pin */
        volatile uint32 * PortGpio_Ptr = getPortBasePtr(Pin);
            
        if(PinConfig.direction_change == STD_ON)
        {
          if(PinConfig.direction == PORT_PIN_IN)
          {
            CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* Clear the corresponding bit in the GPIODIR register to configure it as input pin */

          }
          else if(PinConfig.direction == PORT_PIN_OUT)
          {
            SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIR_REG_OFFSET) , PinId);                /* Set the corresponding bit in the GPIODIR register to configure it as output pin */

          }    
        }
        else
        {
          /* No Action Required */
        }
      }
    }
  }
}

/************************************************************************************
* Service Name: Port_SetPinMode
* Service ID[hex]: 0x04
* Sync/Async: Synchronous
* Reentrancy: reentrant
* Parameters (in): Pin - Port Pin ID number,
                   Mode - New Port Pin mode to be set on port pin
* Parameters (inout): None
* Parameters (out): None
* Return value: None
* Description: Sets the port pin mode.
************************************************************************************/
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode )
{
  boolean error = FALSE;
  /* get the pin number (PinId) and the Port number (PortId) */
  uint8 PinId = getPinId(Pin);
  uint8 PortId = getPortId(Pin);

  /* get the configuration struct for this specific Port-Pin */
  Port_ConfigPin PinConfig = *Port_pinConfigurationSet.Pins[Pin];
  
  /* get the Port registed of the selected Pin */
  volatile uint32 * PortGpio_Ptr = getPortBasePtr(Pin);
  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* check if the Port driver initialized or Not */
  if(Port_Status != PORT_INITIALIZED)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* No action Required */
  }
  
  /* check if the pin mode is changeable */
  if(PinConfig.mode_change == STD_OFF)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE);
    error = TRUE;    
  }
  else
  {
    /* No action Required */
  }
  
  /* check that this pin is available to be configured, or even EXIST! */
  if(Port_pinConfigurationSet.Pins[Pin] == NULL_PTR)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN);
    error = TRUE;   
  }
  else
  {
    /* No action Required */
  }
  
  /* check if the mode passed is a valid mode */
  if(PinConfig.mode > PORT_ANALOG_MODE)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE);
    error = TRUE;       
  }
  else
  {
    /* No action Required */
  }
  
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */
  
  if(error == FALSE)
  {
    if(Mode == PORT_DIO_MODE)
    {
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);         /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
       CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);                /* Disable Alternative function for this pin by clear the corresponding bit in GPIOAFSEL register */
       *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));        /* Clear the PMCx bits for this pin */
    }
    else if(Mode == PORT_ANALOG_MODE)
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_DIGITAL_ENABLE_REG_OFFSET) , PinId);        /* Clear the corresponding bit in the GPIODEN register to disable digital functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);     /* Set the corresponding bit in the GPIOAMSEL register to enable analog functionality on this pin */
    }
    else
    {
      CLEAR_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ANALOG_MODE_SEL_REG_OFFSET) , PinId);          /* Clear the corresponding bit in the GPIOAMSEL register to disable analog functionality on this pin */
      SET_BIT(*(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_ALT_FUNC_REG_OFFSET) , PinId);                   /* enable Alternative function for this pin by Setting the corresponding bit in GPIOAFSEL register */
      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) &= ~(0x0000000F << (PinId * 4));         /* Clear the PMCx bits for this pin */
      *(volatile uint32 *)((volatile uint8 *)PortGpio_Ptr + PORT_CTL_REG_OFFSET) |= (PinConfig.mode << (PinId * 4));      /* Set the PMCx bits for this pin to the selected Alternate function in the configurations */
    }
  }
}

/************************************************************************************
* Service Name: Port_GetVersionInfo
* Service ID[hex]: 0x03
* Sync/Async: Synchronous
* Reentrancy: Non reentrant
* Parameters (in): None
* Parameters (inout): None
* Parameters (out): versioninfo - Pointer to where to store the version information of this module
* Return value: None
* Description: Returns the version information of this module.
************************************************************************************/
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo )
{
  boolean error = FALSE;
  
#if (PORT_DEV_ERROR_DETECT == STD_ON)
  
  /* Check if input pointer is not Null pointer */
  if(NULL_PTR == versioninfo)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER);
    error = TRUE;
  }
  else
  {
    /* No action Required */
  }
  
  /* check if the Port driver initialized or Not */
  if(Port_Status != PORT_INITIALIZED)
  {
    /* Report to DET  */
    Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT);
    error = TRUE;
  }
  else
  {
    /* No action Required */
  }
  
#endif /* (PORT_DEV_ERROR_DETECT == STD_ON) */

  if(error == FALSE)
  {
        /* Copy the vendor Id */
        versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
        /* Copy the module Id */
        versioninfo->moduleID = (uint16)PORT_MODULE_ID;
        /* Copy Software Major Version */
        versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
  }
}
#endif