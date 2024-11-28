/*

Adapted from Vince Diesi's source code found at "SAMPLE\SCEE\CD\MOVIE2" inside the developer's CD.

Some changes have been made for Dragon's Lair.

*/


/************************************************************
 *                                                          *
 *                       control.c                          *
 *                                                          *
 *                                                          *
 *               Vince Diesi     13/02/96                   *
 *                                                          *
 *   Copyright (C) 1996 Sony Computer Entertainment Inc.    *
 *                  All Rights Reserved                     *
 *                                                          *
 ***********************************************************/

/* ---------------------------------------------------------------------------
 * - Description:
 * - ------------
 * - Controller functions. Only supports the standard controller. 
 * ---------------------------------------------------------------------------
 */

#include <sys/types.h>
#include <kernel.h>
#include <libsn.h>
#include <libgte.h>
#include <libgpu.h>
#include <libetc.h>

#define CONTROL_C
#include "game.h"
#include "ctrller.h"
#include "options.h"
#include "control.h"
#include "font.h"


/* ---------------------------------------------------------------------------
 * - CONSTANTS 
 * ---------------------------------------------------------------------------
 */

// Define for timing and testing functions.
// #define TESTING


// Controllers connected.
#define NO_PADS			0
#define PAD_ONE			1
#define PAD_TWO			2
#define BOTH_PADS		3

/* ---------------------------------------------------------------------------
 * - GLOBAL DEFINITIONS 
 * ---------------------------------------------------------------------------
 */

static volatile short connected = 0;			// No. controllers connected.
static volatile short currController = 0;		// Current active controller.

static volatile ControllerPacket buffers[2];


/* ---------------------------------------------------------------------------
 * - FUNCTION DEFINITIONS
 * ---------------------------------------------------------------------------
 */

void Shake_DualShock(void);

void Init_DS_Motors(void)
{

Big_Motor.Strength = 0x00;
Big_Motor.Duration = 0;

Small_Motor.Strength = 0x00;
Small_Motor.Duration = 0;


}

/* ------------------------------------------------------------------------ */

void Init_DualShock(void)
{

MotorStatus[0] = MotorStatus[1] = 0x00;
PadSetAct(0, &MotorStatus[0], DSBufferLength);
DualShock_Ready = PadSetActAlign(0x00, DS_Align);

Init_DS_Motors();

}

/* ------------------------------------------------------------------------ */

 
void InitControllers(void) {


/* - Type:	PUBLIC 
 * -
 * - Usage: Init controllers. 
 */
/*
	InitPAD((char *) &buffers[0], MAX_CONTROLLER_BYTES, (char *) &buffers[1], MAX_CONTROLLER_BYTES);
	StartPAD();
	ChangeClearPAD(0);
	VSync(0);
*/

	PadInitDirect(&buffers[0], &buffers[1]);
	PadStartCom();
	ChangeClearPAD(0);
//	VSync(FRAMES_PER_SECOND); // Delay before turning on analog mode.
	VSync(60);

	Last_Pad_ID = GetType(&buffers[0]);

// Attempt turning on analog mode if pad is ready.
	if (PadGetState(0x00) == 6)
		{
		PadSetMainMode(0x00, 1, 0);
		}

	CheckControllers();

}

/* ------------------------------------------------------------------------ */

void StopControllers(void) {


/* - Type:	PUBLIC 
 * -
 * - Usage: Stop controllers. 
 */


//	StopPAD();

	MotorStatus[0] = MotorStatus[1] = 0;
	VSync(2);
	PadStopCom();

	connected = 0;
	currController = 0;
	DualShock_Ready = 0;
}

/* ------------------------------------------------------------------------ */

void CheckControllers(void) {


/* - Type:	PUBLIC 
 * -
 * - Usage:	Check number of controllers connected (stored in connected).
 * - 		Also selects the active controller (stored in currController). 
 * - 		Should be called in the VSyncCallback() to constantly check the
 * -		controller status.
 */


	connected = 0;


	if (GoodData(&buffers[0]) && ( ( GetType(&buffers[0]) == STD_PAD) || ( GetType(&buffers[0]) == DUAL_SHOCK) ) )
			connected |= PAD_ONE;

	if (GoodData(&buffers[1]) && (GetType(&buffers[1]) == STD_PAD))
			connected |= PAD_TWO;

	
	if (connected == BOTH_PADS || connected == PAD_ONE)
		{
		currController = 0;
		if ( GetType(&buffers[0]) != Last_Pad_ID )
			{
			DualShock_Ready = 0;
			}
		if (PadGetState(0x00) == 6 && DualShock_Ready == 0)
			{
			Init_DualShock();
			}
		}

	else if (connected == PAD_TWO || connected == NO_PADS)
		{
		currController = 1;
		DualShock_Ready = 0;
		}

	Last_Pad_ID = GetType(&buffers[0]);

}

/* ------------------------------------------------------------------------ */

short Pressed(short button) {


/* - Type:	PUBLIC 
 * -
 * - Param:	button = (In) Button to test.
 * -
 * - Ret:	1 if pressed, 0 otherwise.
 * -
 * - Usage:	Test if button has been pressed. 
 */


	return (connected && !(buffers[currController].data.pad & button));
}

/* ------------------------------------------------------------------------ */


// Additional stuff required for Dragon's Lair.


void CheckButtons(void)
{

// Analog Sticks.
if ( GetType(&buffers[0]) == DUAL_SHOCK )
	{
	Left_Stick_X = JoystickLeftX(&buffers[0]) - 127;
	Right_Stick_X = JoystickRightX(&buffers[0]) - 127;
	Left_Stick_Y = JoystickLeftY(&buffers[0]) - 127;
	Right_Stick_Y = JoystickRightY(&buffers[0]) - 127;
	}

//FntPrint(fIdA, "\n%d %d %d %d", Left_Stick_X, Left_Stick_Y, Right_Stick_X, Right_Stick_Y );
//FntFlush(fIdA);


	if ( (Pressed(UP_KEY)) || ( Left_Stick_Y < -Game_Config.Sensitivity || Right_Stick_Y < -Game_Config.Sensitivity ) )
		{
		Pad1.Up++;
		limitRange(Pad1.Up, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Up = IDLE_BUTTON;
		}

	if ( Pressed(DOWN_KEY) || ( Left_Stick_Y > Game_Config.Sensitivity || Right_Stick_Y > Game_Config.Sensitivity ) )
		{
		Pad1.Down++;
		limitRange(Pad1.Down, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Down = IDLE_BUTTON;
		}

	if ( Pressed(LEFT_KEY) || ( Left_Stick_X < -Game_Config.Sensitivity || Right_Stick_X < -Game_Config.Sensitivity ) )
		{
		Pad1.Left++;
		limitRange(Pad1.Left, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Left = IDLE_BUTTON;
		}

	if ( Pressed(RIGHT_KEY) || ( Left_Stick_X > Game_Config.Sensitivity || Right_Stick_X > Game_Config.Sensitivity ) )
		{
		Pad1.Right++;
		limitRange(Pad1.Right, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Right = IDLE_BUTTON;
		}

	if ( Pressed(TRIANGLE_KEY) )
		{
		Pad1.Triangle++;
		limitRange(Pad1.Triangle, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Triangle = IDLE_BUTTON;
		}

	if ( Pressed(X_KEY) )
		{
		Pad1.Cross++;
		limitRange(Pad1.Cross, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Cross = IDLE_BUTTON;
		}

	if ( Pressed(SQUARE_KEY) )
		{
		Pad1.Square++;
		limitRange(Pad1.Square, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Square = IDLE_BUTTON;
		}

	if ( Pressed(CIRCLE_KEY) )
		{
		Pad1.Circle++;
		limitRange(Pad1.Circle, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Circle = IDLE_BUTTON;
		}

	if ( Pressed(SELECT_KEY) )
		{
		Pad1.Select++;
		limitRange(Pad1.Select, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Select = IDLE_BUTTON;
		}

	if ( Pressed(START_KEY) )
		{
		Pad1.Start++;
		limitRange(Pad1.Start, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.Start = IDLE_BUTTON;
		}

	if ( Pressed(L1_KEY) )
		{
		Pad1.L_1++;
		limitRange(Pad1.L_1, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.L_1 = IDLE_BUTTON;
		}

	if ( Pressed(L2_KEY) )
		{
		Pad1.L_2++;
		limitRange(Pad1.L_2, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.L_2 = IDLE_BUTTON;
		}

	if ( Pressed(R1_KEY) )
		{
		Pad1.R_1++;
		limitRange(Pad1.R_1, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.R_1 = IDLE_BUTTON;
		}

	if ( Pressed(R2_KEY) )
		{
		Pad1.R_2++;
		limitRange(Pad1.R_2, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.R_2 = IDLE_BUTTON;
		}

	if ( Pressed(PAD_L3) )
		{
		Pad1.L_3++;
		limitRange(Pad1.L_3, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.L_3 = IDLE_BUTTON;
		}

	if ( Pressed(PAD_R3) )
		{
		Pad1.R_3++;
		limitRange(Pad1.R_3, IDLE_BUTTON, HOLD_BUTTON);
		}
	else
		{
		Pad1.R_3 = IDLE_BUTTON;
		}

// Use Sword variable as a wildcard instead of quering value of each other button.

	if ( Pad1.Triangle == TAP_BUTTON || Pad1.Cross == TAP_BUTTON || Pad1.Square == TAP_BUTTON || Pad1.Circle == TAP_BUTTON || Pad1.L_1 == TAP_BUTTON || Pad1.R_1 == TAP_BUTTON || Pad1.L_2 == TAP_BUTTON || Pad1.R_2 == TAP_BUTTON || Pad1.L_3 == TAP_BUTTON || Pad1.R_3 == TAP_BUTTON )
		{
		Pad1.Sword = TAP_BUTTON;
		}
	else
		{
		Pad1.Sword = IDLE_BUTTON;
		}

// Pause game when no valid pad is connected to port 1.
if ( currController == 1 && Game_Status == 5 && Player1.Pause == NO)
	{
	Pad1.Start = TAP_BUTTON;
	}

Shake_DualShock();
}

/* ------------------------------------------------------------------------ */

// Big motor rumble, max strength.

void DS_Big_Rumble(void)
{

Big_Motor.Strength = 0xff;
Big_Motor.Duration = 10;

}

/* ------------------------------------------------------------------------ */

// Small motor rumble.

void DS_Small_Rumble(void)
{

Small_Motor.Strength = 0x1;
Small_Motor.Duration = 10;

}

/* ------------------------------------------------------------------------ */

// Big motor rumble, med strength.

void DS_Medium_Rumble(void)
{

Big_Motor.Strength = 0x90;
Big_Motor.Duration = 10;

}


/* ------------------------------------------------------------------------ */

// Big motor rumble, low strength.

void DS_Low_Rumble(void)
{

Big_Motor.Strength = 0x70;
Big_Motor.Duration = 10;

}


/* ------------------------------------------------------------------------ */

// Big motor (max) and small motor rumble.

void DS_Both_Rumble(void)
{

DS_Big_Rumble();
DS_Small_Rumble();

}

/* ------------------------------------------------------------------------ */

void Shake_DualShock(void)
{

if (Game_Config.Vibration == 1 && PadGetState(0x00) == 6)
	{
	if (Big_Motor.Duration > 0)
		{
		Big_Motor.Duration--;
		if (Big_Motor.Duration == 0)
			{
			Big_Motor.Strength = 0x00;
			}
		}

	MotorStatus[1] = Big_Motor.Strength;

	if (Small_Motor.Duration > 0)
		{
		Small_Motor.Duration--;
		if (Small_Motor.Duration == 0)
			{
			Small_Motor.Strength = 0x00;
			}
		}

	MotorStatus[0] = Small_Motor.Strength;
	}
}


/* ------------------------------------------------------------------------ */

// Hidden option for testing controllers.

void Pad_Test(void)
{

char Buttons[1];
static short X_Tri=100, Y_Tri=105, X_Squ=185, Y_Squ=105;

//FntPrint(fIdA, "\nPad id: %x", GetType(&buffers[0]) );
FntPrint(fIdA, "\nPad id: %x", buffers[0].dataFormat );
if ( GetType(&buffers[0]) == DUAL_SHOCK )
	{
	sprintf(Buttons, "%c", ' '-14);
	Puts16p(Left_Stick_X + 130, Left_Stick_Y + 110, Buttons, ColorRed);
	sprintf(Buttons, "%c", ' '-2);
	Puts16p(Right_Stick_X + 160, Right_Stick_Y + 110, Buttons, ColorBlue);
	FntPrint(fIdA, ". Analog." );
	}
else if ( GetType(&buffers[0]) == STD_PAD )
	{
	FntPrint(fIdA, ". Digital." );
	}
else
	{
	FntPrint(fIdA, ". Insert valid controller." );
	}
FntPrint(fIdA, "\nStatus: %x", buffers[0].transStatus );
FntPrint(fIdA, "\nData: %x", buffers[0].data.pad );
if ( GetType(&buffers[0]) == DUAL_SHOCK )
	FntPrint(fIdA, " %x %x %x %x", buffers[0].data.joystick.left_x, buffers[0].data.joystick.left_y, buffers[0].data.joystick.right_x, buffers[0].data.joystick.right_y );
FntPrint(fIdA, "\nBytes returned: %x", DataBytesReturned(&buffers[0]) );
//FntPrint(fIdA, "\nData address: %x", ControllerDataAddress(&buffers[0]) );

// Dual shock stuff.

FntPrint(fIdA, "\nPadGetState: %x", PadGetState(0x00) );
if (PadGetState(0x00) == 6)
	{
	FntPrint(fIdA, "\nActuators: %x", PadInfoAct(0x00, -1, 0));
	FntPrint(fIdA, "\nActuator 0: %x, %x, %x, %d, %x", PadInfoAct(0x00, 0, 1), PadInfoAct(0x00, 0, 2), PadInfoAct(0x00, 0, 3), PadInfoAct(0x00, 0, 4), 	PadInfoAct(0x00, 0, 5) );
	FntPrint(fIdA, "\nActuator 1: %x, %x, %x, %d, %x", PadInfoAct(0x00, 1, 1), PadInfoAct(0x00, 1, 2), PadInfoAct(0x00, 1, 3), PadInfoAct(0x00, 1, 4), 	PadInfoAct(0x00, 1, 5) );
	FntPrint(fIdA, "\nMotor 0: %x, Motor 1: %x", MotorStatus[0], MotorStatus[1]);
	}



sprintf(Buttons, "%c", ' '-8);
Puts16p(X_Tri, Y_Tri, Buttons, ColorGreen);

sprintf(Buttons, "%c", ' '-10);
Puts16p(X_Squ, Y_Squ, Buttons, ColorPink);


FntPrint(fIdA, "\n\n\n\n\n\n\n\n	PRESS SELECT + START TO EXIT." );

FntPrint(fIdA, "\n\n\n\n	   archive.org/details/@qbl" );
FntPrint(fIdA, "\n	github.com/netyarouze/spaceace" );

FntFlush(fIdA);

if ( PadKeyIsPressed(&buffers[0], UP_KEY) && Y_Tri > 0)
	{
	Y_Tri--;
	MotorStatus[0]++;
	}

if ( PadKeyIsPressed(&buffers[0], DOWN_KEY) && Y_Tri < 240)
	{
	Y_Tri++;
	MotorStatus[0]--;
	}

if ( PadKeyIsPressed(&buffers[0], LEFT_KEY) && Y_Tri > 0)
	{
	X_Tri--;
	MotorStatus[1]--;
	}

if ( PadKeyIsPressed(&buffers[0], RIGHT_KEY) && Y_Tri < 320)
	{
	X_Tri++;
	MotorStatus[1]++;
	}

if ( PadKeyIsPressed(&buffers[0], TRIANGLE_KEY) && Y_Squ > 0)
	{
	Y_Squ--;
	}

if ( PadKeyIsPressed(&buffers[0], X_KEY) && Y_Squ < 240)
	{
	Y_Squ++;
	}

if ( PadKeyIsPressed(&buffers[0], SQUARE_KEY) && Y_Squ > 0)
	{
	X_Squ--;
	}

if ( PadKeyIsPressed(&buffers[0], CIRCLE_KEY) && Y_Squ < 320)
	{
	X_Squ++;
	}

if ( PadKeyIsPressed(&buffers[0], PAD_L3) )
	{
// Test left motor here.

//	MotorStatus[1] = 0xff;
	DS_Big_Rumble();
	}

if ( PadKeyIsPressed(&buffers[0], PAD_R3) )
	{
// Test right motor here.

//	MotorStatus[0] = 0x1;
	DS_Small_Rumble();
	}

if ( PadKeyIsPressed(&buffers[0], SELECT_KEY) && PadKeyIsPressed(&buffers[0], START_KEY) )
	{
	Init_Status(STATUS_TITLE);
	}

if (Pad1.Select == TAP_BUTTON)
	{

	MotorStatus[0] = MotorStatus[1] = 0;

	}


if (Pad1.L_1)
	{
	DS_Big_Rumble();
	}

else if (Pad1.L_2)
	{
	DS_Low_Rumble();
	}

else if (Pad1.R_2)
	{
	DS_Medium_Rumble();
	}

if (Pad1.R_1)
	{
	DS_Small_Rumble();
	}

}


/* ------------------------------------------------------------------------ */

// Holding down the SELECT button while loading launches the PAL version.
#ifdef NTSC
void Trigger_PAL_Version(void)
{

if ( PadKeyIsPressed(&buffers[0], SELECT_KEY) )
	{
	StopControllers();
	StopCallback();
	_96_init();
	LoadExec("cdrom:\\DRAGONSL.PAL;1",0x801FFFF0,0);
	}

}
#endif