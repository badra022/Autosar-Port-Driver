 /******************************************************************************
 *
 * Module: Port
 *
 * File Name: Port_PBcfg.c
 *
 * Description: Post Build Configuration Source file for TM4C123GH6PM Microcontroller - Port Driver
 *
 * Author: Ahmed Badra
 ******************************************************************************/

#include "Port.h"

/*
 * Module Version 1.0.0
 */
#define PORT_PBCFG_SW_MAJOR_VERSION              (1U)
#define PORT_PBCFG_SW_MINOR_VERSION              (0U)
#define PORT_PBCFG_SW_PATCH_VERSION              (0U)

/*
 * AUTOSAR Version 4.0.3
 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION     (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION     (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION     (3U)

/* AUTOSAR Version checking between Port_PBcfg.c and Port.h files */
#if ((PORT_PBCFG_AR_RELEASE_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
 ||  (PORT_PBCFG_AR_RELEASE_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
  #error "The AR version of PBcfg.c does not match the expected version"
#endif

/* Software Version checking between Dio_PBcfg.c and Dio.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of PBcfg.c does not match the expected version"
#endif


/* definitions of Indecies of the Multible Configuration array */
#define CONST_DIO_CONST_INPUT_PULLUP             (1U)
#define DEFAULT                                  (0U)
#define DIO_INPUT_PULLUP                         (0U)
#define CONST_DIO_CONST_INPUT_PULLDOWN           (2U)
#define CONST_DIO_CONST_INPUT                    (3U)
#define DIO_OUTPUT                               (4U)
#define CONST_DIO_CONST_OUTPUT                   (5U)
#define DIO_CONST_OUTPUT                         (6U)
#define CONST_DIO_OUTPUT                         (7U)

/*
 * Selectable Multible Configuration sets definitions
   Config Item Consist of:
                    1. direction
                    2. internal resistor
                    3. initial value
                    4. mode
                    5. direction changeable
                    6. mode changeable
 */
const Port_ConfigPin Port_Configuration[]={
  
  {PORT_PIN_IN, PULL_UP, STD_HIGH, PORT_DIO_MODE, STD_ON, STD_ON}, /* DEFAULT */
  
  {PORT_PIN_IN, PULL_UP, STD_HIGH, PORT_DIO_MODE, STD_OFF, STD_OFF}, /* CONST_DIO_CONST_INPUT_PULLUP */
  
  {PORT_PIN_IN, PULL_DOWN, STD_HIGH, PORT_DIO_MODE, STD_OFF, STD_OFF}, /* CONST_DIO_CONST_INPUT_PULLDOWN */
  
  {PORT_PIN_IN, OFF, STD_HIGH, PORT_DIO_MODE, STD_OFF, STD_OFF}, /* CONST_DIO_CONST_INPUT */
  
  {PORT_PIN_OUT, OFF, STD_LOW, PORT_DIO_MODE, STD_ON, STD_ON}, /* DIO_OUTPUT */
  
  {PORT_PIN_OUT, OFF, STD_LOW, PORT_DIO_MODE, STD_OFF, STD_OFF}, /* CONST_DIO_CONST_OUTPUT */
  
  {PORT_PIN_OUT, OFF, STD_LOW, PORT_DIO_MODE, STD_ON, STD_OFF}, /* DIO_CONST_OUTPUT */
  
  {PORT_PIN_OUT, OFF, STD_LOW, PORT_DIO_MODE, STD_OFF, STD_ON} /* CONST_DIO_OUTPUT */
  
};

  
/*
 * PB structure used with Dio_Init API,
 * Contains pointer to some Configuration for each Port-Pin Index in the MCU 
 */
const Port_ConfigType Port_pinConfigurationSet = {

  &Port_Configuration[DEFAULT],                 /* PORT_PA0 */
  &Port_Configuration[DEFAULT],                 /* PORT_PA1 */
  &Port_Configuration[DEFAULT],                 /* PORT_PA2 */
  &Port_Configuration[DEFAULT],                 /* PORT_PA3 */
  &Port_Configuration[DEFAULT],                 /* PORT_PA4 */
  &Port_Configuration[DEFAULT],                 /* PORT_PA5 */
  &Port_Configuration[DEFAULT],                 /* PORT_PA6 */
  &Port_Configuration[DEFAULT],                 /* PORT_PA7 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB0 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB1 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB2 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB3 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB4 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB5 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB6 */
  &Port_Configuration[DEFAULT],                 /* PORT_PB7 */
  NULL_PTR,                                     /* PORT_PC0 */
  NULL_PTR,                                     /* PORT_PC1 */
  NULL_PTR,                                     /* PORT_PC2 */
  NULL_PTR,                                     /* PORT_PC3 */
  &Port_Configuration[DEFAULT],                 /* PORT_PC4 */
  &Port_Configuration[DEFAULT],                 /* PORT_PC5 */
  &Port_Configuration[DEFAULT],                 /* PORT_PC6 */
  &Port_Configuration[DEFAULT],                 /* PORT_PC7 */
  &Port_Configuration[DEFAULT],                 /* PORT_PD0 */
  &Port_Configuration[DEFAULT],                 /* PORT_PD1 */
  &Port_Configuration[DEFAULT],                 /* PORT_PD2 */
  &Port_Configuration[DEFAULT],                 /* PORT_PD3 */
  &Port_Configuration[DEFAULT],                 /* PORT_PD4 */
  &Port_Configuration[DEFAULT],                 /* PORT_PD5 */
  &Port_Configuration[DEFAULT],                 /* PORT_PD6 */
  NULL_PTR,                                     /* PORT_PD7 */
  &Port_Configuration[DEFAULT],                 /* PORT_PE0 */
  &Port_Configuration[DEFAULT],                 /* PORT_PE1 */
  &Port_Configuration[DEFAULT],                 /* PORT_PE2 */
  &Port_Configuration[DEFAULT],                 /* PORT_PE3 */
  &Port_Configuration[DEFAULT],                 /* PORT_PE4 */
  &Port_Configuration[DEFAULT],                 /* PORT_PE5 */
  NULL_PTR,                                     /* PORT_PE6 */  
  NULL_PTR,                                     /* PORT_PE7 */  
  NULL_PTR,                                     /* PORT_PF0 */
  &Port_Configuration[CONST_DIO_CONST_OUTPUT],  /* PORT_PF1 */
  &Port_Configuration[DEFAULT],                 /* PORT_PF2 */
  &Port_Configuration[DEFAULT],                 /* PORT_PF3 */
  &Port_Configuration[CONST_DIO_CONST_INPUT_PULLUP],  /* PORT_PF4 */
  NULL_PTR,                                     /* PORT_PF5 */
  NULL_PTR,                                     /* PORT_PF6 */
  NULL_PTR,                                     /* PORT_PF7 */
  
};