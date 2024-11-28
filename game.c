/************************************************************
 *                                                          *
 *                      Dragon's Lair                       *
 *                  PlayStation version                     *
 *          Based on Dragon's Lair II Time Warp             *
 *         To be compiled with Psyq 4.6 or higher           *
 *                                                          *
 *                 Started: August 2024                     *
 *               Completed: August 2024		            *
 *                		                            *
 *            https://archive.org/details/@qbl              *
 *         https://github.com/netyarouze/dragonslair        *
 *                                                          *
 ***********************************************************/


#include <sys/types.h>
#include <libgte.h>
#include <libgpu.h>
#include <libcd.h>
#include "kernel.h"
#include <libsnd.h>

#define GAME_C

#include "control.h"
#include "assets.h"
#include "files.h"
#include "options.h"
#include "sectors.h"
#include "game.h"
#include "bsframes.h"
#include "font.h"
#include "main.h"
#include "sound.h"
#include "movie.h"
#include "movies.h"
#include "language.h"
#include "debug.h"
#include "stages.h"
#include "credits.h"


// ******************************************************************************************


// For debugging only. Modify with custom parameters as required.

void Print_Debug_Info(void)
{

if ( Player1.CurrentScene <= Game_Stages[Player1.CurrentStage].TotalScenes)
	{
FntPrint(fIdA, "Next move: ");

// Display next move.
// Up
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[1] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[1]->Type == MOVIE_ALT_EXIT) )
		{
		FntPrint(fIdA, "UP ");
		}

// Down
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[2] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[2]->Type == MOVIE_ALT_EXIT) )
		{
		FntPrint(fIdA, "DOWN ");
		}

// Left
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[3] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[3]->Type == MOVIE_ALT_EXIT) )
		{
		FntPrint(fIdA, "LEFT ");
		}

// Right.
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[4] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[4]->Type == MOVIE_ALT_EXIT) )
		{
		FntPrint(fIdA, "RIGHT ");
		}

// Sword
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[5] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[5]->Type == MOVIE_ALT_EXIT) )
		{
		FntPrint(fIdA, "SWORD ");
		}
	}
else
	{
	FntPrint(fIdA, " ");
	}

FntPrint(fIdA, "\nStage: %d. ID: %d", Player1.CurrentStage+1, Game_Stages[Player1.CurrentStage].ID);
FntPrint(fIdA, "\nScene: %d", Player1.CurrentScene+1);// In STAGES.H scenes start counting on 1.
FntPrint(fIdA, "\nCheckpoint: %d", Player1.CurrentCheckpoint);
FntPrint(fIdA, "\nFrame: %d", STRCurrentFrame);

/*
if (Game_Config.Vibration == YES)
	{
	FntPrint(fIdA, "\nNext rumble at: %d. Type: %d", Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->RumbleFrame, Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->RumbleType);
	}
*/

if ( ( STRCurrentFrame >= Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Frame ) && ( STRCurrentFrame < Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Frame + Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Time) )
	{
	FntPrint(fIdA, "\n\n\n\n\n			   ~c990Action!\n\n");

// Print pad input.
	if (Pad1.Up)
		{
		FntPrint(fIdA, " UP, ");
		}
	if (Pad1.Down)
		{
		FntPrint(fIdA, " DOWN, ");
		}
	if (Pad1.Left)
		{
		FntPrint(fIdA, " LEFT, ");
		}
	if (Pad1.Right)
		{
		FntPrint(fIdA, " RIGHT, ");
		}
	if (Pad1.Sword)
		{
		FntPrint(fIdA, " SWORD, ");
		}

	}

FntFlush(fIdA);

}


// ******************************************************************************************


// Stores debug info for spotting errors.

void SaveError(short ErrorID, char File[12], char Function[30], int Line)
{

Error_Report.ErrorID = ErrorID;
strcpy(Error_Report.File, File);
strcpy(Error_Report.Function, Function);
Error_Report.Line = Line;

}

// ******************************************************************************************


// This stores a screenshot on vram which will be used for the fadeout effect.


void CopyScreen(short CurrentDisplayBuffer)
{
RECT MyRect;

// Some garbage (a few wrong pixels) is displayed storing the screen like this. Doing it in two steps the result is the same.
setRECT(&MyRect, db[CurrentDisplayBuffer].disp.disp.x, db[CurrentDisplayBuffer].disp.disp.y, db[CurrentDisplayBuffer].disp.disp.w, db[CurrentDisplayBuffer].disp.disp.h);

MoveImage(&MyRect, 320, 0);
DrawSync(0);

// Init brightness for the fade out.
FadeBrightness = 150;
}



// ******************************************************************************************

void Set_StartingFrame(void)
{

if (Player1.CurrentCheckpoint > 0)
	{

	switch (Game_Stages[Player1.CurrentStage].ID)
		{

		case 1: // Main hall.
			Player1.CurrentScene = 1;
		break;

		case 24: // Lizard king.
			Player1.CurrentScene = 7;
		break;

		case 32: // River.
			Player1.CurrentScene = 8;
		break;

		case 38: // Dragon's lair.
			Player1.CurrentScene = 3;
		break;

		}
	
	Player1.StartingFrame = Game_Stages[Player1.CurrentStage].Checkpoint;

	}

// Skip to desired frame when stage provides several chances for correct move.

else if (Player1.SkipSceneFlag > 0)
	{
	switch (Game_Stages[Player1.CurrentStage].ID)
		{

		case 10: // Grim reaper
			Player1.CurrentScene = 1;
			Player1.StartingFrame = 165;
		break;

		case 36: // Geyser.
			if (Player1.SkipSceneFlag == 1)
				{
				Player1.CurrentScene = 2;
				Player1.StartingFrame = 84;
				}

			else if (Player1.SkipSceneFlag == 2)
				{
				Player1.CurrentScene = 3;
				Player1.StartingFrame = 158;
				}
		break;

		}

	Player1.SkipSceneFlag = 0;
	Player1.CurrentAction = NO_ACTION;
	}

else
	{
	Player1.CurrentScene = 0;
	Player1.StartingFrame = 0;
	}

}

// ******************************************************************************************

// Arrange default stages before shuffling and randomly select regular or mirrored variants.

void Init_Default_Stages(void)
{
short i;

// Upper floors.

Game_Stages[0] = Stage1; // Draw bridge.
Game_Stages[1] = Stage2; // Green tentacles.
Game_Stages[2] = Stage3; // Snakes.

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[3] = Stage18; // Ropes (mirrored).
	}
else
	{
	Game_Stages[3] = Stage4; // Ropes.
	}

Game_Stages[4] = Stage6; // Cauldron.
Game_Stages[5] = Stage7; // Giddy goons.
Game_Stages[6] = Stage12; // Bricked wall.
Game_Stages[7] = Stage13; // Room on fire.
Game_Stages[8] = Stage11; // Windy room.
Game_Stages[9] = Stage25; // Poison.

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[10] = Stage31; // Elevator (mirrored).
	}
else
	{
	Game_Stages[10] = Stage21; // Elevator.
	}

// Middle floors.

Game_Stages[11] = Stage8; // Tricky stairs.

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[12] = Stage22; // Smithee (mirrored).
	}
else
	{
	Game_Stages[12] = Stage9; // Smithee.
	}

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[13] = Stage23; // Flying horse (mirrored).
	}
else
	{
	Game_Stages[13] = Stage14; // Flying horse.
	}

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[14] = Stage30; // Checkered floor (mirrored).
	}
else
	{
	Game_Stages[14] = Stage15; // Checkered floor.
	}

Game_Stages[15] = Stage17; // Crumbling bridge.
Game_Stages[16] = Stage20; // Giant bat.
Game_Stages[17] = Stage28; // Tilting floor.
Game_Stages[18] = Stage29; // Throne room.

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[19] = Stage19; // Pool and spider (mirrored).
	}
else
	{
	Game_Stages[19] = Stage5; // Pool and spider.
	}

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[20] = Stage31; // Elevator (mirrored).
	}
else
	{
	Game_Stages[20] = Stage21; // Elevator.
	}

// Lower floors.

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[21] = Stage27; // Grim reaper (mirrored), only one chance.
	}
else
	{
	Game_Stages[21] = Stage10; // Grim reaper, several chances.
	}

Game_Stages[22] = Stage32; // Underground river.
Game_Stages[23] = Stage33; // Mudmen.
Game_Stages[24] = Stage34; // Black horseman.
Game_Stages[25] = Stage35; // Giant marbles.
Game_Stages[26] = Stage36; // Geyser.

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[27] = Stage26; // Crypt keepers (mirrored).
	}
else
	{
	Game_Stages[27] = Stage16; // Crypt keepers.
	}

Game_Stages[28] = Stage24; // Lizard king.

i = rand() % 2;

if (i == 1)
	{
	Game_Stages[29] = Stage31; // Elevator (mirrored).
	}
else
	{
	Game_Stages[29] = Stage21; // Elevator.
	}

Game_Stages[30] = Stage38; // Dragon's lair.

}


// ******************************************************************************************


// Randomly arrange stages. 

void Shuffle_Stages(void)
{

short i, New_Position, Previous_Position;

Init_Default_Stages();

// Shuffle upper floors.

for (i=1; i<=9; i++)
	{
	New_Position = rand() % 9;

	if ( i + New_Position > 9)
		{
		Previous_Position = New_Position;

		New_Position = 9 - Previous_Position;
		}
	if (New_Position == 0)
		{
		New_Position++;
		}

	Current_Stage = Game_Stages[i];

	Previous_Stage = Game_Stages[New_Position];

	Game_Stages[New_Position] = Current_Stage;

	Game_Stages[i] = Previous_Stage;

	}

// Shuffle middle floors.

for (i=11; i<=19; i++)
	{
	New_Position = rand() % 9;

	if ( i + New_Position > 19)
		{
		Previous_Position = New_Position;

		New_Position = 19 - Previous_Position;
		}
	else
		{
		New_Position += i;
		}

	if (New_Position == 10)
		{
		New_Position++;
		}

	Current_Stage = Game_Stages[i];

	Previous_Stage = Game_Stages[New_Position];

	Game_Stages[New_Position] = Current_Stage;

	Game_Stages[i] = Previous_Stage;

	}

// Shuffle lower floors.

for (i=21; i<=28; i++)
	{
	New_Position = rand() % 8;

	if ( i + New_Position > 28)
		{
		Previous_Position = New_Position;

		New_Position = 28 - Previous_Position;
		}
	else
		{
		New_Position += i;
		}

	if (New_Position == 20)
		{
		New_Position++;
		}

	Current_Stage = Game_Stages[i];

	Previous_Stage = Game_Stages[New_Position];

	Game_Stages[New_Position] = Current_Stage;

	Game_Stages[i] = Previous_Stage;

	}

}


// ******************************************************************************************


// Init instant death scenes.

void Init_InstantDeathScene(void)
{

switch (Game_Stages[Player1.CurrentStage].ID)
	{
	case 1:
	CurrentInstantDeathScene[0] = Stage1InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage1InstantDeathScene2;
	break;

	case 4:
	CurrentInstantDeathScene[0] = Stage4InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage4InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage4InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage4InstantDeathScene4;
	break;

	case 7:
	CurrentInstantDeathScene[0] = Stage7InstantDeathScene1;
	break;

	case 9:
	CurrentInstantDeathScene[0] = Stage9InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage9InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage9InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage9InstantDeathScene4;
	break;

	case 10:
	CurrentInstantDeathScene[0] = Stage10InstantDeathScene1;
	break;

	case 11:
	CurrentInstantDeathScene[0] = Stage11InstantDeathScene1;
	break;

	case 18:
	CurrentInstantDeathScene[0] = Stage18InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage18InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage18InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage18InstantDeathScene4;
	break;

	case 21:
	CurrentInstantDeathScene[0] = Stage21InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage21InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage21InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage21InstantDeathScene4;
	CurrentInstantDeathScene[4] = Stage21InstantDeathScene5;
	CurrentInstantDeathScene[5] = Stage21InstantDeathScene6;
	CurrentInstantDeathScene[6] = Stage21InstantDeathScene7;
	CurrentInstantDeathScene[7] = Stage21InstantDeathScene8;
	CurrentInstantDeathScene[8] = Stage21InstantDeathScene9;
	CurrentInstantDeathScene[9] = Stage21InstantDeathScene10;
	break;

	case 22:
	CurrentInstantDeathScene[0] = Stage22InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage22InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage22InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage22InstantDeathScene4;
	break;

	case 27:
	CurrentInstantDeathScene[0] = Stage27InstantDeathScene1;
	break;

	case 29:
	CurrentInstantDeathScene[0] = Stage29InstantDeathScene1;
	break;

	case 31:
	CurrentInstantDeathScene[0] = Stage31InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage31InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage31InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage31InstantDeathScene4;
	CurrentInstantDeathScene[4] = Stage31InstantDeathScene5;
	CurrentInstantDeathScene[5] = Stage31InstantDeathScene6;
	CurrentInstantDeathScene[6] = Stage31InstantDeathScene7;
	CurrentInstantDeathScene[7] = Stage31InstantDeathScene8;
	CurrentInstantDeathScene[8] = Stage31InstantDeathScene9;
	CurrentInstantDeathScene[9] = Stage31InstantDeathScene10;
	break;

	case 34:
	CurrentInstantDeathScene[0] = Stage34InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage34InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage34InstantDeathScene3;
	break;

	case 35:
	CurrentInstantDeathScene[0] = Stage35InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage35InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage35InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage35InstantDeathScene4;
	CurrentInstantDeathScene[4] = Stage35InstantDeathScene5;
	CurrentInstantDeathScene[5] = Stage35InstantDeathScene6;
	break;

	case 36:
	CurrentInstantDeathScene[0] = Stage36InstantDeathScene1;
	CurrentInstantDeathScene[1] = Stage36InstantDeathScene2;
	CurrentInstantDeathScene[2] = Stage36InstantDeathScene3;
	CurrentInstantDeathScene[3] = Stage36InstantDeathScene4;
	break;

	}

}


// ******************************************************************************************


// Set player variables during game.

void Init_Player(short Cause)
{

switch (Cause)
	{

	case INIT_PLAYER_NEWGAME:

	Player1.Lives = INITIAL_LIVES;
	switch (Game_Config.Difficulty)
		{
		case EASY_DIFFICULTY:
		Player1.Credits = -1; // Unlimited
		break;

		case NORMAL_DIFFICULTY:
		Player1.Credits = 3;
		break;

		case HARD_DIFFICULTY:
		Player1.Credits = 0;
		break;
		}
	Player1.CurrentStage = 0;
	Player1.CurrentScene = 0;
	Player1.CurrentCheckpoint = 0;
	Player1.StartingFrame = 0;
	Player1.CurrentAction = NO_ACTION;
	Player1.Deaths = 0;
	Player1.CreditsUsed = 0;
	Player1.Pause = NO;
	Player1.Score = 0;
	Player1.InstantDeathFlag = 0;
	Player1.SkipSceneFlag = 0;

	break;

	case INIT_PLAYER_DEATH:

// Unlimited lives in debug mode.
	if (Debug_Config.Debug_Mode == NO)
		{
		Player1.Lives--;
		}
	else if (Debug_Stage.UnlimitedLives == NO)
		{
		Player1.Lives--;
		}

	Player1.Deaths++;


	// Set current scene after checkpoint or restart from the beginning.
	Set_StartingFrame();

	Player1.CurrentAction = NO_ACTION;
	Player1.InstantDeathFlag = 0;

	break;

	case INIT_PLAYER_CONTINUE:

	if (Game_Config.Difficulty > EASY_DIFFICULTY)
		Player1.Credits--;
	Player1.CreditsUsed++;
	Player1.Lives = INITIAL_LIVES;
	// Set current scene after checkpoint or restart from the beginning.
	Set_StartingFrame();
	Player1.CurrentAction = NO_ACTION;
	Player1.SkipSceneFlag = 0;

	break;

	case INIT_PLAYER_STAGECLEAR:

	Player1.CurrentStage++;
	Player1.CurrentScene = 0;
	Player1.CurrentCheckpoint = 0;
	Player1.StartingFrame = 0;
	Player1.CurrentAction = NO_ACTION;
//	Previous_Stage = Current_Stage = Game_Stages[Player1.CurrentStage];
	Init_InstantDeathScene();
	Player1.SkipSceneFlag = 0;

	break;

	case INIT_PLAYER_DEBUGGING:

// Restore current stage.
//	Game_Stages[Player1.CurrentStage] = Previous_Stage;

	Player1.CurrentStage = Debug_Stage.Stage;
	Player1.CurrentCheckpoint = Debug_Stage.Checkpoint;
	if (Game_Stages[Player1.CurrentStage].Checkpoint == 0)
		{
		Player1.CurrentCheckpoint = 0;
		}
	Player1.InstantDeathFlag = 0;

// Replace random stage with custom selected one.

	switch(Game_Stages[Player1.CurrentStage].ID)
		{

		case 4:
		case 18:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage18;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage4;
			}
		break;

		case 5:
		case 19:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage19;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage5;
			}
		break;

		case 9:
		case 22:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage22;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage9;
			}

		break;

		case 10:
		case 27:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage27;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage10;
			}

		break;

		case 14:
		case 23:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage23;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage14;
			}

		break;

		case 15:
		case 30:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage30;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage15;
			}

		break;

		case 16:
		case 26:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage26;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage16;
			}

		break;

		case 21:
		case 31:

		if (Debug_Stage.Alternate == 1)
			{
			Game_Stages[Player1.CurrentStage] = Stage31;
			}
		else
			{
			Game_Stages[Player1.CurrentStage] = Stage21;
			}

		break;

		}

//-------------------

//	Previous_Stage = Current_Stage = Game_Stages[Debug_Stage.Stage];
	Init_InstantDeathScene();
	Set_StartingFrame();
	Player1.CurrentAction = NO_ACTION;
	Game_Status = STATUS_GAMEPLAY;
	Player1.SkipSceneFlag = 0;

	break;

	}

BSCurrentFrame = 0;

}


// ******************************************************************************************


// Init required variables when starting a new game.

void Init_Game(void)
{

Init_Player(INIT_PLAYER_NEWGAME);

Shuffle_Stages();
Init_InstantDeathScene();

}


// ******************************************************************************************


// Init variables as required for current game status.

void Init_Status(short Status)
{

switch (Status)
	{

	case STATUS_LOADING:
	CopyScreen(cdb);
	Game_Status = STATUS_FADEOUT;
	Next_Game_Status = STATUS_LOADING;
	break;

	case STATUS_TITLE:
	if (Game_Config.Vibration == YES && PadGetState(0x00) == 6 )
		{
		Init_DS_Motors();
		}
// Exclude fadeout in 24bit mode.
	if (dec.is24Bit)
		{
		FadeBrightness = 150;
		}
// Select required buffer index before taking screenshot for fadeout.
	else if (Game_Status == STATUS_GAMEPLAY || Game_Status == STATUS_DEATH || Game_Status == STATUS_DIRK)
		{

		if( !(Player1.Pause) )
			{
			dec.rectId ^= 1;
			CopyScreen(dec.rectId);
			}
		else
			{
			CopyScreen(dec.rectId);
			dec.rectId ^= 1;
			}

//		dec.rectId ^= 1;
//		CopyScreen(dec.rectId);
		}
	else if (Game_Status == STATUS_INTRO_MOVIE || Game_Status == STATUS_SECRET || Game_Status == STATUS_WATCHMOVIES)
		{
		CopyScreen(dec.rectId);		
		}
	else
		{
		CopyScreen(cdb);
		}

	Game_Status = STATUS_FADEOUT;
	Next_Game_Status = STATUS_TITLE;
	Title_Music_Playing = NO;
	Countdown_To_Intro = TITLE_IDLE_TIME;
	BSCurrentFrame = 0;
	Options_Menu = 0;
	Selected_Option = 0;
	Player1.Pause = 0;
	break;

	case STATUS_INTRO_MOVIE:
	CopyScreen(cdb);
	Game_Status = STATUS_FADEOUT;
	Next_Game_Status = STATUS_INTRO_MOVIE;
	break;

	case STATUS_GAMEPLAY:
	if (Game_Config.Vibration == YES && PadGetState(0x00) == 6 )
		{
		Init_DS_Motors();
		}
	Init_Game();
	CopyScreen(cdb);
	Game_Status = STATUS_FADEOUT;
	Next_Game_Status = STATUS_GAMEPLAY;
	break;

	case STATUS_CONTINUE:
	CopyScreen(cdb);
	Game_Status = STATUS_FADEOUT;
	Next_Game_Status = STATUS_GAMEPLAY;

	Init_Player(INIT_PLAYER_CONTINUE);
	break;

	case STATUS_CREDITS:
// Japanese font set can't display western characters with accents.
	if (SelectedLanguage == 1) // Japanese
		{
		End_Credits[CREDITS_LENGTH-3][9] = 'O';
		}
	else
		{
		End_Credits[CREDITS_LENGTH-3][9] = 'Ó';
		}

	Credits_Y = 240;
	BSCurrentFrame = 0;
	Game_Status = STATUS_CREDITS;
	PlaySound(SFXEnd);
	break;

	case STATUS_DEBUGMENU:
	CopyScreen(cdb);
	Game_Status = STATUS_FADEOUT;
	Next_Game_Status = STATUS_DEBUGMENU;
	BSCurrentFrame = 0;
	break;

	case STATUS_PADTEST:
	CopyScreen(cdb);
	Game_Status = STATUS_FADEOUT;
	Next_Game_Status = STATUS_PADTEST;
	break;
	
	}

// For handling errors.
Prev_Game_Status = Next_Game_Status;

}

// ******************************************************************************************

// Score for ending screen.


void Display_Score(void)
{
char TotalStars[5];

short i;

if (Player1.Score == 0)
	{
	for (i=0; i<5; i++)
		{
		TotalStars[i] = ' ';
		}

	switch(Game_Config.Difficulty)
		{

		case EASY_DIFFICULTY:

		Player1.Score += 1;

		if (Player1.CreditsUsed == 0)
			{
			Player1.Score += 1;
			}

		if (Player1.Deaths == 0)
			{
			Player1.Score += 1;
			}
		break;

		case NORMAL_DIFFICULTY:

		Player1.Score += 1;


		if (Player1.CreditsUsed == 0)
			{
			Player1.Score += 1;
			}

		if (Player1.Deaths == 0)
			{
			Player1.Score += 2;
			}
		break;

		case HARD_DIFFICULTY:

		Player1.Score += 2;

		if (Player1.Deaths == 0)
			{
			Player1.Score += 3;
			}
		break;
		}

//printf("\nScore: %d", Player1.Score);
	}


for (i=0; i<Player1.Score; i++)
	{
	TotalStars[i] = ' '-15;
	}

if (Player1.Score == 0)
	{
	TotalStars[0] = ' '-16;
	Puts16p(16+(strlen(TXT_Score[SelectedLanguage]) * 16)+32, 26+(20*9), TotalStars, ColorYellow);	
	}
else
	{
	Puts16p(16+(strlen(TXT_Score[SelectedLanguage]) * 16)+32, 26+(20*9), TotalStars, ColorYellow);
	}

}


// ******************************************************************************************


// Ending screen.

void Ending_Screen(void)
{
char MyText[30];


PlayBSFrame(BSEnding, BSNOLOOP);


// Deaths.
sprintf(MyText, "%s: %d", TXT_Mistakes[SelectedLanguage], Player1.Deaths);
Puts16p(16, 26+(20), MyText, ColorWhite);

// Continues.
sprintf(MyText, "%s: %d", TXT_Retries[SelectedLanguage], Player1.CreditsUsed);
Puts16p(16, 26+(20*2), MyText, ColorWhite);

// Perfect run.
if ( Player1.Deaths == 0 )
	{
	Blinking_Text( TXT_Perfect[SelectedLanguage] );
	}

//Difficulty.
sprintf(MyText, "%s:%s", TXT_Difficulty[SelectedLanguage], Difficulty_Entries[Game_Config.Difficulty]);
if ( (Game_Config.Difficulty == 2 && SelectedLanguage == 4) || SelectedLanguage == 5)
	{
	Puts8p(16, 26+(20*7), MyText, ColorWhite);
	}
else
	{
	Puts16p(16, 26+(20*7), MyText, ColorWhite);
	}

// Score.
sprintf(MyText, "%s:", TXT_Score[SelectedLanguage]);
Puts16p(16, 26+(20*9), MyText, ColorWhite);
Display_Score();

if (Debug_Config.Debug_Mode == 1)
	{
	CenterText(10, 8, "Debug Mode", ColorWhite);
	}

if (Pad1.Start == TAP_BUTTON)
	{
	SsUtAllKeyOff(0);
	Init_Status(STATUS_CREDITS);
	}
}


// ******************************************************************************************

// Hidden movie playback.


void Play_Secret(void)
{

PlayStream(&STR_TWDemo, 0);

if (Game_Status != STATUS_ERRORSCREEN)
	{
	Init_Status(STATUS_TITLE);
	}
// To avoid a blinking frame when framebuffer index does not match.
cdb = dec.rectId;
}


// ******************************************************************************************


// End credits roll.

void Credits_Roll(void)
{
short i;

PlayBSFrame(BSBackground, BSNOLOOP);


if ( Credits_Y > (-12 * CREDITS_LENGTH) )
	{
	Credits_Y-=2;
	}
else
	{
	SsUtAllKeyOff(0);
	if (Game_Config.Difficulty == HARD_DIFFICULTY )
		{
		Game_Status = STATUS_SECRET;
		}
	else
		{
		Init_Status(STATUS_TITLE);
		}
	return;
	}


for (i=0;i < CREDITS_LENGTH; i++)
	{
	if ( ( ( Credits_Y + (i*12) ) > -8 ) && ( ( Credits_Y + (i*12) ) < 248 ) )
		{
		CenterText(Credits_Y + (i*12), 8, End_Credits[i], ColorWhite);
		}
	}

//if (Credits_Y < -1800)
if (Credits_Y < -12 * (CREDITS_LENGTH - 10) )
	{
	CenterText(116,16,"Thanks for playing!", ColorWhite);
	}

if ( Pressed(UP_KEY) || Left_Stick_Y < -STICK_THRESHOLD || Right_Stick_Y < -STICK_THRESHOLD )
	{
	Credits_Y -= 10;
	}

if ( Credits_Y < 240 && ( Pressed(DOWN_KEY) || Left_Stick_Y > STICK_THRESHOLD || Right_Stick_Y > STICK_THRESHOLD ) )
	{
	Credits_Y += 10;
	}

}


// ******************************************************************************************


// Play current stage movie.

void Play_Stage(void)
{

if (Player1.SkipSceneFlag > 0)
	{
	Set_StartingFrame();
	}

PlayStream(Game_Stages[Player1.CurrentStage].Movie, Player1.StartingFrame);

// Init next stage or alternate path.

// Play alternate exit movie if required.

if (Game_Status == STATUS_ALT_EXIT)
	{
	PlayStream(Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction], 0);

// Check if player has not pressed START+SELECT to quit during movie.
	if (Game_Status == STATUS_ALT_EXIT)
		{
		Game_Status = STATUS_GAMEPLAY; // Keep playing game.
		}
	}

// Elevator exception. Reaching the end of the movie means Dirk has died.

else if (Game_Status == STATUS_GAMEPLAY && ( Game_Stages[Player1.CurrentStage].ID == 21 || Game_Stages[Player1.CurrentStage].ID == 31) )
	{
	if (Player1.Lives > 0)
		{
		Init_Player(INIT_PLAYER_DEATH);
		Game_Status = STATUS_DIRK;
		}
	else
		{
// Game Over / Continue screen.
		if (Player1.Credits > 0 || Game_Config.Difficulty == EASY_DIFFICULTY)
			{
			Game_Status = STATUS_CONTINUE;
			Countdown_To_Intro = 10;
			}
		else
			{
			PlaySound(SFXContinue);
			Game_Status = STATUS_GAMEOVER;
			}
		BSCurrentFrame = 0;
		}
	}


if (Game_Status == STATUS_GAMEPLAY && Player1.SkipSceneFlag == 0)
	{
	if (Player1.CurrentStage < MAX_STAGES-1)
		{
		Init_Player(INIT_PLAYER_STAGECLEAR);
		}
	else
		{
		BSCurrentFrame = 0;
		Game_Status = STATUS_ENDING;
		PlaySound(SFXContinue);
		}
	}

else if (Game_Status == STATUS_DEBUGGING)
	{
	Init_Player(INIT_PLAYER_DEBUGGING);
	}

// To avoid a blinking frame when framebuffer index does not match.
cdb = dec.rectId;
}


// ******************************************************************************************


// Game Over screen.

void GameOver_Screen(void)
{

PlayBSFrame(BSGameOver, BSNOLOOP);

CenterText(112, 16, "Game Over", ColorWhite);

if (Pad1.Start == TAP_BUTTON || Pad1.Sword == TAP_BUTTON && BSCurrentFrame >= 10)
	{
	SsUtAllKeyOff(0);
	PlaySound(SFXConfirm);
	Init_Status(STATUS_TITLE);
	}

}


// ******************************************************************************************


// Continue screen.

void Continue_Screen(void)
{
char MyText[20];

PlayBSFrame(BSBackground, BSNOLOOP);

if ( Game_Config.Difficulty == EASY_DIFFICULTY )
	{
	sprintf(MyText, "%s: `", TXT_Credits[SelectedLanguage]);
	Puts16p(16, 26, MyText, ColorWhite);
	}
else
	{
	sprintf(MyText, "%s: %d", TXT_Credits[SelectedLanguage], Player1.Credits);
	Puts16p(16, 26, MyText, ColorWhite);
	}

CenterText(112, 16, TXT_Continue[SelectedLanguage], ColorWhite);

sprintf(MyText, "%d", Countdown_To_Intro);

CenterText(132, 16, MyText, ColorWhite);

if (Countdown_To_Intro <= 0)
	{
	PlaySound(SFXContinue);
	Game_Status = STATUS_GAMEOVER;
	BSCurrentFrame = 0;
	}

else if (  ( ( LoopCount % (FRAMES_PER_SECOND/2) ) == 0 ) || Pad1.Sword == TAP_BUTTON)
	{
	PlaySound(SFXWrong);
	Countdown_To_Intro--;
	}

else if (Pad1.Start == TAP_BUTTON)
	{
	PlaySound(SFXTitle);
	Init_Status(STATUS_CONTINUE);
	}

}

// ******************************************************************************************

// Print remaining lives.

void Print_Lives(void)
{
char MyText[20];

sprintf(MyText, "%s: %d", TXT_Lives[SelectedLanguage], Player1.Lives);
CenterText(210, 16, MyText, ColorWhite);

}


// ******************************************************************************************

// Dirk animation.

void Play_DirkMovie(void)
{

PlayStream(Game_Stages[Player1.CurrentStage].DirkMovie, 0);

// If not preseed SELECT+START during movie playback continue playing game.

if (Game_Status == STATUS_DIRK)
	{
	Game_Status = STATUS_GAMEPLAY;
	Prev_Game_Status = STATUS_DIRK;
	}

}


// ******************************************************************************************


// Play death movie.

void Play_Death(void)
{

if (Player1.InstantDeathFlag == 1)
	{
	PlayStream(DeathMovie, 0);
	}
else
	{
	PlayStream(Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction], 0);
	}

// Check player has not pressed START + SELECT during movie.
if (Game_Status == STATUS_DEATH)
	{
	Init_Player(INIT_PLAYER_DEATH);

	if (Player1.Lives > 0)
		{
		Game_Status = STATUS_DIRK;
		}
	else
		{
// Game Over / Continue screen.
		if (Player1.Credits > 0 || Game_Config.Difficulty == EASY_DIFFICULTY)
			{
			Game_Status = STATUS_CONTINUE;
			Countdown_To_Intro = 10;
			}
		else
			{
			PlaySound(SFXContinue);
			Game_Status = STATUS_GAMEOVER;
			}
		BSCurrentFrame = 0;
		}
	}

if (Game_Config.Vibration == YES && PadGetState(0x00) == 6)
	{
	Init_DS_Motors();
	}

// To avoid a blinking frame when framebuffer index does not match.
cdb = dec.rectId;
}


// ******************************************************************************************


// Initialize textures and sounds previously loaded from disc.

int InitAssets(void)
{
// Init font textures. Load western font by default.

	if ( ReadMyTIM((u_long *)FONT16W_TIM) == 1)
		{
		return 1; // Error.
		}
	InitFont16p(640, 0, 640, 256);

	if ( ReadMyTIM((u_long *)FONT8W_TIM) == 1)
		{
		return 1; // Error.
		}
	InitFont8p(704, 0, 704, 256);

// Set up primitives for the fade out effect.
	setRGB0(&FadeLeft, 255, 255, 255);
	setXYWH(&FadeLeft, 0, 0, 192, 255 );
	setTPage(&FadeLeft, 2, 1, 320, 0);
	setUV4(&FadeLeft, 0, 0, 192, 0, 0, 255, 192, 255);

	setRGB0(&FadeRight, 255, 255, 255);
	setXYWH(&FadeRight, 192, 0, 128, 255 );
	setTPage(&FadeRight, 2, 1, 512, 0);
	setUV4(&FadeRight, 0, 0, 128, 0, 0, 255, 128, 255);

// Init dimensions of bitstream chunks.
	InitBSFrameSize();
	InitBSMovie();

// Init sound samples.
	SoundEffects = SsVabTransfer((u_char*)SFX_VH, (u_char*)SFX_VB, 0, SS_WAIT_COMPLETED);

// Check for errors.

	if ( (int)SoundEffects < 0 )
		{
		return 1;
		}

// No errors.
	return 0;

}


// ******************************************************************************************

// Intro movie playback.


void Play_Intro(void)
{

PlayStream(&STR_Intro, 0);

if (Game_Status != STATUS_ERRORSCREEN)
	{
	Init_Status(STATUS_TITLE);
	}
// To avoid a blinking frame when framebuffer index does not match.
cdb = dec.rectId;
}


// ****************************************************************************************



// Show stored screenshot with decreasing brightness until screen fades to black.


void FadeOut(void)
{
RECT MyRect = {320,0,320,240};

setRGB0(&FadeLeft, FadeBrightness, FadeBrightness, FadeBrightness);
setRGB0(&FadeRight, FadeBrightness, FadeBrightness, FadeBrightness);

setPolyFT4(&FadeLeft);
DrawPrim(&FadeLeft);

setPolyFT4(&FadeRight);
DrawPrim(&FadeRight);

FadeBrightness -= 2;


if (FadeBrightness <= 0)
	{
//Fade out complete, move on.
	Game_Status = Next_Game_Status;
	ClearImage(&MyRect, 0, 0, 0);
	}

}


// ******************************************************************************************

// This is the first screen shown after booting the program. Assets are loaded from disc while a progress bar is displayed.

void Loading_Screen(void)
{
POLY_F4 BG_Frame;
CdlLOC FilePosition;
static short Gauge = 0;

//Frame and background.

SetPolyF4(&BG_Frame);
setRGB0(&BG_Frame, 255, 0, 0); //Red background
//setXY4(&BG_Frame, 10, 15, 310, 15, 10, Height-30, 310, Height-30);
setXY4(&BG_Frame, 0, 0, 320, 0, 0, Height, 320, Height);
DrawPrim(&BG_Frame);

//Loading gauge
SetPolyF4(&BG_Frame);
setRGB0(&BG_Frame, 255, 255, 255); //White frame
setXY4(&BG_Frame, 60, 150, 260, 150, 60, 200, 260, 200);
DrawPrim(&BG_Frame);

//Empty bar
SetPolyF4(&BG_Frame);
setRGB0(&BG_Frame, 255, 0, 0); //Red empty bar
setXY4(&BG_Frame, 60+5, 150+5, 260-5, 150+5, 60+5, 200-5, 260-5, 200-5);
DrawPrim(&BG_Frame);

FntPrint(fIdA, "\n\n\n~c990Dragon's Lair~c999 is a registered\ntrademark of\
 bluth group, ltd.\n\n\nThis is an unofficial, unauthorized \nport made \
for educational purposes\nonly.\n\n\nNot to be sold in any form.");

//Progress bar is empty
if (Gauge == 0)
	{
//Start reading assets file.
	if ( !CdControl(CdlSetloc, (u_char *)CdIntToPos(Assets.Position, &FilePosition),0) )
		{
//		CdControlB(CdlPause, 0, 0); //Pause CD
		PauseCD();
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;

		SaveError(READ_ERROR, __FILE__, __FUNCTION__, __LINE__);
		return;
		}

	if ( !CdRead(Assets.Size, (u_long *)ASSETS_ADDRESS, CdlModeSpeed) )
		{
//		CdControlB(CdlPause, 0, 0); //Pause CD
		PauseCD();
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;

		SaveError(READ_ERROR, __FILE__, __FUNCTION__, __LINE__);
		return;
		}

// Compute % of loaded data.
	Gauge = 1 + Assets.Size - CdReadSync(1, 0);
	}
else if (CdReadSync(1, 0) == 0)
	{
//Assets loaded.
	if ( InitAssets() == 0)
		{
		Game_Status = STATUS_FADEOUT;
		Next_Game_Status = STATUS_LANGUAGE_SELECTION;
		}
	else
		{
		Game_Status = STATUS_ERRORSCREEN;
		SaveError(READ_ERROR, __FILE__, __FUNCTION__, __LINE__);
		return;
		}
	}
else if (CdReadSync(1, 0) == -1 || _get_errno() == 2)
	{
//Read error.
//	CdControlB(CdlPause, 0, 0); //Pause CD
	PauseCD();
	Prev_Game_Status = Game_Status;
	Game_Status = STATUS_ERRORSCREEN;

	SaveError(READ_ERROR, __FILE__, __FUNCTION__, __LINE__);
	return;
	}

//Fill progress bar while loading.
	Gauge = 1 + Assets.Size - CdReadSync(1, 0);

	//Yellow progress bar
	SetPolyF4(&BG_Frame);
	setRGB0(&BG_Frame, 255, 255, 0); //Yellow progress bar
	setXY4(&BG_Frame, 60+5, 150+5, ((60+5) + ( (Gauge * 100)/Assets.Size)*190/100 ), 150+5, 60+5, 200-5, ((60+5) + ( (Gauge * 100)/Assets.Size)*190/100 ), 200-5);
	DrawPrim(&BG_Frame);


//Print % of loaded data.
FntPrint(fIdA, "\n\n\n\n\n\n\n			 Loading %3d%%", (Gauge * 100)/Assets.Size);

//Print errors (for debugging only)
//FntPrint(fIdA, "\n\nError: %d", _get_errno());
//printf("\nError: %d", _get_errno());


FntFlush(fIdA);

// Leave when ready and take a screenshot for the fade out.
if ( Game_Status == STATUS_FADEOUT)
	{
	FntPrint(fIdA, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n	  WELCOME TO DRAGON'S LAIR");

// For the random mirrored levels.
//	srand(LoopCount);
	srand(GetRCnt(2));
	printf("\nWelcome to Dragon's Lair.\nBuild date: %s", __DATE__);
	PlaySound(SFXConfirm);
	FntFlush(fIdA);
	CopyScreen(cdb);
	}
// In case of read error init gauge to retry reading.
else if ( Game_Status == STATUS_ERRORSCREEN )
	{
	Gauge = 0;
	}

}


// ******************************************************************************************

// Take a screenshot for the pause mode. Not optimized for 24bit pictures.

extern void StrClearVRAM(void);
extern StrInfo StrInfoBase;

void Take_Pause_Screenshot(void)
{
short BufferIndex = dec.rectId;

// Only 16bit mode.
if (StrInfoBase.mode == STR_MODE16)
	{
	BufferIndex ^= 1;
	CopyScreen(BufferIndex);

	setRGB0(&FadeLeft, 150, 150, 150);
	setRGB0(&FadeRight, 150, 150, 150);
	}
else
	{
	StrClearVRAM();
	}
}

// ******************************************************************************************

void Show_Pause_Screenshot(void)
{
if (StrInfoBase.mode == STR_MODE16)
	{
	setPolyFT4(&FadeLeft);
	DrawPrim(&FadeLeft);

	setPolyFT4(&FadeRight);
	DrawPrim(&FadeRight);
	}

}

// ******************************************************************************************

// Alternate pause state during game.

void Switch_Pause_Mode(void)
{

if (Game_Config.Vibration == YES && PadGetState(0x00) == 6 )
	{
	Init_DS_Motors();
	}

PlaySound(SFXConfirm);
Player1.Pause ^= 1;
if (Player1.Pause == YES)
	{
	Take_Pause_Screenshot();
//	CdControlB(CdlPause, 0, 0);
	if ( !PauseCD() )
		{
		StopPlayingMovie = YES;
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;

		SaveError(READ_ERROR, __FILE__, __FUNCTION__, __LINE__);
		}
	}
else
	{
	if ( !CdRead2(CdlModeStream|CdlModeSpeed|CdlModeRT) )
		{
//		CdControlB(CdlPause, 0, 0); //Pause CD
		PauseCD();
		StopPlayingMovie = YES;
		Prev_Game_Status = Game_Status;
		Game_Status = STATUS_ERRORSCREEN;

		SaveError(READ_ERROR, __FILE__, __FUNCTION__, __LINE__);
		}
	}

}



// ******************************************************************************************

// Debug / cheat menu for quickly testing scenes.

void InGame_Debug_Menu(void)
{

//DrawWindow(50,127,220,90);

FntPrint(fIdA, "\n\n\n\n\n\n\n\n\n\n\n\n\n\n			  debug menu");
FntPrint(fIdA, "\n\n 		Unlimited lives: %s", OnOff_Entries[Debug_Stage.UnlimitedLives]);
FntPrint(fIdA, "\n\n 		Stage: %d. ID: %d", Debug_Stage.Stage+1, Game_Stages[Debug_Stage.Stage].ID);

if (Game_Stages[Debug_Stage.Stage].Checkpoint > 0)
	{
	FntPrint(fIdA, "\n\n 		Checkpoint: %d", Debug_Stage.Checkpoint);
	}
else
	{
	FntPrint(fIdA, "\n\n");
	}

switch(Game_Stages[Debug_Stage.Stage].ID)
	{

	case 4:
	case 18:
	case 5:
	case 19:
	case 9:
	case 22:
	case 10:
	case 27:
	case 14:
	case 23:
	case 15:
	case 30:
	case 16:
	case 26:
	case 21:
	case 31:
	FntPrint(fIdA, "\n\n 		Mirrored: %s", OnOff_Entries[Debug_Stage.Alternate]);
	break;

	default:
	FntPrint(fIdA, "\n\n");

	}

FntPrint(fIdA, "\n\n 		Apply changes");
FntFlush(fIdA);

Puts8p(75, 144 + (Selected_Option*16), ">", ColorWhite);

if (Pad1.Down == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	Selected_Option++;
	if (Selected_Option > 4)
		{
		Selected_Option = 0;
		}
	}

if (Pad1.Up == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	Selected_Option--;
	if (Selected_Option < 0)
		{
		Selected_Option = 4;
		}
	}

if (Pad1.Right == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	switch ( Selected_Option )
		{
		case 0: // Unlimited lives.
		Debug_Stage.UnlimitedLives ^= 1;
		break;

		case 1: // Stage.
		Debug_Stage.Stage++;
		if ( Debug_Stage.Stage > MAX_STAGES-1 )
			{
			Debug_Stage.Stage = 0;
			}
		break;

		case 2: // Checkpoint.
		Debug_Stage.Checkpoint++;
		if ( Debug_Stage.Checkpoint > 1 )
			{
			Debug_Stage.Checkpoint = 0;
			}
		break;

		case 3: // Alternate levels.
		Debug_Stage.Alternate ^= 1;
		break;
		}
	}

if (Pad1.Left == TAP_BUTTON)
	{
	PlaySound(SFXCorrect);
	switch ( Selected_Option )
		{
		case 0: // Unlimited lives.
		Debug_Stage.UnlimitedLives ^= 1;
		break;

		case 1: // Stage.
		Debug_Stage.Stage--;
		if ( Debug_Stage.Stage < 0 )
			{
			Debug_Stage.Stage = MAX_STAGES-1;
			}
		break;

		case 2: // Checkpoint.
		Debug_Stage.Checkpoint--;
		if ( Debug_Stage.Checkpoint < 0 )
			{
			Debug_Stage.Checkpoint = 1;
			}
		break;

		case 3: // Alternate levels.
		Debug_Stage.Alternate ^= 1;
		break;
		}	
	}

if ( Pad1.Sword == TAP_BUTTON && Selected_Option == 4 )
	{
	StopPlayingMovie = YES;
	Game_Status = STATUS_DEBUGGING;
	Switch_Pause_Mode();
	}

}


// ******************************************************************************************

// Play sound effect depending on player's right or wrong choice.

void Decide_SFX(void)
{

if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction]->Type == MOVIE_ALT_EXIT ) )
	{
	PlaySound(SFXCorrect);
	}
else
	{
	PlaySound(SFXWrong);
	}

}


// ******************************************************************************************

// Print correct move when playing easy difficulty setting.

void Display_Hints(void)
{

if ( Game_Config.Difficulty == EASY_DIFFICULTY && Player1.CurrentScene <= Game_Stages[Player1.CurrentStage].TotalScenes)
//if ( Game_Config.Difficulty == EASY_DIFFICULTY )
	{
// Up
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[1] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[1]->Type == MOVIE_ALT_EXIT) )
		{
		if (Player1.CurrentAction == NO_ACTION)
			{
			CenterText(16, 16, Move_Entries[1], ColorWhite);
			}
		else if (Player1.CurrentAction == ACTION_UP)
			{
			CenterText(16, 16, Move_Entries[1], ColorYellow);
			}
		else
			{
			CenterText(16, 16, Move_Entries[1], ColorRed);
			}
		}

// Down
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[2] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[2]->Type == MOVIE_ALT_EXIT) )
		{
		if (Player1.CurrentAction == NO_ACTION)
			{
			CenterText(210, 16, Move_Entries[2], ColorWhite);
			}
		else if (Player1.CurrentAction == ACTION_DOWN)
			{
			CenterText(210, 16, Move_Entries[2], ColorYellow);
			}
		else
			{
			CenterText(210, 16, Move_Entries[2], ColorRed);
			}
		}

// Left
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[3] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[3]->Type == MOVIE_ALT_EXIT) )
		{
		if (Player1.CurrentAction == NO_ACTION)
			{
			Puts16p(16, 112, Move_Entries[3], ColorWhite);
			}
		else if (Player1.CurrentAction == ACTION_LEFT)
			{
			Puts16p(16, 112, Move_Entries[3], ColorYellow);
			}
		else
			{
			Puts16p(16, 112, Move_Entries[3], ColorRed);
			}
		}

// Right.
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[4] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[4]->Type == MOVIE_ALT_EXIT) )
		{
		if (Player1.CurrentAction == NO_ACTION)
			{
			AlignRight(112, 16, Move_Entries[4], ColorWhite);
			}
		else if (Player1.CurrentAction == ACTION_RIGHT)
			{
			AlignRight(112, 16, Move_Entries[4], ColorYellow);
			}
		else
			{
			AlignRight(112, 16, Move_Entries[4], ColorRed);
			}

		}

// Sword
	if ( ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[5] == KEEP_PLAYING ) || ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[5]->Type == MOVIE_ALT_EXIT) )
		{
		if (Player1.CurrentAction == NO_ACTION)
			{
			CenterText(130, 16, Move_Entries[5], ColorWhite);
			}
		else if (Player1.CurrentAction == ACTION_SWORD)
			{
			CenterText(130, 16, Move_Entries[5], ColorYellow);
			}
		else
			{
			CenterText(130, 16, Move_Entries[5], ColorRed);
			}
		}

	}

}


// ******************************************************************************************


// Shake dualshock when reaching certain frames.

void Check_Rumble_Frame(void)
{

if ( (Game_Config.Vibration == YES) && (PadGetState(0x00) == 6) && (STRCurrentFrame == Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->RumbleFrame) && (Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->RumbleType != NULL) )
	{
	Rumble_Motor[Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->RumbleType-1].motor();
	}


else if ( (Game_Config.Vibration == YES) && (PadGetState(0x00) == 6) )
	{
	switch(Game_Stages[Player1.CurrentStage].ID)
		{

// Gate slams before main hall.

		case 1:

		if (STRCurrentFrame == 235)
			{
			Rumble_Motor[MEDIUM_RUMBLE-1].motor();
			}

		else if (STRCurrentFrame == 247)
			{
			Rumble_Motor[MEDIUM_RUMBLE-1].motor();
			}

		break;

// Smithee.
		case 9:
		case 22:

		if (STRCurrentFrame == 189)
			{
			Rumble_Motor[LOW_RUMBLE-1].motor();
			}

		else if (STRCurrentFrame == 260)
			{
			Rumble_Motor[SMALL_RUMBLE-1].motor();
			}

		break;

// Flying horse.
		case 14:
		case 23:

		if (STRCurrentFrame == 201)
			{
			Rumble_Motor[MEDIUM_RUMBLE-1].motor();
			}

		else if (STRCurrentFrame == 232)
			{
			Rumble_Motor[LOW_RUMBLE-1].motor();
			}
		break;

// Black armor knight.
		case 15:
		case 30:

		if (STRCurrentFrame == 249)
			{
			Rumble_Motor[SMALL_RUMBLE-1].motor();
			}

		break;

// Crypt keepers.
		case 16:
		case 26:

		if (STRCurrentFrame == 185)
			{
			Rumble_Motor[SMALL_RUMBLE-1].motor();
			}

		break;

// Elevator.
		case 21:
		case 31:

		if (STRCurrentFrame == 235)
			{
			Rumble_Motor[BIG_RUMBLE-1].motor();
			}

		break;

// River.

		case 32:

		if (STRCurrentFrame == 555)
			{
			Rumble_Motor[LOW_RUMBLE-1].motor();
			}

		else if (STRCurrentFrame == 572)
			{
			Rumble_Motor[MEDIUM_RUMBLE-1].motor();
			}

		break;

// Dragon's lair.

		case 38:

		if (STRCurrentFrame == 966)
			{
			Rumble_Motor[BIG_RUMBLE-1].motor();
			}

		else if (STRCurrentFrame == 1061)
			{
			Rumble_Motor[MEDIUM_RUMBLE-1].motor();
			}

		else if (STRCurrentFrame == 1093)
			{
			Rumble_Motor[LOW_RUMBLE-1].motor();
			}

		break;

		}
	}
}


// ******************************************************************************************


// Handle pad input during intro movie.

void Interactions_Intro(void) {

if (Pad1.Start == TAP_BUTTON || Pad1.Sword == TAP_BUTTON)
	{
	PlaySound(SFXConfirm);
	StopPlayingMovie = YES;
	}
}


// ******************************************************************************************


// Pad input during death, Dirk and exit movies.

void Interactions_Additional_Movie(void) {

if (Game_Status == STATUS_DIRK)
	{
	Print_Lives();
	if (Game_Config.Vibration == YES && Player1.Pause == NO && STRCurrentFrame == 30 && Big_Motor.Duration == 0 && PadGetState(0x00) == 6)
	{
	DS_Low_Rumble();
	}
	}

//else if (Game_Config.Vibration == YES && Player1.Pause == NO && STRCurrentFrame == 2 && Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction]->Type == MOVIE_DEATH && Big_Motor.Duration == 0 && PadGetState(0x00) == 6)

else if (Game_Status == STATUS_DEATH && Game_Config.Vibration == YES && Player1.Pause == NO && STRCurrentFrame == 2 && Big_Motor.Duration == 0 && PadGetState(0x00) == 6)
	{
	DS_Medium_Rumble();
	}

// Quit game and return to title screen.
if ( Pressed(START_KEY) && Pressed(SELECT_KEY) )
	{
	PlaySound(SFXWrong);
	StopPlayingMovie = YES;
	Init_Status(STATUS_TITLE);
	}


// Pause mode prompt.
if ( Player1.Pause == YES)
	{
	Show_Pause_Screenshot();
	Blinking_Text( TXT_Pause[SelectedLanguage] );
	LoopCount++;
	}

// Toggle pause mode.
if ( Pad1.Start == TAP_BUTTON && ( STRCurrentFrame > 1 ) && ( STRCurrentFrame < Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction]->Frames-1 )) // To prevent the game from crashing when pausing during last frame.
	{
	Switch_Pause_Mode();
	}

}


// ******************************************************************************************


// In certain stages pressing the right button at a specific time skips the movie to a later position.

void Check_Skippable_Scene(void)
{

if ( (Game_Stages[Player1.CurrentStage].ID == 10) || (Game_Stages[Player1.CurrentStage].ID == 36) )
	{
	if (Pad1.Up == TAP_BUTTON)
		{
		Player1.CurrentAction = ACTION_UP;
		}

	else if (Pad1.Down == TAP_BUTTON)
		{
		Player1.CurrentAction = ACTION_DOWN;
		}

	if (Pad1.Left == TAP_BUTTON)
		{
		Player1.CurrentAction = ACTION_LEFT;
		}

	if (Pad1.Right == TAP_BUTTON)
		{
		Player1.CurrentAction = ACTION_RIGHT;
		}

	if (Pad1.Sword == TAP_BUTTON)
		{
		Player1.CurrentAction = ACTION_SWORD;
		}
	

	switch (Game_Stages[Player1.CurrentStage].ID)
		{

// Grim reaper.
		case 10:

		if ( (STRCurrentFrame >= 105 && STRCurrentFrame <= 110) || (STRCurrentFrame >= 121 && STRCurrentFrame <= 126) || (STRCurrentFrame >= 132 && STRCurrentFrame <= 137) || (STRCurrentFrame >= 142 && STRCurrentFrame <= 147))
			{
			if (Player1.CurrentAction == NO_ACTION)
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					CenterText(16, 16, Move_Entries[1], ColorWhite);
					}
				}
			else if (Player1.CurrentAction == ACTION_UP)
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					CenterText(16, 16, Move_Entries[1], ColorYellow);
					}
				if (Game_Config.Difficulty < HARD_DIFFICULTY)
					{
					PlaySound(SFXCorrect);
					}
				Game_Status = STATUS_GAMEPLAY;
				Player1.InstantDeathFlag = 0;
				Player1.CurrentScene = 1;
				Player1.SkipSceneFlag = 1;
				StopPlayingMovie = 1;
				Player1.CurrentAction = NO_ACTION;
				}
			else
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					CenterText(16, 16, Move_Entries[1], ColorRed);
					}
				}
			}

		break;

// Geyser.
		case 36:

		if ( (STRCurrentFrame >= 65 && STRCurrentFrame <= 70) || (STRCurrentFrame >= 73 && STRCurrentFrame <= 78) )
			{
			if (Player1.CurrentAction == NO_ACTION)
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					CenterText(16, 16, Move_Entries[1], ColorWhite);
					}
				}
			else if (Player1.CurrentAction == ACTION_UP)
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					CenterText(16, 16, Move_Entries[1], ColorYellow);
					}
				if (Game_Config.Difficulty < HARD_DIFFICULTY)
					{
					PlaySound(SFXCorrect);
					}
				Game_Status = STATUS_GAMEPLAY;
				Player1.InstantDeathFlag = 0;
				Player1.CurrentScene = 2;
				Player1.SkipSceneFlag = 1;
				StopPlayingMovie = 1;
				Player1.CurrentAction = NO_ACTION;
				}
			else
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					CenterText(16, 16, Move_Entries[1], ColorRed);
					}
				}
			}

		else if ( (STRCurrentFrame >= 123 && STRCurrentFrame <= 128) || (STRCurrentFrame >= 134 && STRCurrentFrame <= 139) )
			{
			if (Player1.CurrentAction == NO_ACTION)
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					Puts16p(16, 112, Move_Entries[3], ColorWhite);
					}
				}
			else if (Player1.CurrentAction == ACTION_LEFT)
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					Puts16p(16, 112, Move_Entries[3], ColorYellow);
					}
				if (Game_Config.Difficulty < HARD_DIFFICULTY)
					{
					PlaySound(SFXCorrect);
					}
				Game_Status = STATUS_GAMEPLAY;
				Player1.InstantDeathFlag = 0;
				Player1.CurrentScene = 3;
				Player1.SkipSceneFlag = 2;
				StopPlayingMovie = 1;
				Player1.CurrentAction = NO_ACTION;
				}
			else
				{
				if ( Game_Config.Difficulty == EASY_DIFFICULTY )
					{
					Puts16p(16, 112, Move_Entries[3], ColorRed);
					}
				}
			}
		break;

		}
	}

}


// ******************************************************************************************

// In some scenes, pressing some buttons out of time leads to an instant death.

void Check_Instant_Death(void)
{
short i;

if (Game_Stages[Player1.CurrentStage].InstantDeath == YES)
	{
//	FntPrint(fIdA, "%d Stage has %d instant death scenes. ID: %d", STRCurrentFrame, Game_Stages[Player1.CurrentStage].InstantDeathScenes, Game_Stages[Player1.CurrentStage].ID);

	for (i=0; i<Game_Stages[Player1.CurrentStage].InstantDeathScenes; i++)
		{
		if (STRCurrentFrame >= CurrentInstantDeathScene[i].StartingFrame && STRCurrentFrame <= CurrentInstantDeathScene[i].EndingFrame)
			{
//	FntPrint(fIdA, " \nInside instant death loop. %d-%d", CurrentInstantDeathScene[0].StartingFrame, CurrentInstantDeathScene[0].EndingFrame);

			if (Pad1.Up == TAP_BUTTON && CurrentInstantDeathScene[i].Movie[1] != KEEP_PLAYING)
				{
				Game_Status = STATUS_DEATH;
				Player1.InstantDeathFlag = 1;
				DeathMovie = CurrentInstantDeathScene[i].Movie[1];
				StopPlayingMovie = YES;
				return;
				}

			else if (Pad1.Down == TAP_BUTTON && CurrentInstantDeathScene[i].Movie[2] != KEEP_PLAYING)
				{
				Game_Status = STATUS_DEATH;
				Player1.InstantDeathFlag = 1;
				DeathMovie = CurrentInstantDeathScene[i].Movie[2];
				StopPlayingMovie = YES;
				return;
				}

			else if (Pad1.Left == TAP_BUTTON && CurrentInstantDeathScene[i].Movie[3] != KEEP_PLAYING)
				{
				Game_Status = STATUS_DEATH;
				Player1.InstantDeathFlag = 1;
				DeathMovie = CurrentInstantDeathScene[i].Movie[3];
				StopPlayingMovie = YES;
				return;
				}

			else if (Pad1.Right == TAP_BUTTON && CurrentInstantDeathScene[i].Movie[4] != KEEP_PLAYING)
				{
				Game_Status = STATUS_DEATH;
				Player1.InstantDeathFlag = 1;
				DeathMovie = CurrentInstantDeathScene[i].Movie[4];
				StopPlayingMovie = YES;
				return;
				}

			else if (Pad1.Sword == TAP_BUTTON && CurrentInstantDeathScene[i].Movie[5] != KEEP_PLAYING)
				{
				Game_Status = STATUS_DEATH;
				Player1.InstantDeathFlag = 1;
				DeathMovie = CurrentInstantDeathScene[i].Movie[5];
				StopPlayingMovie = YES;
				return;
				}
			}
		}
//	FntFlush(fIdA);
	}

}


// ******************************************************************************************


// Pad input for actual gameplay.

void Interactions_Gameplay(void) {

// Quit game and return to title screen.
if ( Pressed(START_KEY) && Pressed(SELECT_KEY) )
	{
	PlaySound(SFXWrong);
	StopPlayingMovie = YES;
	Init_Status(STATUS_TITLE);
	return;
	}

// Pause mode prompt.
if ( Player1.Pause )
	{
	Show_Pause_Screenshot();
	Blinking_Text( TXT_Pause[SelectedLanguage] );
	LoopCount++;
// Display debug menu when enabled.
	if (Debug_Config.Debug_Mode == YES)
		{
		InGame_Debug_Menu();
		}
	}
// Actual gameplay.
else
	{
// Update checkpoint value.
	if ( ( STRCurrentFrame > Game_Stages[Player1.CurrentStage].Checkpoint ) && ( Game_Stages[Player1.CurrentStage].Checkpoint > 0) && ( Player1.CurrentCheckpoint < 1 ) && ( Game_Config.Difficulty != HARD_DIFFICULTY ) )
		{
		Player1.CurrentCheckpoint++;
		}

// Update scene index when correct move is performed or play death/exit animation.

	if ( ( STRCurrentFrame > ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Frame + Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Time) || (STRCurrentFrame >= Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene + 1]->Frame) && (Player1.CurrentScene+1 < Game_Stages[Player1.CurrentStage].TotalScenes) ) && Player1.CurrentScene <= Game_Stages[Player1.CurrentStage].TotalScenes )
		{
// Correct move.
		if ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction] == KEEP_PLAYING )
			{
			Player1.CurrentScene++;
			Player1.CurrentAction = NO_ACTION; // Update status to no button pressed.
			}
		else
// Wrong move or alternate path.
			{
			StopPlayingMovie = YES;
			if ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction]->Type == MOVIE_DEATH )
				{
				Game_Status = STATUS_DEATH;
				}

			else if ( Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Movie[Player1.CurrentAction]->Type == MOVIE_ALT_EXIT )
				{
				Game_Status = STATUS_ALT_EXIT;
				}
			}
		}

	else if ( ( STRCurrentFrame >= Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Frame ) && ( STRCurrentFrame < Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Frame + Game_Stages[Player1.CurrentStage].Scene[Player1.CurrentScene]->Time) )
		{
// Display hints on easy mode.
		Display_Hints();

// Check and update action performed.
		if (Pad1.Up == TAP_BUTTON)
			{
			Player1.CurrentAction = ACTION_UP;
			Decide_SFX();
			}

		else if (Pad1.Down == TAP_BUTTON)
			{
			Player1.CurrentAction = ACTION_DOWN;
			Decide_SFX();
			}

		else if (Pad1.Left == TAP_BUTTON)
			{
			Player1.CurrentAction = ACTION_LEFT;
			Decide_SFX();
			}

		else if (Pad1.Right == TAP_BUTTON)
			{
			Player1.CurrentAction = ACTION_RIGHT;
			Decide_SFX();
			}

		else if (Pad1.Sword == TAP_BUTTON)
			{
			Player1.CurrentAction = ACTION_SWORD;
			Decide_SFX();
			}
		}


	Check_Instant_Death();

	Check_Skippable_Scene();

	Check_Rumble_Frame();
	} // end else if Player1.Pause


// Display debug info.
if (Debug_Config.Debug_Mode == YES)
	{
	if (Debug_Config.Debug_Info == YES)
		{
		Print_Debug_Info();
		}
	if (Pad1.Select == TAP_BUTTON)
		{
		Debug_Config.Debug_Info ^= 1;
		}
	}

// Toggle pause mode.
if (Pad1.Start == TAP_BUTTON)
	{
	Switch_Pause_Mode();
	}

}


// ******************************************************************************************


// Handle pad input while testing movies in debug menu.

void Interactions_DebugMenu(void) {


// Blinking text while in pause mode.
if ( Player1.Pause == YES)
	{
	Show_Pause_Screenshot();
	Blinking_Text( TXT_Pause[SelectedLanguage] );
	LoopCount++;
	}

// Print frame number.
if (Debug_Config.Debug_Mode == YES)
	{
	FntPrint(fIdA, "\n\n  FRAME: %d", STRCurrentFrame);

	FntFlush(fIdA);
	}

// Pause.
if (Pad1.Start == TAP_BUTTON)
	{
	Switch_Pause_Mode();
	}

// Quit movie.
if (Pad1.Sword == TAP_BUTTON)
	{
	PlaySound(SFXConfirm);
	StopPlayingMovie = YES;
	}
}



// ******************************************************************************************


// Handle pad input while watching movies in hidden option.

void Interactions_WatchMovies(void) {


// Blinking text while in pause mode.
if ( Player1.Pause )
	{
	Show_Pause_Screenshot();
	Blinking_Text( TXT_Pause[SelectedLanguage] );
	LoopCount++;
	}

// Pause.
if (Pad1.Start == TAP_BUTTON)
	{
	Switch_Pause_Mode();
	}

// Next movie.
if (Pad1.Sword == TAP_BUTTON && !(Player1.Pause) )
	{
	StopPlayingMovie = YES;
	}

// Quit movie player.
if ( Pressed(START_KEY) && Pressed(SELECT_KEY) )
	{
	StopPlayingMovie = YES;
	MovieIndex = MAX_STAGES;
	}
}

// ******************************************************************************************

// Hidden option for watching stage movies in sequence.

void Watch_Movies(void)
{

Shuffle_Stages();

for (MovieIndex=0; MovieIndex<MAX_STAGES; MovieIndex++)
	{
	PlayStream(Game_Stages[MovieIndex].Movie, 0);
	}

Init_Status(STATUS_TITLE);

}


// ******************************************************************************************


// We should never see this screen.

void Error_Screen(void)
{
FntPrint(fIdA, "\n\n~c990%s", ErrorType[Error_Report.ErrorID]);
FntPrint(fIdA, "\n\n~c990File: %s", Error_Report.File);
FntPrint(fIdA, "\n\n~c990Function: %s", Error_Report.Function);
FntPrint(fIdA, "\n\n~c990Line: %d", Error_Report.Line);
FntPrint(fIdA, "\n\n~c990Error code: %d", _get_errno());
FntPrint(fIdA, "\n\n~c990Last STR Frame: %d", STRCurrentFrame);
FntPrint(fIdA, "\n\n\n\n\n~c990	Press start to retry.\n	Press select for disc test.");

FntFlush(fIdA);

if (Pad1.Start == TAP_BUTTON)
	{
	Game_Status = Prev_Game_Status;
	Init_Status(Prev_Game_Status);

// Init report values in case of unexpected error.
	Error_Report.ErrorID = NULL;
	strcpy(Error_Report.File, NULL);
	strcpy(Error_Report.Function, NULL);
	Error_Report.Line = NULL;
	}

if (Pad1.Select == TAP_BUTTON)
	{
	Game_Status = STATUS_VERIFY;
	Init_Status(Game_Status);

// Init report values in case of unexpected error.
	Error_Report.ErrorID = NULL;
	strcpy(Error_Report.File, NULL);
	strcpy(Error_Report.Function, NULL);
	Error_Report.Line = NULL;
	}

}


