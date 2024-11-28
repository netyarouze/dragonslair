

typedef struct{
int SoundNo;
int NoteNo;
int Volume;
}SoundSample;

#ifdef SOUND_C

long SoundEffects;

SoundSample SFXTitle = {0, 64, 127};
SoundSample SFXContinue = {1, 64, 127};
SoundSample SFXCorrect = {2, 64, 100};
SoundSample SFXWrong = {3, 64, 100};
SoundSample SFXConfirm = {4, 64, 100};
SoundSample SFXEnd = {5, 64, 127};

extern GAME_OPTIONS Game_Config;

extern short Game_Status;

#else

extern long SoundEffects;

extern SoundSample SFXTitle;
extern SoundSample SFXContinue;
extern SoundSample SFXCorrect;
extern SoundSample SFXWrong;
extern SoundSample SFXConfirm;
extern SoundSample SFXEnd;

#endif