/**********************************************************************************************************************
File: user_app1.c                                                                

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

Description:
This is a user_app1.c file template 

------------------------------------------------------------------------------------------------------------------------
API:

Public functions:


Protected System functions:
void UserApp1Initialize(void)
Runs required initialzation for the task.  Should only be called once in main init section.

void UserApp1RunActiveState(void)
Runs current task state.  Should only be called once in main loop.


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                       /* Global state flags */
LedCommandType aeDemoList[]={{RED,1000,TRUE,LED_PWM_100},
                               {RED,6000,FALSE,LED_PWM_0},
							   {GREEN,3000,TRUE,LED_PWM_100},
							   {GREEN,9000,FALSE,LED_PWM_0},
							    {WHITE,3000,TRUE,LED_PWM_100},
								{CYAN,3000,TRUE,LED_PWM_100}
							   };

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemFlags;                  /* From main.c */
extern volatile u32 G_u32ApplicationFlags;             /* From main.c */

extern volatile u32 G_u32SystemTime1ms;                /* From board-specific source file */
extern volatile u32 G_u32SystemTime1s;                 /* From board-specific source file */

extern u8 G_au8DebugScanfBuffer[];  /* From debug.c */
extern u8 G_u8DebugScanfCharCount;  /* From debug.c */



/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_StateMachine;            /* The state machine function pointer */
//static u32 UserApp1_u32Timeout;                      /* Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Public functions                                                                                                   */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/* Protected functions                                                                                                */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------
Function: UserApp1Initialize

Description:
Initializes the State Machine and its variables.

Requires:
  -

Promises:
  - 
*/
void UserApp1Initialize(void)
{
	LedOff(RED);
	LedOff(GREEN);
	LCDMessage(LINE1_START_ADDR," 0 0  0 0  0 0  0 0 ");
  
  
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    UserApp1_StateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_StateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*----------------------------------------------------------------------------------------------------------------------
Function UserApp1RunActiveState()

Description:
Selects and runs one iteration of the current state in the state machine.
All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
  - State machine function pointer points at current state

Promises:
  - Calls the function to pointed by the state machine function pointer
*/
void UserApp1RunActiveState(void)
{
  UserApp1_StateMachine();

} /* end UserApp1RunActiveState */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Private functions                                                                                                  */
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/

/*-------------------------------------------------------------------------------------------------------------------*/
/* Wait for ??? */

  /* Wait for a message to be queued */
  static void UserApp1SM_Idle(void)
{
 static u32 u32Time=0;
 static u8 u8Index;
 static u8 au8LedAddr[]={1,3,6,8,11,13,16,18};
 u8 u8Counter[4]={'0','0','0','0'};
  
 u32Time++;
 
 //time=0 every ten seconds
 if(u32Time == 10000)
 {
    u32Time=0;
 }
 
 //display time in Line2
 u8Counter[0]=0x30+u32Time/1000;
 u8Counter[1]=0x30+u32Time%1000/100; 
 u8Counter[2]=0x30+u32Time%100/10; 
 u8Counter[3]=0x30+u32Time%10; 

 
 //display once every second
 if(u32Time%100 == 0)
  {
	
 	LCDMessage(LINE2_START_ADDR,u8Counter);
  }
 
 //Led display and LCD display '0'and'1'
  for(u8Index=0;u8Index<6;u8Index++)
 {
	if(u32Time==aeDemoList[u8Index].u32Time)
	{
	  LedPWM(aeDemoList[u8Index].eLed, aeDemoList[u8Index].eCurrentRate);
	  
	  if(aeDemoList[u8Index].bOn==TRUE)
	  {
		LCDMessage(LINE1_START_ADDR+au8LedAddr[aeDemoList[u8Index].eLed],"1");
	  }                                                                                                          
	  else
	  {
		LCDMessage(LINE1_START_ADDR+au8LedAddr[aeDemoList[u8Index].eLed],"0");
	  }
	}	
 }
} /* end UserAppSM_Idle() */

 


	

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)      
{
 
} /* end UserApp1SM_Error() */



/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
