 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port.h
 *
 * Description: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ahmed Badra
 ******************************************************************************/

#ifndef PORT_H
#define PORT_H

/* Id for the company in the AUTOSAR
 * for example Ahmed Badra's ID = 1000 :) */
#define PORT_VENDOR_ID    (1000U)

/* port Module Id */
#define PORT_MODULE_ID    (124U)

/* port Instance Id */
#define PORT_INSTANCE_ID  (0U)

/*
 * Module Version 1.0.0
 */
#define PORT_SW_MAJOR_VERSION           (1U)
#define PORT_SW_MINOR_VERSION           (0U)
#define PORT_SW_PATCH_VERSION           (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_AR_RELEASE_MAJOR_VERSION   (4U)
#define PORT_AR_RELEASE_MINOR_VERSION   (0U)
#define PORT_AR_RELEASE_PATCH_VERSION   (3U)

/*
 * Macros for Port Status
 */
#define PORT_INITIALIZED                (1U)
#define PORT_NOT_INITIALIZED            (0U)

/* Number of Pins in the Single Port (MCU Specific) */
#define NUM_OF_PORT_SINGLE_PORT         (8U)

/*
 * macros for pin different Modes,
 * assigned to mode of type Port_PinModeType
 */
#define PORT_DIO_MODE                   (0U)
#define PORT_ALTERNATE_FUNCTION_01_MODE (1U)
#define PORT_ALTERNATE_FUNCTION_02_MODE (2U)
#define PORT_ALTERNATE_FUNCTION_03_MODE (3U)
#define PORT_ALTERNATE_FUNCTION_04_MODE (4U)
#define PORT_ALTERNATE_FUNCTION_05_MODE (5U)
#define PORT_ALTERNATE_FUNCTION_06_MODE (6U)
#define PORT_ALTERNATE_FUNCTION_07_MODE (7U)
#define PORT_ALTERNATE_FUNCTION_08_MODE (8U)
#define PORT_ALTERNATE_FUNCTION_09_MODE (9U)
#define PORT_ALTERNATE_FUNCTION_10_MODE (10U)
#define PORT_ALTERNATE_FUNCTION_11_MODE (11U)
#define PORT_ALTERNATE_FUNCTION_12_MODE (12U)
#define PORT_ALTERNATE_FUNCTION_13_MODE (13U)
#define PORT_ALTERNATE_FUNCTION_14_MODE (14U)
#define PORT_ANALOG_MODE                (15U)

/*
 * symbolic names of each Port-Pin in the Microcontroller (MCU SPECIFIC)
 * , must be as symbolic names provided by the configuration tool,
 * this Project doesn't have a configuration tool so it's up to you
 */
#define PORT_PA0                        (0U)
#define PORT_PA1                        (1U)
#define PORT_PA2                        (2U)
#define PORT_PA3                        (3U)
#define PORT_PA4                        (4U)
#define PORT_PA5                        (5U)
#define PORT_PA6                        (6U)
#define PORT_PA7                        (7U)
#define PORT_PB0                        (8U)
#define PORT_PB1                        (9U)
#define PORT_PB2                        (10U)
#define PORT_PB3                        (11U)
#define PORT_PB4                        (12U)
#define PORT_PB5                        (13U)
#define PORT_PB6                        (14U)
#define PORT_PB7                        (15U)
#define PORT_PC0                        (16U)
#define PORT_PC1                        (17U)
#define PORT_PC2                        (18U)
#define PORT_PC3                        (19U)
#define PORT_PC4                        (20U)
#define PORT_PC5                        (21U)
#define PORT_PC6                        (22U)
#define PORT_PC7                        (23U)
#define PORT_PD0                        (24U)
#define PORT_PD1                        (25U)
#define PORT_PD2                        (26U)
#define PORT_PD3                        (27U)
#define PORT_PD4                        (28U)
#define PORT_PD5                        (29U)
#define PORT_PD6                        (30U)
#define PORT_PD7                        (31U)
#define PORT_PE0                        (32U)
#define PORT_PE1                        (33U)
#define PORT_PE2                        (34U)
#define PORT_PE3                        (35U)
#define PORT_PE4                        (36U)
#define PORT_PE5                        (37U)
#define PORT_PE6                        (38U)
#define PORT_PE7                        (39U)
#define PORT_PF0                        (40U)
#define PORT_PF1                        (41U)
#define PORT_PF2                        (42U)
#define PORT_PF3                        (43U)
#define PORT_PF4                        (44U)
#define PORT_PF5                        (45U)
#define PORT_PF6                        (46U)
#define PORT_PF7                        (47U)

/* Standard AUTOSAR types */
#include "Std_Types.h"

/* AUTOSAR checking between Std Types and Port Modules */
#if ((STD_TYPES_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (STD_TYPES_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Std_Types.h does not match the expected version"
#endif

/* Port Pre-Compile Configuration Header file */
#include "Port_Cfg.h"

/* AUTOSAR Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_CFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of Port_Cfg.h does not match the expected version"
#endif

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif

/* Non AUTOSAR files */
#include "Common_Macros.h"

/******************************************************************************
 *                      API Service Id Macros                                 *
 ******************************************************************************/

/* service ID for PORT init */
#define PORT_INIT_SID                   (uint8)0x00

/* service ID for PORT set pin direction */
#define PORT_SET_PIN_DIRECTION_SID          (uint8)0x01

/* service ID for PORT refresh pin direction */
#define PORT_REFRESH_PORT_DIRECTION_SID      (uint8)0x02

/* service ID for PORT get version info */
#define PORT_GET_VERSION_INFO_SID           (uint8)0x03

/* service ID for PORT set pin mode */
#define PORT_SET_PIN_MODE_SID               (uint8)0x04


/*******************************************************************************
 *                      DET Error Codes                                        *
 *******************************************************************************/
/* DET Code for Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN                  (uint8)0x0A

/* DET Code for Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE     (uint8)0x0B

/* DET Code for API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG               (uint8)0x0C

/* DET Code for API Port_SetPinMode service called with wrong parameter Mode */
#define PORT_E_PARAM_INVALID_MODE         (uint8)0x0D

/* DET Code for API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE          (uint8)0x0E

/* DET Code for API service called without module initialization */
#define PORT_E_UNINIT                     (uint8)0x0F

/* DET Code for APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER              (uint8)0x10

/*******************************************************************************
 *                              Module Data Types                              *
 *******************************************************************************/

/* Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;

/* Possible directions of a port pin */
typedef enum{
  PORT_PIN_IN,          /* Sets port pin as input */
  PORT_PIN_OUT,         /* Sets port pin as output */
}Port_PinDirectionType;

/* Different port pin modes */
typedef uint8 Port_PinModeType;

/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
    OFF,PULL_UP,PULL_DOWN
}Port_InternalResistor;

/* Description: Structure to configure each individual PIN:
 *	1. the direction of pin --> INPUT or OUTPUT
 *      2. the internal resistor --> Disable, Pull up or Pull down
 *      3. the initial value in output case -> high or low
 *      4. pin's Mode -> DIO, Aletrnate Function 01, .... ,Analog
 *      5. pin direction changeability -> ON or OFF
 *      6. pin mode changeability -> ON or OFF
 */
typedef struct
{
    Port_PinDirectionType       direction;              /* PORT_PIN_IN, PORT_PIN_OUT */
    Port_InternalResistor       resistor;               /* OFF,PULL_UP,PULL_DOWN */
    uint8                       initial_value;          /* STD_HIGH, STD_LOW */
    Port_PinModeType            mode;                   /* PORT_DIO_MODE...PORT_ANALOG_MODE */
    uint8                       direction_change;       /* STD_ON, STD_OFF */
    uint8                       mode_change;             /* STD_ON, STD_OFF */
}Port_ConfigPin;

/* structure that is required for initialization API */
typedef struct
{
  /* array of pointers to config struct to optimize memory storage */
  const Port_ConfigPin* Pins[PORT_ALL_PINS_NUMBER];
}Port_ConfigType;


/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/

/* function for PORT initialization API */
void Port_Init( const Port_ConfigType* ConfigPtr );

#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
/* function for setting direction API */
void Port_SetPinDirection( Port_PinType Pin, Port_PinDirectionType Direction );
#endif

/* function for refreshing port direction API */
void Port_RefreshPortDirection( void );

/* function for setting pin mode API */
void Port_SetPinMode( Port_PinType Pin, Port_PinModeType Mode );

/* function for getting version info API */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo( Std_VersionInfoType* versioninfo );
#endif

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/

/* Extern PB structures to be used by Port and other modules */
extern const Port_ConfigType Port_pinConfigurationSet;

#endif /* PORT_H */
