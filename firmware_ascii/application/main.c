/***********************************************************************************************************************
File: main.c                                                                

Description:
Container for the EiE firmware.  
***********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32SystemFlags = 0;                     /* Global system flags */
volatile u32 G_u32ApplicationFlags = 0;                /* Global applications flags: set when application is successfully initialized */

/*--------------------------------------------------------------------------------------------------------------------*/
/* External global variables defined in other files (must indicate which file they are defined in) */
extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "Main_" and be declared as static.
***********************************************************************************************************************/
typedef struct
{
  u8 u8ServerNumber;                    /* Unique token for this item */
  DrinkType asServingTray[MAX_DRINKS];  /* Data payload array */
  void* psNextServer;                   /* Pointer to next ServerType*/
} ServerType;

/***********************************************************************************************************************
Main Program
Main has two sections:

1. Initialization which is run once on power-up or reset.  All drivers and applications are setup here without timing
contraints but must complete execution regardless of success or failure of starting the application. 

2. Super loop which runs infinitely giving processor time to each application.  The total loop time should not exceed
1ms of execution time counting all application execution.  SystemSleep() will execute to complete the remaining time in
the 1ms period.
***********************************************************************************************************************/





u16 u16NumBit,u16NumBit1;
u16 u16NumBit=0x1234;
u16 u16NumBit1=0x1234;
void set_bit(void)
{
u16NumBit|=_BIT;
} 
void clear_bit(void)
{
 u16NumBit1&=~(_BIT1);
}




void main(void)
{
  u8 u8MyData=0;
  G_u32SystemFlags |= _SYSTEM_INITIALIZING;
	clear_bit();
	set_bit();




	u8 u8Test=0xA5;
	u8*pu8Example;
	u32 u32Test=0x0000ffff;
	u32*pu32Example;
	pu8Example=&u8Test;
	pu32Example=&u32Test;
	*pu8Example+=1;
	(*pu32Example)++;
	pu8Example++;
	*pu32Example++; 



	u8 u8CurrentServer;
	ServerType sServer1;
	ServerType* psServerParser;

	psServerParser = &sServer1;
	sServer1.u8ServerNumber = 18;
	u8CurrentServer = psServerParser->u8ServerNumber;




  /* Low level initial;ization */
  WatchDogSetup(); /* During development, does not reset processor if timeout */
  GpioSetup();
  ClockSetup();
  InterruptSetup();
  SysTickSetup();

  /* Driver initialization */
  MessagingInitialize();
  UartInitialize();
  DebugInitialize();

  /* Debug messages through DebugPrintf() are available from here */

  ButtonInitialize();
  TimerInitialize();  
  SspInitialize();
  TWIInitialize();
  Adc12Initialize();
  
  LcdInitialize();
  LedInitialize();
  AntInitialize();
  AntApiInitialize();
  SdCardInitialize();

  /* Application initialization */

  UserApp1Initialize();
  //UserApp2Initialize();
  //UserApp3Initialize();

  
  /* Exit initialization */
  SystemStatusReport();
  G_u32SystemFlags &= ~_SYSTEM_INITIALIZING;
    
  /* Super loop */  
  while(1)
  {
    WATCHDOG_BONE();
    u8MyData++;
    
    /* Drivers */
    LedUpdate();
    ButtonRunActiveState();
    UartRunActiveState();
    TimerRunActiveState(); 
    SspRunActiveState();
    TWIRunActiveState();
    Adc12RunActiveState();
    MessagingRunActiveState();
    DebugRunActiveState();
    LcdRunActiveState();
    AntRunActiveState();
    AntApiRunActiveState();
    SdCardRunActiveState();

    /* Applications */
    UserApp1RunActiveState();
    //UserApp2RunActiveState();
    //UserApp3RunActiveState();
    
    /* System sleep*/
   // HEARTBEAT_OFF();
    SystemSleep();
   // HEARTBEAT_ON();
    
  } /* end while(1) main super loop */
  
} /* end main() */


/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File */
/*--------------------------------------------------------------------------------------------------------------------*/
