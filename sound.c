#define SOUND_C
#include "options.h"
#include "sound.h"
#include "game.h"

void PlaySound(SoundSample Sample)
{

// Disable beeps in hard difficulty.
if (SoundEffects >= 0 && Game_Config.Difficulty == HARD_DIFFICULTY && Game_Status == STATUS_GAMEPLAY)
	{
	if ( Sample.SoundNo != 2 && Sample.SoundNo != 3 && Sample.SoundNo != 4)
		{
		SsUtKeyOn(SoundEffects, Sample.SoundNo, 0, Sample.NoteNo, 0, Sample.Volume, Sample.Volume);
		}
	}
// Beeps enabled
else if (SoundEffects >= 0 && Game_Config.Sound == 1)
	{
	SsUtKeyOn(SoundEffects, Sample.SoundNo, 0, Sample.NoteNo, 0, Sample.Volume, Sample.Volume);
	}
// Beeps disabled (hidden option)
else if (Sample.SoundNo != 2 && Sample.SoundNo != 3 && Sample.SoundNo != 4)
	{
	SsUtKeyOn(SoundEffects, Sample.SoundNo, 0, Sample.NoteNo, 0, Sample.Volume, Sample.Volume);
	}
}