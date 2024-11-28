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

#define MAIN_C

#include "main.h"
#include "game.h"

//----------------------------------------------------------------------------


DB db[2];		

short cdb = 0; // Current double buffer.


//----------------------------------------------------------------------------

// Main core. Actual game code is inside GAME.C

int main(void) {


	InitSys();
	InitEnvs(db);
	

	PutDispEnv(&db[cdb].disp);
	SetDispMask(1);

// Holding down SELECT button while loading launches the PAL version.
#ifdef NTSC
	Trigger_PAL_Version();
#endif

	while (1)
		{
// This prevents blank frames when switching between movies.
		if ( ( Game_Status != STATUS_GAMEPLAY ) && ( Game_Status != STATUS_DEATH ) && ( Game_Status != STATUS_DIRK ) )
			{
			cdb ^= 1;
			}

		switch(Game_Status)
			{
			case STATUS_LOADING:
				Loading_Screen();
			break;

			case STATUS_FADEOUT:
				FadeOut();
			break;

			case STATUS_LANGUAGE_SELECTION:
				Language_Selection(); // BS movie.
			break;

			case STATUS_INTRO_MOVIE:
				Play_Intro(); // STR movie.
			break;

			case STATUS_TITLE:
				Title_Screen(); // BS movie.
			break;

			case STATUS_GAMEPLAY:
				Play_Stage(); // STR movie.
			break;

			case STATUS_DEATH:
				Play_Death(); // STR movie.
			break;

			case STATUS_DIRK:
				Play_DirkMovie(); // STR movie.
			break;

			case STATUS_CONTINUE:
				Continue_Screen(); // BS movie.
			break;

			case STATUS_GAMEOVER:
				GameOver_Screen(); // BS movie.
			break;

			case STATUS_ENDING:
				Ending_Screen(); // BS movie.
			break;

			case STATUS_CREDITS:
				Credits_Roll(); // BS movie.
			break;

			case STATUS_SECRET:
				Play_Secret(); // STR movie.
			break;

			case STATUS_WATCHMOVIES:
				Watch_Movies(); // STR movie.
			break;

			case STATUS_DEBUGMENU:
				Debug_Menu();
			break;

			case STATUS_VERIFY:
				Verify_Screen();
			break;

			case STATUS_PADTEST:
				Pad_Test();
			break;

			default:
				Error_Screen();
			}

// Same as above. Workaround to avoid blank frames between end and start of next movie.
		if ( ( Game_Status != STATUS_GAMEPLAY ) && ( Game_Status != STATUS_DEATH ) && ( Game_Status != STATUS_DIRK ) )
			{
			DrawSync(0);
			VSync(0);

			PutDrawEnv(&db[cdb].draw);
			PutDispEnv(&db[cdb].disp);

			LoopCount++;

// Pad input processing.
			CheckButtons();

			}
		}
	
	
	CloseSys();		
	return 0;
}




