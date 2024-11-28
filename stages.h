

//		  Frame No.  Reaction time   No action        Up           Down           Left.         Right.        Sword     RumbleFrame   RumbleStrength


// Stage 1: The drawbridge, main hall.

SCENE Stage1Scene1 = {163, DEFAULT_FRAMES, &STR_Stage1d1, &STR_Stage1d1, &STR_Stage1d1, &STR_Stage1d1, &STR_Stage1d1, KEEP_PLAYING, 142, LOW_RUMBLE};
SCENE Stage1Scene2 = {294, DEFAULT_FRAMES, &STR_Stage1d2, &STR_Stage1d2, &STR_Stage1d2, &STR_Stage1d2, KEEP_PLAYING, &STR_Stage1d2, 292, MEDIUM_RUMBLE};
SCENE Stage1Scene3 = {310, DEFAULT_FRAMES, &STR_Stage1d3, &STR_Stage1d2, &STR_Stage1d3, &STR_Stage1d2, KEEP_PLAYING, &STR_Stage1d3, 319, BIG_RUMBLE};

STAGE Stage1 = {
&STR_Stage1, // First level movie.
&STR_Stage1b, // Dead Dirk movie.
1, // Stage ID.
273, // Checkpoint 1.
YES, // Stage has instant death scenes.
2, // Scenes.
2, // Instant death scenes.
&Stage1Scene1, &Stage1Scene2, &Stage1Scene3
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage1InstantDeathScene1 = {286, 292, KEEP_PLAYING, &STR_Stage1d2, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage1InstantDeathScene2 = {293, 318, KEEP_PLAYING, &STR_Stage1d2, KEEP_PLAYING, &STR_Stage1d2, KEEP_PLAYING, KEEP_PLAYING};


// -------------------------------------------------------------------------------------------

// Stage 2: Green tentacles.

SCENE Stage2Scene1 = {59, DEFAULT_FRAMES, &STR_Stage2d1, &STR_Stage2d1, &STR_Stage2d1, &STR_Stage2d1, &STR_Stage2d1, KEEP_PLAYING, NULL, NULL};
SCENE Stage2Scene2 = {102, DEFAULT_FRAMES, &STR_Stage2d2, KEEP_PLAYING, &STR_Stage2d2, &STR_Stage2d2, &STR_Stage2d2, &STR_Stage2d2, 95, LOW_RUMBLE};
SCENE Stage2Scene3 = {118, DEFAULT_FRAMES, &STR_Stage2d2, &STR_Stage2d2, &STR_Stage2d2, &STR_Stage2d2, KEEP_PLAYING, &STR_Stage2d2, NULL, NULL};
SCENE Stage2Scene4 = {138, DEFAULT_FRAMES, &STR_Stage2d4, &STR_Stage2d4, KEEP_PLAYING, &STR_Stage2d4, &STR_Stage2d4, &STR_Stage2d4, NULL, NULL};
SCENE Stage2Scene5 = {170, DEFAULT_FRAMES, &STR_Stage2d3, &STR_Stage2d3, &STR_Stage2d3, KEEP_PLAYING, &STR_Stage2d3, &STR_Stage2d3, NULL, NULL};
SCENE Stage2Scene6 = {196, DEFAULT_FRAMES, &STR_Stage2d2, KEEP_PLAYING, &STR_Stage2d2, &STR_Stage2d2, &STR_Stage2d2, &STR_Stage2d2, NULL, NULL};

STAGE Stage2 = {
&STR_Stage2, // Second level movie.
&STR_Stage2b, // Dead Dirk movie.
2, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
5, // Scenes.
0, // Instant death scenes.
&Stage2Scene1, &Stage2Scene2, &Stage2Scene3, &Stage2Scene4, &Stage2Scene5, &Stage2Scene6
};


// -------------------------------------------------------------------------------------------


// Stage 3: Snakes.

SCENE Stage3Scene1 = {52, DEFAULT_FRAMES, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, KEEP_PLAYING, 32, LOW_RUMBLE};
SCENE Stage3Scene2 = {73, DEFAULT_FRAMES, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, KEEP_PLAYING, 71, LOW_RUMBLE};
SCENE Stage3Scene3 = {94, 7, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, &STR_Stage3d1, KEEP_PLAYING, 92, LOW_RUMBLE};
SCENE Stage3Scene4 = {105, DEFAULT_FRAMES, &STR_Stage3d1, KEEP_PLAYING, &STR_Stage3d1, &STR_Stage3d1, KEEP_PLAYING, &STR_Stage3d1, NULL, NULL};

STAGE Stage3 = {
&STR_Stage3, // Third level movie.
&STR_Stage3b, // Dead Dirk movie.
3, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
3, // Scenes.
0, // Instant death scenes.
&Stage3Scene1, &Stage3Scene2, &Stage3Scene3, &Stage3Scene4
};


// -------------------------------------------------------------------------------------------

// Stage 4: Ropes in fire room (Right)

SCENE Stage4Scene1 = {83, DEFAULT_FRAMES, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING, &STR_Stage4d2, NULL, NULL};
SCENE Stage4Scene2 = {109, 7, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING, &STR_Stage4d2, NULL, NULL};
SCENE Stage4Scene3 = {132, 7, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING, &STR_Stage4d2, NULL, NULL};
SCENE Stage4Scene4 = {150, 7, &STR_Stage4d1, &STR_Stage4d1, &STR_Stage4d1, &STR_Stage4d1, KEEP_PLAYING, &STR_Stage4d1, NULL, NULL};

STAGE Stage4 = {
&STR_Stage4, // Fourth level movie.
&STR_Stage4b, // Dead Dirk movie.
4, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
3, // Scenes.
4, // Instant death scenes.
&Stage4Scene1, &Stage4Scene2, &Stage4Scene3, &Stage4Scene4
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage4InstantDeathScene1 = {30, 82, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage4InstantDeathScene2 = {94, 108, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage4InstantDeathScene3 = {117, 131, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage4InstantDeathScene4 = {140, 149, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 18: Ropes in fire room (Left)

SCENE Stage18Scene1 = {83, DEFAULT_FRAMES, &STR_Stage18d2, &STR_Stage18d2, &STR_Stage18d2, KEEP_PLAYING, &STR_Stage18d2, &STR_Stage18d2, NULL, NULL};
SCENE Stage18Scene2 = {109, 7, &STR_Stage18d2, &STR_Stage18d2, &STR_Stage18d2, KEEP_PLAYING, &STR_Stage18d2, &STR_Stage18d2, NULL, NULL};
SCENE Stage18Scene3 = {132, 7, &STR_Stage18d2, &STR_Stage18d2, &STR_Stage18d2, KEEP_PLAYING, &STR_Stage18d2, &STR_Stage18d2, NULL, NULL};
SCENE Stage18Scene4 = {150, 7, &STR_Stage18d1, &STR_Stage18d1, &STR_Stage18d1, KEEP_PLAYING, &STR_Stage18d1, &STR_Stage18d1, NULL, NULL};

STAGE Stage18 = {
&STR_Stage18, // Fourth level movie.
&STR_Stage18b, // Dead Dirk movie.
18, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
3, // Scenes.
4, // Instant death scenes.
&Stage18Scene1, &Stage18Scene2, &Stage18Scene3, &Stage18Scene4
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage18InstantDeathScene1 = {30, 82, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage18InstantDeathScene2 = {94, 108, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage18InstantDeathScene3 = {117, 131, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage18InstantDeathScene4 = {140, 149, KEEP_PLAYING, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, &STR_Stage4d2, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 5: Pool and spider.

SCENE Stage5Scene1 = {44, DEFAULT_FRAMES, &STR_Stage5d2, &STR_Stage5d2, &STR_Stage5d2, KEEP_PLAYING, &STR_Stage5d2, &STR_Stage5d2, 48, MEDIUM_RUMBLE};
SCENE Stage5Scene2 = {65, DEFAULT_FRAMES, &STR_Stage5d1, KEEP_PLAYING, &STR_Stage5d1, &STR_Stage5d1, &STR_Stage5d1, &STR_Stage5d1, 73, MEDIUM_RUMBLE};
SCENE Stage5Scene3 = {95, DEFAULT_FRAMES, &STR_Stage5d2, &STR_Stage5d2, &STR_Stage5d2, &STR_Stage5d2, KEEP_PLAYING, &STR_Stage5d2, 95, MEDIUM_RUMBLE};
SCENE Stage5Scene4 = {113, DEFAULT_FRAMES, &STR_Stage5d3, KEEP_PLAYING, &STR_Stage5d3, &STR_Stage5d3, &STR_Stage5d3, &STR_Stage5d3, 120, MEDIUM_RUMBLE};
SCENE Stage5Scene5 = {143, DEFAULT_FRAMES, &STR_Stage5d4, &STR_Stage5d4, &STR_Stage5d4, KEEP_PLAYING, &STR_Stage5d4, &STR_Stage5d4, 133, LOW_RUMBLE};
SCENE Stage5Scene6 = {167, DEFAULT_FRAMES, &STR_Stage5d5, KEEP_PLAYING, &STR_Stage5d5, &STR_Stage5d5, &STR_Stage5d5, &STR_Stage5d5, 177, MEDIUM_RUMBLE};
SCENE Stage5Scene7 = {203, DEFAULT_FRAMES, &STR_Stage5d6, &STR_Stage5d6, &STR_Stage5d6, &STR_Stage5d6, &STR_Stage5d6, KEEP_PLAYING, 203, LOW_RUMBLE};
SCENE Stage5Scene8 = {227, DEFAULT_FRAMES, &STR_Stage5d3, &STR_Stage5d3, &STR_Stage5d3, &STR_Stage5d3, KEEP_PLAYING, &STR_Stage5d3, 227, MEDIUM_RUMBLE};
SCENE Stage5Scene9 = {249, DEFAULT_FRAMES, &STR_Stage5d7, KEEP_PLAYING, &STR_Stage5d7, &STR_Stage5d7, &STR_Stage5d7, &STR_Stage5d7, 238, LOW_RUMBLE};

STAGE Stage5 = {
&STR_Stage5, // Fifth level movie.
&STR_Stage5b, // Dead Dirk movie.
5, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
8, // Scenes.
0, // Instant death scenes.
&Stage5Scene1, &Stage5Scene2, &Stage5Scene3, &Stage5Scene4, &Stage5Scene5, &Stage5Scene6, &Stage5Scene7, &Stage5Scene8, &Stage5Scene9
};

// -------------------------------------------------------------------------------------------

// Stage 19: Pool and spider (mirrored).

SCENE Stage19Scene1 = {44, DEFAULT_FRAMES, &STR_Stage19d2, &STR_Stage19d2, &STR_Stage19d2, &STR_Stage19d2, KEEP_PLAYING, &STR_Stage19d2, 48, MEDIUM_RUMBLE};
SCENE Stage19Scene2 = {65, DEFAULT_FRAMES, &STR_Stage19d1, KEEP_PLAYING, &STR_Stage19d1, &STR_Stage19d1, &STR_Stage19d1, &STR_Stage19d1, 73, MEDIUM_RUMBLE};
SCENE Stage19Scene3 = {95, DEFAULT_FRAMES, &STR_Stage19d2, &STR_Stage19d2, &STR_Stage19d2, KEEP_PLAYING, &STR_Stage19d2, &STR_Stage19d2, 95, MEDIUM_RUMBLE};
SCENE Stage19Scene4 = {113, DEFAULT_FRAMES, &STR_Stage19d3, KEEP_PLAYING, &STR_Stage19d3, &STR_Stage19d3, &STR_Stage19d3, &STR_Stage19d3, 120, MEDIUM_RUMBLE};
SCENE Stage19Scene5 = {143, DEFAULT_FRAMES, &STR_Stage19d4, &STR_Stage19d4, &STR_Stage19d4, &STR_Stage19d4, KEEP_PLAYING, &STR_Stage19d4, 133, LOW_RUMBLE};
SCENE Stage19Scene6 = {167, DEFAULT_FRAMES, &STR_Stage19d5, KEEP_PLAYING, &STR_Stage19d5, &STR_Stage19d5, &STR_Stage19d5, &STR_Stage19d5, 177, MEDIUM_RUMBLE};
SCENE Stage19Scene7 = {203, DEFAULT_FRAMES, &STR_Stage19d6, &STR_Stage19d6, &STR_Stage19d6, &STR_Stage19d6, &STR_Stage19d6, KEEP_PLAYING, 203, LOW_RUMBLE};
SCENE Stage19Scene8 = {227, DEFAULT_FRAMES, &STR_Stage19d3, &STR_Stage19d3, &STR_Stage19d3, KEEP_PLAYING, &STR_Stage19d3, &STR_Stage19d3, 227, MEDIUM_RUMBLE};
SCENE Stage19Scene9 = {249, DEFAULT_FRAMES, &STR_Stage19d7, KEEP_PLAYING, &STR_Stage19d7, &STR_Stage19d7, &STR_Stage19d7, &STR_Stage19d7, 238, LOW_RUMBLE};

STAGE Stage19 = {
&STR_Stage19, // Fifth level movie.
&STR_Stage19b, // Dead Dirk movie.
19, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
8, // Scenes.
0, // Instant death scenes.
&Stage19Scene1, &Stage19Scene2, &Stage19Scene3, &Stage19Scene4, &Stage19Scene5, &Stage19Scene6, &Stage19Scene7, &Stage19Scene8, &Stage19Scene9
};


// -------------------------------------------------------------------------------------------

// Stage 6: Magic cauldron.

SCENE Stage6Scene1 = {50, DEFAULT_FRAMES, &STR_Stage6d2, KEEP_PLAYING, &STR_Stage6d2, &STR_Stage6d2, &STR_Stage6d2, &STR_Stage6d2, 33, LOW_RUMBLE};
SCENE Stage6Scene2 = {82, DEFAULT_FRAMES, &STR_Stage6d1, &STR_Stage6d1, &STR_Stage6d1, &STR_Stage6d1, &STR_Stage6d1, KEEP_PLAYING, 79, SMALL_RUMBLE};
SCENE Stage6Scene3 = {100, DEFAULT_FRAMES, &STR_Stage6d2, &STR_Stage6d2, KEEP_PLAYING, &STR_Stage6d2, &STR_Stage6d2, &STR_Stage6d2, 99, LOW_RUMBLE};
SCENE Stage6Scene4 = {118, DEFAULT_FRAMES, &STR_Stage6d3, &STR_Stage6d3, &STR_Stage6d3, &STR_Stage6d3, &STR_Stage6d3, KEEP_PLAYING, NULL, NULL};
SCENE Stage6Scene5 = {156, DEFAULT_FRAMES, &STR_Stage6d2, &STR_Stage6d2, &STR_Stage6d2, &STR_Stage6d2, KEEP_PLAYING, &STR_Stage6d2, 146, LOW_RUMBLE};

STAGE Stage6 = {
&STR_Stage6, // Sixth level movie.
&STR_Stage6b, // Dead Dirk movie.
6, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
4, // Scenes.
0, // Instant death scenes.
&Stage6Scene1, &Stage6Scene2, &Stage6Scene3, &Stage6Scene4, &Stage6Scene5
};

// -------------------------------------------------------------------------------------------

// Stage 7: Giddy goons.

SCENE Stage7Scene1 = {55, DEFAULT_FRAMES, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage7Scene2 = {84, DEFAULT_FRAMES, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d3, KEEP_PLAYING, &STR_Stage7d2, NULL, NULL};
SCENE Stage7Scene3 = {104, 7, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d2, &STR_Stage7d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage7Scene4 = {134, DEFAULT_FRAMES, &STR_Stage7d1, KEEP_PLAYING, &STR_Stage7d1, &STR_Stage7d1, &STR_Stage7d1, &STR_Stage7d1, NULL, NULL};

STAGE Stage7 = {
&STR_Stage7, // Seventh level movie.
&STR_Stage7b, // Dead Dirk movie.
7, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
3, // Scenes.
1, // Instant death scenes.
&Stage7Scene1, &Stage7Scene2, &Stage7Scene3, &Stage7Scene4
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage7InstantDeathScene1 = {94, 112, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage7d1, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 8: Tricky stairs and pink tentacles.

SCENE Stage8Scene1 = {65, DEFAULT_FRAMES, &STR_Stage8d1, &STR_Stage8d1, &STR_Stage8d1, KEEP_PLAYING, &STR_Stage8d1, &STR_Stage8d1, 71, LOW_RUMBLE};
SCENE Stage8Scene2 = {97, DEFAULT_FRAMES, &STR_Stage8d2, &STR_Stage8d2, &STR_Stage8d2, &STR_Stage8d2, &STR_Stage8d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage8Scene3 = {117, 7, &STR_Stage8d2, &STR_Stage8d2, &STR_Stage8d1, KEEP_PLAYING, &STR_Stage8d2, &STR_Stage8d2, 111, LOW_RUMBLE};
SCENE Stage8Scene4 = {150, 8, &STR_Stage8d1, &STR_Stage8d3, &STR_Stage8d1, KEEP_PLAYING, &STR_Stage8d1, &STR_Stage8d1, 152, LOW_RUMBLE};

STAGE Stage8 = {
&STR_Stage8, // Eighth level movie.
&STR_Stage8b, // Dead Dirk movie.
8, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
3, // Scenes.
0, // Instant death scenes.
&Stage8Scene1, &Stage8Scene2, &Stage8Scene3, &Stage8Scene4
};

// -------------------------------------------------------------------------------------------

// Stage 9: The smithee.

SCENE Stage9Scene1 = {70, DEFAULT_FRAMES, &STR_Stage9d2, &STR_Stage9d2, &STR_Stage9d2, &STR_Stage9d2, &STR_Stage9d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage9Scene2 = {100, DEFAULT_FRAMES, &STR_Stage9d3, &STR_Stage9d3, &STR_Stage9d3, &STR_Stage9d3, &STR_Stage9d3, KEEP_PLAYING, 85, SMALL_RUMBLE};
SCENE Stage9Scene3 = {128, DEFAULT_FRAMES, &STR_Stage9d4, &STR_Stage9d4, &STR_Stage9d4, KEEP_PLAYING, &STR_Stage9d4, &STR_Stage9d4, 114, SMALL_RUMBLE};
SCENE Stage9Scene4 = {156, DEFAULT_FRAMES, &STR_Stage9d5, &STR_Stage9d5, &STR_Stage9d5, &STR_Stage9d5, &STR_Stage9d5, KEEP_PLAYING, NULL, NULL};
SCENE Stage9Scene5 = {230, DEFAULT_FRAMES, &STR_Stage9d6, &STR_Stage9d6, &STR_Stage9d6, &STR_Stage9d6, &STR_Stage9d6, KEEP_PLAYING, 169, SMALL_RUMBLE};

STAGE Stage9 = {
&STR_Stage9, // Ninth level movie.
&STR_Stage9b, // Dead Dirk movie.
9, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
4, // Scenes.
4, // Instant death scenes.
&Stage9Scene1, &Stage9Scene2, &Stage9Scene3, &Stage9Scene4, &Stage9Scene5
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage9InstantDeathScene1 = {29, 69, KEEP_PLAYING, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d2};
INSTANT_DEATH_SCENE Stage9InstantDeathScene2 = {88, 99, KEEP_PLAYING, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d3};
INSTANT_DEATH_SCENE Stage9InstantDeathScene3 = {123, 146, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage9d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage9InstantDeathScene4 = {147, 155, KEEP_PLAYING, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d1, &STR_Stage9d5};

// -------------------------------------------------------------------------------------------

// Stage 22: The smithee (mirrored).

SCENE Stage22Scene1 = {70, DEFAULT_FRAMES, &STR_Stage22d2, &STR_Stage22d2, &STR_Stage22d2, &STR_Stage22d2, &STR_Stage22d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage22Scene2 = {100, DEFAULT_FRAMES, &STR_Stage22d3, &STR_Stage22d3, &STR_Stage22d3, &STR_Stage22d3, &STR_Stage22d3, KEEP_PLAYING, 85, SMALL_RUMBLE};
SCENE Stage22Scene3 = {128, DEFAULT_FRAMES, &STR_Stage22d4, &STR_Stage22d4, &STR_Stage22d4, &STR_Stage22d4, KEEP_PLAYING, &STR_Stage22d4, 114, SMALL_RUMBLE};
SCENE Stage22Scene4 = {156, DEFAULT_FRAMES, &STR_Stage22d5, &STR_Stage22d5, &STR_Stage22d5, &STR_Stage22d5, &STR_Stage22d5, KEEP_PLAYING, NULL, NULL};
SCENE Stage22Scene5 = {230, DEFAULT_FRAMES, &STR_Stage22d6, &STR_Stage22d6, &STR_Stage22d6, &STR_Stage22d6, &STR_Stage22d6, KEEP_PLAYING, 169, SMALL_RUMBLE};

STAGE Stage22 = {
&STR_Stage22, // 22nd level movie.
&STR_Stage22b, // Dead Dirk movie.
22, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
4, // Scenes.
4, // Instant death scenes.
&Stage22Scene1, &Stage22Scene2, &Stage22Scene3, &Stage22Scene4, &Stage22Scene5
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage22InstantDeathScene1 = {29, 69, KEEP_PLAYING, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d2};
INSTANT_DEATH_SCENE Stage22InstantDeathScene2 = {88, 99, KEEP_PLAYING, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d3};
INSTANT_DEATH_SCENE Stage22InstantDeathScene3 = {123, 146, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage22d1, KEEP_PLAYING, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage22InstantDeathScene4 = {147, 155, KEEP_PLAYING, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d1, &STR_Stage22d5};

// -------------------------------------------------------------------------------------------

// Stage 10: Grim reaper.

SCENE Stage10Scene1 = {152, 5, &STR_Stage10d1, KEEP_PLAYING, &STR_Stage10d1, &STR_Stage10d1, &STR_Stage10d1, &STR_Stage10d1, NULL, NULL};// Requires additional coding for skipping to required frame.
SCENE Stage10Scene2 = {190, DEFAULT_FRAMES, &STR_Stage10d2, &STR_Stage10d2, &STR_Stage10d2, &STR_Stage10d2, &STR_Stage10d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage10Scene3 = {228, DEFAULT_FRAMES, &STR_Stage10d3, &STR_Stage10d3, KEEP_PLAYING, &STR_Stage10d3, &STR_Stage10d3, &STR_Stage10d3, 214, SMALL_RUMBLE};
SCENE Stage10Scene4 = {259, DEFAULT_FRAMES, &STR_Stage10d3, KEEP_PLAYING, &STR_Stage10d3, &STR_Stage10d3, &STR_Stage10d3, &STR_Stage10d3, 257, LOW_RUMBLE};

STAGE Stage10 = {
&STR_Stage10, // Tenth level movie.
&STR_Stage10b, // Dead Dirk movie.
10, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
3, // Scenes.
1, // Instant death scenes.
&Stage10Scene1, &Stage10Scene2, &Stage10Scene3, &Stage10Scene4
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage10InstantDeathScene1 = {86, 151, KEEP_PLAYING, &STR_Stage10d1, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING};


// -------------------------------------------------------------------------------------------

// Stage 27: Grim reaper (mirrored), less chances to bypass the trap.

SCENE Stage27Scene1 = {150, DEFAULT_FRAMES, &STR_Stage27d1, KEEP_PLAYING, &STR_Stage27d1, &STR_Stage27d1, &STR_Stage27d1, &STR_Stage27d1, NULL, NULL};// Requires additional coding for skipping to required frame.
SCENE Stage27Scene2 = {192, DEFAULT_FRAMES, &STR_Stage27d2, &STR_Stage27d2, &STR_Stage27d2, &STR_Stage27d2, &STR_Stage27d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage27Scene3 = {228, DEFAULT_FRAMES, &STR_Stage27d3, &STR_Stage27d3, KEEP_PLAYING, &STR_Stage27d3, &STR_Stage27d3, &STR_Stage27d3, 216, SMALL_RUMBLE};
SCENE Stage27Scene4 = {259, DEFAULT_FRAMES, &STR_Stage27d3, KEEP_PLAYING, &STR_Stage27d3, &STR_Stage27d3, &STR_Stage27d3, &STR_Stage27d3, 259, LOW_RUMBLE};

STAGE Stage27 = {
&STR_Stage27, // 27th level movie.
&STR_Stage27b, // Dead Dirk movie.
27, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
3, // Scenes.
1, // Instant death scenes.
&Stage27Scene1, &Stage27Scene2, &Stage27Scene3, &Stage27Scene4
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage27InstantDeathScene1 = {86, 149, KEEP_PLAYING, &STR_Stage27d1, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

//Stage 11: Windy room.

SCENE Stage11Scene1 = {117, DEFAULT_FRAMES, &STR_Stage11d1, &STR_Stage11d1, &STR_Stage11d1, &STR_Stage11d1, KEEP_PLAYING, &STR_Stage11d1, 81, MEDIUM_RUMBLE};

STAGE Stage11 = {
&STR_Stage11, // 11th level movie.
&STR_Stage11b, // Dead Dirk movie.
11, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
0, // Scenes.
1, // Instant death scenes.
&Stage11Scene1
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage11InstantDeathScene1 = {104, 116, KEEP_PLAYING, &STR_Stage11d1, KEEP_PLAYING, &STR_Stage11d1, KEEP_PLAYING, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 12: Bricked room.

SCENE Stage12Scene1 = {50, DEFAULT_FRAMES, &STR_Stage12d1, KEEP_PLAYING, &STR_Stage12d2, &STR_Stage12d2, &STR_Stage12d2, &STR_Stage12d2, 37, LOW_RUMBLE};

STAGE Stage12 = {
&STR_Stage12, // 12th level movie.
&STR_Stage12b, // Dead Dirk movie.
12, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
0, // Scenes.
0, // Instant death scenes.
&Stage12Scene1
};


// -------------------------------------------------------------------------------------------

// Stage 13: Room on fire.

SCENE Stage13Scene1 = {62, DEFAULT_FRAMES, &STR_Stage13d1, &STR_Stage13d1, &STR_Stage13d1, &STR_Stage13d1, KEEP_PLAYING, &STR_Stage13d1, 44, LOW_RUMBLE};
SCENE Stage13Scene2 = {84, DEFAULT_FRAMES, &STR_Stage13d1, KEEP_PLAYING, &STR_Stage13d1, &STR_Stage13d1, &STR_Stage13d1, &STR_Stage13d1, 86, MEDIUM_RUMBLE};
SCENE Stage13Scene3 = {110, DEFAULT_FRAMES, &STR_Stage13d1, &STR_Stage13d1, KEEP_PLAYING, &STR_Stage13d1, &STR_Stage13d1, &STR_Stage13d1, 109, LOW_RUMBLE};
SCENE Stage13Scene4 = {131, DEFAULT_FRAMES, &STR_Stage13d1, &STR_Stage13d1, &STR_Stage13d1, KEEP_PLAYING, &STR_Stage13d1, &STR_Stage13d1, NULL, NULL};

STAGE Stage13 = {
&STR_Stage13, // 13th level movie.
&STR_Stage13b, // Dead Dirk movie.
13, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
3, // Scenes.
0, // Instant death scenes.
&Stage13Scene1, &Stage13Scene2, &Stage13Scene3, &Stage13Scene4
};


// -------------------------------------------------------------------------------------------

// Stage 14: Horse riding.

SCENE Stage14Scene1 = {74, DEFAULT_FRAMES, &STR_Stage14d3, &STR_Stage14d3, &STR_Stage14d3, &STR_Stage14d3, KEEP_PLAYING, &STR_Stage14d3, 57, MEDIUM_RUMBLE};
SCENE Stage14Scene2 = {92, DEFAULT_FRAMES, &STR_Stage14d3, &STR_Stage14d3, &STR_Stage14d3, KEEP_PLAYING, &STR_Stage14d3, &STR_Stage14d3, NULL, NULL};
SCENE Stage14Scene3 = {113, 8, &STR_Stage14d1, &STR_Stage14d1, &STR_Stage14d1, &STR_Stage14d1, KEEP_PLAYING, &STR_Stage14d1, NULL, NULL};
SCENE Stage14Scene4 = {137, 8, &STR_Stage14d1, &STR_Stage14d1, &STR_Stage14d1, KEEP_PLAYING, &STR_Stage14d1, &STR_Stage14d1, NULL, NULL};
SCENE Stage14Scene5 = {160, 8, &STR_Stage14d2, &STR_Stage14d2, &STR_Stage14d2, KEEP_PLAYING, &STR_Stage14d2, &STR_Stage14d2, NULL, NULL};
SCENE Stage14Scene6 = {177, 8, &STR_Stage14d1, &STR_Stage14d1, &STR_Stage14d1, KEEP_PLAYING, &STR_Stage14d1, &STR_Stage14d1, NULL, NULL};

STAGE Stage14 = {
&STR_Stage14, // 14th level movie.
&STR_Stage14b, // Dead Dirk movie.
14, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
5, // Scenes.
0, // Instant death scenes.
&Stage14Scene1, &Stage14Scene2, &Stage14Scene3, &Stage14Scene4, &Stage14Scene5, &Stage14Scene6
};

// -------------------------------------------------------------------------------------------

// Stage 23: Horse riding (mirrored).

SCENE Stage23Scene1 = {74, DEFAULT_FRAMES, &STR_Stage23d3, &STR_Stage23d3, &STR_Stage23d3, KEEP_PLAYING, &STR_Stage23d3, &STR_Stage23d3, 57, MEDIUM_RUMBLE};
SCENE Stage23Scene2 = {92, DEFAULT_FRAMES, &STR_Stage23d3, &STR_Stage23d3, &STR_Stage23d3, &STR_Stage23d3, KEEP_PLAYING, &STR_Stage23d3, NULL, NULL};
SCENE Stage23Scene3 = {113, 8, &STR_Stage23d1, &STR_Stage23d1, &STR_Stage23d1, KEEP_PLAYING, &STR_Stage23d1, &STR_Stage23d1, NULL, NULL};
SCENE Stage23Scene4 = {137, 8, &STR_Stage23d1, &STR_Stage23d1, &STR_Stage23d1, &STR_Stage23d1, KEEP_PLAYING, &STR_Stage23d1, NULL, NULL};
SCENE Stage23Scene5 = {160, 8, &STR_Stage23d2, &STR_Stage23d2, &STR_Stage23d2, &STR_Stage23d2, KEEP_PLAYING, &STR_Stage23d2, NULL, NULL};
SCENE Stage23Scene6 = {177, 8, &STR_Stage23d1, &STR_Stage23d1, &STR_Stage23d1, &STR_Stage23d1, KEEP_PLAYING, &STR_Stage23d1, NULL, NULL};

STAGE Stage23 = {
&STR_Stage23, // 14th level movie.
&STR_Stage23b, // Dead Dirk movie.
23, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
5, // Scenes.
0, // Instant death scenes.
&Stage23Scene1, &Stage23Scene2, &Stage23Scene3, &Stage23Scene4, &Stage23Scene5, &Stage23Scene6
};

// -------------------------------------------------------------------------------------------

// Stage 15: Checkered floor and black armor knight.

SCENE Stage15Scene1 = {72, DEFAULT_FRAMES, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, KEEP_PLAYING, &STR_Stage15d1, NULL, NULL};
SCENE Stage15Scene2 = {90, DEFAULT_FRAMES, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, KEEP_PLAYING, &STR_Stage15d1, &STR_Stage15d1, NULL, NULL};
SCENE Stage15Scene3 = {109, 8, &STR_Stage15d1, KEEP_PLAYING, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, NULL, NULL};
SCENE Stage15Scene4 = {134, DEFAULT_FRAMES, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, KEEP_PLAYING, &STR_Stage15d1, &STR_Stage15d1, NULL, NULL};
SCENE Stage15Scene5 = {157, DEFAULT_FRAMES, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, KEEP_PLAYING, &STR_Stage15d1, NULL, NULL};
SCENE Stage15Scene6 = {174, 8, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, KEEP_PLAYING, &STR_Stage15d1, &STR_Stage15d1, NULL, NULL};
SCENE Stage15Scene7 = {184, 8, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, &STR_Stage15d1, KEEP_PLAYING, &STR_Stage15d1, NULL, NULL};
SCENE Stage15Scene8 = {212, DEFAULT_FRAMES, &STR_Stage15d2, &STR_Stage15d2, &STR_Stage15d2, &STR_Stage15d2, &STR_Stage15d2, KEEP_PLAYING, NULL, NULL};

STAGE Stage15 = {
&STR_Stage15, // 15th level movie.
&STR_Stage15b, // Dead Dirk movie.
15, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
7, // Scenes.
0, // Instant death scenes.
&Stage15Scene1, &Stage15Scene2, &Stage15Scene3, &Stage15Scene4, &Stage15Scene5, &Stage15Scene6, &Stage15Scene7, &Stage15Scene8
};


// -------------------------------------------------------------------------------------------

// Stage 30: Checkered floor and black armor knight (mirrored).

SCENE Stage30Scene1 = {72, DEFAULT_FRAMES, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, KEEP_PLAYING, &STR_Stage30d1, &STR_Stage30d1, NULL, NULL};
SCENE Stage30Scene2 = {90, DEFAULT_FRAMES, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, KEEP_PLAYING, &STR_Stage30d1, NULL, NULL};
SCENE Stage30Scene3 = {109, 8, &STR_Stage30d1, KEEP_PLAYING, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, NULL, NULL};
SCENE Stage30Scene4 = {134, DEFAULT_FRAMES, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, KEEP_PLAYING, &STR_Stage30d1, NULL, NULL};
SCENE Stage30Scene5 = {157, DEFAULT_FRAMES, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, KEEP_PLAYING, &STR_Stage30d1, &STR_Stage30d1, NULL, NULL};
SCENE Stage30Scene6 = {174, 8, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, KEEP_PLAYING, &STR_Stage30d1, NULL, NULL};
SCENE Stage30Scene7 = {184, 8, &STR_Stage30d1, &STR_Stage30d1, &STR_Stage30d1, KEEP_PLAYING, &STR_Stage30d1, &STR_Stage30d1, NULL, NULL};
SCENE Stage30Scene8 = {212, DEFAULT_FRAMES, &STR_Stage30d2, &STR_Stage30d2, &STR_Stage30d2, &STR_Stage30d2, &STR_Stage30d2, KEEP_PLAYING, NULL, NULL};

STAGE Stage30 = {
&STR_Stage30, // 15th level movie.
&STR_Stage30b, // Dead Dirk movie.
30, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
7, // Scenes.
0, // Instant death scenes.
&Stage30Scene1, &Stage30Scene2, &Stage30Scene3, &Stage30Scene4, &Stage30Scene5, &Stage30Scene6, &Stage30Scene7, &Stage30Scene8
};

// -------------------------------------------------------------------------------------------

// Stage 16: Crypt keepers.

SCENE Stage16Scene1 = {59, DEFAULT_FRAMES, &STR_Stage16d1, KEEP_PLAYING, &STR_Stage16d1, &STR_Stage16d1, &STR_Stage16d1, &STR_Stage16d1, NULL, NULL};
SCENE Stage16Scene2 = {77, DEFAULT_FRAMES, &STR_Stage16d2, &STR_Stage16d2, &STR_Stage16d2, &STR_Stage16d2, &STR_Stage16d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage16Scene3 = {100, DEFAULT_FRAMES, &STR_Stage16d3, KEEP_PLAYING, &STR_Stage16d3, &STR_Stage16d3, &STR_Stage16d3, &STR_Stage16d3, 91, SMALL_RUMBLE};
SCENE Stage16Scene4 = {119, DEFAULT_FRAMES, &STR_Stage16d2, &STR_Stage16d2, &STR_Stage16d2, &STR_Stage16d2, &STR_Stage16d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage16Scene5 = {138, DEFAULT_FRAMES, &STR_Stage16d3, &STR_Stage16d3, &STR_Stage16d3, KEEP_PLAYING, &STR_Stage16d3, &STR_Stage16d3, 132, SMALL_RUMBLE};
SCENE Stage16Scene6 = {160, DEFAULT_FRAMES, &STR_Stage16d4, &STR_Stage16d4, &STR_Stage16d4, &STR_Stage16d4, &STR_Stage16d4, KEEP_PLAYING, NULL, NULL};

STAGE Stage16 = {
&STR_Stage16, // 16th level movie.
&STR_Stage16b, // Dead Dirk movie.
16, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
5, // Scenes.
0, // Instant death scenes.
&Stage16Scene1, &Stage16Scene2, &Stage16Scene3, &Stage16Scene4, &Stage16Scene5, &Stage16Scene6
};

// -------------------------------------------------------------------------------------------

// Stage 26: Crypt keepers (mirrored).

SCENE Stage26Scene1 = {59, DEFAULT_FRAMES, &STR_Stage26d1, KEEP_PLAYING, &STR_Stage26d1, &STR_Stage26d1, &STR_Stage26d1, &STR_Stage26d1, NULL, NULL};
SCENE Stage26Scene2 = {77, DEFAULT_FRAMES, &STR_Stage26d2, &STR_Stage26d2, &STR_Stage26d2, &STR_Stage26d2, &STR_Stage26d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage26Scene3 = {100, DEFAULT_FRAMES, &STR_Stage26d3, KEEP_PLAYING, &STR_Stage26d3, &STR_Stage26d3, &STR_Stage26d3, &STR_Stage26d3, 91, SMALL_RUMBLE};
SCENE Stage26Scene4 = {119, DEFAULT_FRAMES, &STR_Stage26d2, &STR_Stage26d2, &STR_Stage26d2, &STR_Stage26d2, &STR_Stage26d2, KEEP_PLAYING, NULL, NULL};
SCENE Stage26Scene5 = {138, DEFAULT_FRAMES, &STR_Stage26d3, &STR_Stage26d3, &STR_Stage26d3, &STR_Stage26d3, KEEP_PLAYING, &STR_Stage26d3, 132, SMALL_RUMBLE};
SCENE Stage26Scene6 = {160, DEFAULT_FRAMES, &STR_Stage26d4, &STR_Stage26d4, &STR_Stage26d4, &STR_Stage26d4, &STR_Stage26d4, KEEP_PLAYING, NULL, NULL};

STAGE Stage26 = {
&STR_Stage26, // 26th level movie.
&STR_Stage26b, // Dead Dirk movie.
26, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
5, // Scenes.
0, // Instant death scenes.
&Stage26Scene1, &Stage26Scene2, &Stage26Scene3, &Stage26Scene4, &Stage26Scene5, &Stage26Scene6
};

// -------------------------------------------------------------------------------------------

// Stage 17: Crumbling bridge and bats.

SCENE Stage17Scene1 = {52, DEFAULT_FRAMES, &STR_Stage17d1, KEEP_PLAYING, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, 52, MEDIUM_RUMBLE};
SCENE Stage17Scene2 = {66, DEFAULT_FRAMES, &STR_Stage17d1, KEEP_PLAYING, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, 71, LOW_RUMBLE};
SCENE Stage17Scene3 = {98, 8, &STR_Stage17d2, &STR_Stage17d2, &STR_Stage17d2, &STR_Stage17d2, &STR_Stage17d2, KEEP_PLAYING, 108, MEDIUM_RUMBLE};
SCENE Stage17Scene4 = {113, DEFAULT_FRAMES, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, KEEP_PLAYING, &STR_Stage17d1, NULL, NULL};
SCENE Stage17Scene5 = {133, 8, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, &STR_Stage17d1, KEEP_PLAYING, &STR_Stage17d1, 136, MEDIUM_RUMBLE};

STAGE Stage17 = {
&STR_Stage17, // 17th level movie.
&STR_Stage17b, // Dead Dirk movie.
17, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
4, // Scenes.
0, // Instant death scenes.
&Stage17Scene1, &Stage17Scene2, &Stage17Scene3, &Stage17Scene4, &Stage17Scene5
};

// -------------------------------------------------------------------------------------------

// Stage 20: Giant bat.

SCENE Stage20Scene1 = {48, DEFAULT_FRAMES, &STR_Stage20d2, &STR_Stage20d2, &STR_Stage20d2, &STR_Stage20d2, &STR_Stage20d2, KEEP_PLAYING, 48, LOW_RUMBLE};
SCENE Stage20Scene2 = {72, 8, &STR_Stage20d2, &STR_Stage20d2, &STR_Stage20d2, KEEP_PLAYING, &STR_Stage20d2, &STR_Stage20d2, 74, LOW_RUMBLE};
SCENE Stage20Scene3 = {99, DEFAULT_FRAMES, &STR_Stage20d3, KEEP_PLAYING, &STR_Stage20d3, &STR_Stage20d3, &STR_Stage20d3, &STR_Stage20d3, 100, LOW_RUMBLE};
SCENE Stage20Scene4 = {127, DEFAULT_FRAMES, &STR_Stage20d1, &STR_Stage20d1, &STR_Stage20d1, &STR_Stage20d1, &STR_Stage20d1, KEEP_PLAYING, 132, LOW_RUMBLE};

STAGE Stage20 = {
&STR_Stage20, // 20th level movie.
&STR_Stage20b, // Dead Dirk movie.
20, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
3, // Scenes.
0, // Instant death scenes.
&Stage20Scene1, &Stage20Scene2, &Stage20Scene3, &Stage20Scene4
};


// -------------------------------------------------------------------------------------------

// Stage 21: Elevator.

SCENE Stage21Scene1 = {88, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p2, &STR_Stage21d1, &STR_Stage21d1, 88, LOW_RUMBLE};
SCENE Stage21Scene2 = {96, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p2, &STR_Stage21d1, &STR_Stage21d1, 96, LOW_RUMBLE};
SCENE Stage21Scene3 = {104, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p2, &STR_Stage21d1, &STR_Stage21d1, 104, LOW_RUMBLE};
SCENE Stage21Scene4 = {139, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p1, &STR_Stage21d1, 139, LOW_RUMBLE};
SCENE Stage21Scene5 = {147, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p1, &STR_Stage21d1, 147, LOW_RUMBLE};
SCENE Stage21Scene6 = {155, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p1, &STR_Stage21d1, 155, LOW_RUMBLE};
SCENE Stage21Scene7 = {191, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p2, &STR_Stage21d1, &STR_Stage21d1, 191, LOW_RUMBLE};
SCENE Stage21Scene8 = {199, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p2, &STR_Stage21d1, &STR_Stage21d1, 199, LOW_RUMBLE};
SCENE Stage21Scene9 = {207, 4, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21p2, &STR_Stage21d1, &STR_Stage21d1, 207, LOW_RUMBLE};

STAGE Stage21 = {
&STR_Stage21, // 21st level movie.
&STR_Stage21b, // Dead Dirk movie.
21, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
8, // Scenes.
10, // Instant death scenes.
&Stage21Scene1, &Stage21Scene2, &Stage21Scene3, &Stage21Scene4, &Stage21Scene5, &Stage21Scene6, &Stage21Scene7, &Stage21Scene8, &Stage21Scene9
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage21InstantDeathScene1 = {84, 87, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene2 = {93, 95, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene3 = {101, 103, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene4 = {109, 138, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene5 = {144, 146, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene6 = {152, 154, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene7 = {160, 190, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene8 = {196, 198, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene9 = {204, 206, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage21InstantDeathScene10 = {212, 228, KEEP_PLAYING, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, &STR_Stage21d1, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 31: Elevator (mirrored).

SCENE Stage31Scene1 = {88, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p2, &STR_Stage31d1, 88, LOW_RUMBLE};
SCENE Stage31Scene2 = {96, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p2, &STR_Stage31d1, 96, LOW_RUMBLE};
SCENE Stage31Scene3 = {104, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p2, &STR_Stage31d1, 104, LOW_RUMBLE};
SCENE Stage31Scene4 = {139, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p1, &STR_Stage31d1, &STR_Stage31d1, 139, LOW_RUMBLE};
SCENE Stage31Scene5 = {147, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p1, &STR_Stage31d1, &STR_Stage31d1, 147, LOW_RUMBLE};
SCENE Stage31Scene6 = {155, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p1, &STR_Stage31d1, &STR_Stage31d1, 155, LOW_RUMBLE};
SCENE Stage31Scene7 = {191, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p2, &STR_Stage31d1, 191, LOW_RUMBLE};
SCENE Stage31Scene8 = {199, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p2, &STR_Stage31d1, 199, LOW_RUMBLE};
SCENE Stage31Scene9 = {207, 4, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31p2, &STR_Stage31d1, 207, LOW_RUMBLE};

STAGE Stage31 = {
&STR_Stage31, // 31st level movie.
&STR_Stage31b, // Dead Dirk movie.
31, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
8, // Scenes.
10, // Instant death scenes.
&Stage31Scene1, &Stage31Scene2, &Stage31Scene3, &Stage31Scene4, &Stage31Scene5, &Stage31Scene6, &Stage31Scene7, &Stage31Scene8, &Stage31Scene9
};

// Instant death moves.
INSTANT_DEATH_SCENE Stage31InstantDeathScene1 = {84, 87, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene2 = {93, 95, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene3 = {101, 103, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene4 = {109, 138, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene5 = {144, 146, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene6 = {152, 154, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene7 = {160, 190, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene8 = {196, 198, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene9 = {204, 206, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage31InstantDeathScene10 = {312, 228, KEEP_PLAYING, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, &STR_Stage31d1, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 24: Lizard king.

SCENE Stage24Scene1 = {45, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d2, &STR_Stage24d1, KEEP_PLAYING, &STR_Stage24d1, &STR_Stage24d1, NULL, NULL};
SCENE Stage24Scene2 = {94, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d2, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, &STR_Stage24d1, 56, SMALL_RUMBLE};
SCENE Stage24Scene3 = {137, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d2, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, &STR_Stage24d1, 111, SMALL_RUMBLE};
SCENE Stage24Scene4 = {163, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d2, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, &STR_Stage24d1, 152, SMALL_RUMBLE};
SCENE Stage24Scene5 = {220, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d2, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, &STR_Stage24d1, 179, SMALL_RUMBLE};
SCENE Stage24Scene6 = {246, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d2, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, &STR_Stage24d1, 236, SMALL_RUMBLE};
SCENE Stage24Scene7 = {276, DEFAULT_FRAMES, &STR_Stage24d1, KEEP_PLAYING, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, 263, SMALL_RUMBLE};
SCENE Stage24Scene8 = {296, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, NULL, NULL};
SCENE Stage24Scene9 = {308, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, 310, LOW_RUMBLE};
SCENE Stage24Scene10 = {319, DEFAULT_FRAMES, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, 320, LOW_RUMBLE};
SCENE Stage24Scene11 = {346, 8, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, &STR_Stage24d1, KEEP_PLAYING, 343, LOW_RUMBLE};

STAGE Stage24 = {
&STR_Stage24, // 24th level movie.
&STR_Stage24b, // Dead Dirk movie.
24, // Stage ID.
299, // Checkpoint 1.
NO, // Stage has instant death scenes.
10, // Scenes.
0, // Instant death scenes.
&Stage24Scene1, &Stage24Scene2, &Stage24Scene3, &Stage24Scene4, &Stage24Scene5, &Stage24Scene6, &Stage24Scene7, &Stage24Scene8, &Stage24Scene9, &Stage24Scene10, &Stage24Scene11
};

// -------------------------------------------------------------------------------------------

// Stage25: Flask of poison.

SCENE Stage25Scene1 = {43, DEFAULT_FRAMES, &STR_Stage25d2, &STR_Stage25d1, &STR_Stage25d2, &STR_Stage25d2, KEEP_PLAYING, &STR_Stage25d2, 45, LOW_RUMBLE};

STAGE Stage25 = {
&STR_Stage25, // 25th level movie.
&STR_Stage25b, // Dead Dirk movie.
25, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
0, // Scenes.
0, // Instant death scenes.
&Stage25Scene1
};

// -------------------------------------------------------------------------------------------

// Stage 28: Tilting room.

SCENE Stage28Scene1 = {73, DEFAULT_FRAMES, &STR_Stage28d2, &STR_Stage28d2, KEEP_PLAYING, &STR_Stage28d2, &STR_Stage28d3, &STR_Stage28d2, 49, MEDIUM_RUMBLE};
SCENE Stage28Scene2 = {86, DEFAULT_FRAMES, &STR_Stage28d3, KEEP_PLAYING, &STR_Stage28d3, &STR_Stage28d2, &STR_Stage28d3, &STR_Stage28d3, 92, LOW_RUMBLE};
SCENE Stage28Scene3 = {104, DEFAULT_FRAMES, &STR_Stage28d3, &STR_Stage28d1, &STR_Stage28d3, KEEP_PLAYING, &STR_Stage28d3, &STR_Stage28d3, NULL, NULL};

STAGE Stage28 = {
&STR_Stage28, // 28th level movie.
&STR_Stage28b, // Dead Dirk movie.
28, // Stage ID.
0, // Checkpoint 1.
NO, // Stage has instant death scenes.
2, // Scenes.
0, // Instant death scenes.
&Stage28Scene1, &Stage28Scene2, &Stage28Scene3
};

// -------------------------------------------------------------------------------------------

// Stage 29: Magnetic fields.

SCENE Stage29Scene1 = {52, 9, &STR_Stage29d2, &STR_Stage29d2, &STR_Stage29d2, &STR_Stage29d2, KEEP_PLAYING, &STR_Stage29d1, 45, LOW_RUMBLE};
SCENE Stage29Scene2 = {62, DEFAULT_FRAMES, &STR_Stage29d2, &STR_Stage29d2, &STR_Stage29d2, &STR_Stage29d2, KEEP_PLAYING, &STR_Stage29d1, NULL, NULL};
SCENE Stage29Scene3 = {73, DEFAULT_FRAMES, &STR_Stage29d2, &STR_Stage29d2, &STR_Stage29d2, &STR_Stage29d1, KEEP_PLAYING, &STR_Stage29d1, NULL, NULL};
SCENE Stage29Scene4 = {123, DEFAULT_FRAMES, &STR_Stage29d3, &STR_Stage29d3, &STR_Stage29d3, &STR_Stage29d3, KEEP_PLAYING, &STR_Stage29d3, 86, LOW_RUMBLE};

STAGE Stage29 = {
&STR_Stage29, // 29th level movie.
&STR_Stage29b, // Dead Dirk movie.
29, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
3, // Scenes.
1, // Instant death scenes.
&Stage29Scene1, &Stage29Scene2, &Stage29Scene3, &Stage29Scene4
};

// Instant death scenes.
INSTANT_DEATH_SCENE Stage29InstantDeathScene1 = {48, 82, KEEP_PLAYING, &STR_Stage29d1, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 32: Underground river.

SCENE Stage32Scene1 = {130, DEFAULT_FRAMES, &STR_Stage32d1, &STR_Stage32d1, &STR_Stage32d1, KEEP_PLAYING, &STR_Stage32d1, &STR_Stage32d1, 50, MEDIUM_RUMBLE};
SCENE Stage32Scene2 = {154, DEFAULT_FRAMES, &STR_Stage32d2, &STR_Stage32d2, &STR_Stage32d2, &STR_Stage32d2, KEEP_PLAYING, &STR_Stage32d2, NULL, NULL};
SCENE Stage32Scene3 = {178, DEFAULT_FRAMES, &STR_Stage32d3, &STR_Stage32d3, &STR_Stage32d3, KEEP_PLAYING, &STR_Stage32d3, &STR_Stage32d3, NULL, NULL};
SCENE Stage32Scene4 = {202, DEFAULT_FRAMES, &STR_Stage32d4, &STR_Stage32d4, &STR_Stage32d4, &STR_Stage32d4, KEEP_PLAYING, &STR_Stage32d4, NULL, NULL};
SCENE Stage32Scene5 = {264, DEFAULT_FRAMES, &STR_Stage32d5, KEEP_PLAYING, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, 225, LOW_RUMBLE};
SCENE Stage32Scene6 = {293, DEFAULT_FRAMES, &STR_Stage32d5, KEEP_PLAYING, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, NULL, NULL};
SCENE Stage32Scene7 = {323, DEFAULT_FRAMES, &STR_Stage32d5, KEEP_PLAYING, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, 306, LOW_RUMBLE};
SCENE Stage32Scene8 = {357, DEFAULT_FRAMES, &STR_Stage32d5, KEEP_PLAYING, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, &STR_Stage32d5, 337, LOW_RUMBLE};
SCENE Stage32Scene9 = {426, DEFAULT_FRAMES, &STR_Stage32d6, &STR_Stage32d6, &STR_Stage32d6, &STR_Stage32d6, KEEP_PLAYING, &STR_Stage32d6, 375, LOW_RUMBLE};
SCENE Stage32Scene10 = {457, DEFAULT_FRAMES, &STR_Stage32d6, &STR_Stage32d6, &STR_Stage32d6, KEEP_PLAYING, &STR_Stage32d6, &STR_Stage32d6, 443, SMALL_RUMBLE};
SCENE Stage32Scene11 = {490, DEFAULT_FRAMES, &STR_Stage32d6, &STR_Stage32d6, &STR_Stage32d6, &STR_Stage32d6, KEEP_PLAYING, &STR_Stage32d6, 474, LOW_RUMBLE};
SCENE Stage32Scene12 = {520, DEFAULT_FRAMES, &STR_Stage32d6, &STR_Stage32d6, &STR_Stage32d6, KEEP_PLAYING, &STR_Stage32d6, &STR_Stage32d6, 504, SMALL_RUMBLE};
SCENE Stage32Scene13 = {582, DEFAULT_FRAMES, &STR_Stage32d7, &STR_Stage32d7, &STR_Stage32d7, &STR_Stage32d7, KEEP_PLAYING, &STR_Stage32d7, 537, LOW_RUMBLE};

STAGE Stage32 = {
&STR_Stage32, // 32nd level movie.
&STR_Stage32b, // Dead Dirk movie.
32, // Stage ID.
411, // Checkpoint 1.
NO, // Stage has instant death scenes.
12, // Scenes.
0, // Instant death scenes.
&Stage32Scene1, &Stage32Scene2, &Stage32Scene3, &Stage32Scene4, &Stage32Scene5, &Stage32Scene6, &Stage32Scene7, &Stage32Scene8, &Stage32Scene9, &Stage32Scene10, &Stage32Scene11, &Stage32Scene12, &Stage32Scene13
};

// -------------------------------------------------------------------------------------------

// Stage 33: Mudmen.

SCENE Stage33Scene1 = {89, DEFAULT_FRAMES, &STR_Stage33d4,  &STR_Stage33d1, &STR_Stage33d4, &STR_Stage33d4, &STR_Stage33d4, KEEP_PLAYING, 72, LOW_RUMBLE};
SCENE Stage33Scene2 = {134, DEFAULT_FRAMES, &STR_Stage33d4, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d4, &STR_Stage33d4, &STR_Stage33d4, 120, LOW_RUMBLE};
SCENE Stage33Scene3 = {153, DEFAULT_FRAMES, &STR_Stage33d4, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d5, &STR_Stage33d5, &STR_Stage33d4, NULL, NULL};
SCENE Stage33Scene4 = {177, DEFAULT_FRAMES, &STR_Stage33d4, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d5, &STR_Stage33d5, &STR_Stage33d4, 172, LOW_RUMBLE};
SCENE Stage33Scene5 = {195, DEFAULT_FRAMES, &STR_Stage33d4, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d3, &STR_Stage33d5, &STR_Stage33d4, NULL, NULL};
SCENE Stage33Scene6 = {215, DEFAULT_FRAMES, &STR_Stage33d4, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d3, &STR_Stage33d5, &STR_Stage33d4, NULL, NULL};
SCENE Stage33Scene7 = {245, DEFAULT_FRAMES, &STR_Stage33d2, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d2, &STR_Stage33d2, &STR_Stage33d2, 242, LOW_RUMBLE};
SCENE Stage33Scene8 = {281, DEFAULT_FRAMES, &STR_Stage33d1, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d2, &STR_Stage33d2, &STR_Stage33d1, NULL, NULL};
SCENE Stage33Scene9 = {342, DEFAULT_FRAMES, &STR_Stage33d4, KEEP_PLAYING, &STR_Stage33d5, &STR_Stage33d5, &STR_Stage33d5, &STR_Stage33d4, 302, LOW_RUMBLE};
SCENE Stage33Scene10 = {353, DEFAULT_FRAMES, KEEP_PLAYING, &STR_Stage33d4, &STR_Stage33d5, &STR_Stage33d5, &STR_Stage33d5, &STR_Stage33d4, 361, LOW_RUMBLE};

STAGE Stage33 = {
&STR_Stage33, // 33rd level movie.
&STR_Stage33b, // Dead Dirk movie.
33, // Stage ID.
235, // Checkpoint 1.
NO, // Stage has instant death scenes.
9, // Scenes.
0, // Instant death scenes.
&Stage33Scene1, &Stage33Scene2, &Stage33Scene3, &Stage33Scene4, &Stage33Scene5, &Stage33Scene6, &Stage33Scene7, &Stage33Scene8, &Stage33Scene9, &Stage33Scene10
};


// -------------------------------------------------------------------------------------------

// Stage 34: Black horseman.

SCENE Stage34Scene1 = {30, DEFAULT_FRAMES, &STR_Stage34d2, KEEP_PLAYING, &STR_Stage34d2, &STR_Stage34d2, &STR_Stage34d2, &STR_Stage34d2, 38, SMALL_RUMBLE};
SCENE Stage34Scene2 = {60, DEFAULT_FRAMES, &STR_Stage34d2, &STR_Stage34d2, &STR_Stage34d2, KEEP_PLAYING, &STR_Stage34d2, &STR_Stage34d2, 66, LOW_RUMBLE};
SCENE Stage34Scene3 = {109, DEFAULT_FRAMES, &STR_Stage34d2, &STR_Stage34d2, &STR_Stage34d2, KEEP_PLAYING, &STR_Stage34d2, &STR_Stage34d2, 114, LOW_RUMBLE};
SCENE Stage34Scene4 = {148, DEFAULT_FRAMES, &STR_Stage34d2, &STR_Stage34d2, &STR_Stage34d2, &STR_Stage34d2, KEEP_PLAYING, &STR_Stage34d2, 151, LOW_RUMBLE};

STAGE Stage34 = {
&STR_Stage34, // 34th level movie.
&STR_Stage34b, // Dead Dirk movie.
34, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
3, // Scenes.
3, // Instant death scenes.
&Stage34Scene1, &Stage34Scene2, &Stage34Scene3, &Stage34Scene4
};

INSTANT_DEATH_SCENE Stage34InstantDeathScene1 = {65, 70, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage34d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage34InstantDeathScene2 = {114, 119, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage34d1, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage34InstantDeathScene3 = {151, 158, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage34d1, &STR_Stage34d1, KEEP_PLAYING, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 35: Giant marbles.

SCENE Stage35Scene1 = {91, 8, &STR_Stage35d1, &STR_Stage35d1, KEEP_PLAYING, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d1, NULL, NULL};
SCENE Stage35Scene2 = {115, 8, &STR_Stage35d1, &STR_Stage35d1, KEEP_PLAYING, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d1, 108, LOW_RUMBLE};
SCENE Stage35Scene3 = {139, 8, &STR_Stage35d1, &STR_Stage35d1, KEEP_PLAYING, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d1, 132, SMALL_RUMBLE};
SCENE Stage35Scene4 = {163, 8, &STR_Stage35d1, &STR_Stage35d1, KEEP_PLAYING, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d1, 156, LOW_RUMBLE};
SCENE Stage35Scene5 = {187, 8, &STR_Stage35d1, &STR_Stage35d1, KEEP_PLAYING, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d1, 180, SMALL_RUMBLE};
SCENE Stage35Scene6 = {211, 8, &STR_Stage35d1, &STR_Stage35d1, KEEP_PLAYING, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d1, 204, LOW_RUMBLE};
SCENE Stage35Scene7 = {230, 8, &STR_Stage35d1, KEEP_PLAYING, &STR_Stage35d1, &STR_Stage35d1, &STR_Stage35d1, &STR_Stage35d1, 228, SMALL_RUMBLE};

STAGE Stage35 = {
&STR_Stage35, // 35th level movie.
&STR_Stage35b, // Dead Dirk movie.
35, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
6, // Scenes.
6, // Instant death scenes.
&Stage35Scene1, &Stage35Scene2, &Stage35Scene3, &Stage35Scene4, &Stage35Scene5, &Stage35Scene6, &Stage35Scene7
};

INSTANT_DEATH_SCENE Stage35InstantDeathScene1 = {86, 90, KEEP_PLAYING, &STR_Stage35d1, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage35InstantDeathScene2 = {110, 114, KEEP_PLAYING, &STR_Stage35d1, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage35InstantDeathScene3 = {134, 138, KEEP_PLAYING, &STR_Stage35d1, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage35InstantDeathScene4 = {158, 162, KEEP_PLAYING, &STR_Stage35d1, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage35InstantDeathScene5 = {182, 186, KEEP_PLAYING, &STR_Stage35d1, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d2, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage35InstantDeathScene6 = {206, 210, KEEP_PLAYING, &STR_Stage35d1, &STR_Stage35d2, &STR_Stage35d2, &STR_Stage35d2, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 36: Geyser.

SCENE Stage36Scene1 = {42, DEFAULT_FRAMES, &STR_Stage36d2, KEEP_PLAYING, &STR_Stage36d2, &STR_Stage36d2, &STR_Stage36d2, &STR_Stage36d2, 34, LOW_RUMBLE};
SCENE Stage36Scene2 = {79, 5, &STR_Stage36d1, KEEP_PLAYING, &STR_Stage36d1, &STR_Stage36d1, &STR_Stage36d1, &STR_Stage36d1, 55, LOW_RUMBLE};
SCENE Stage36Scene3 = {145, 5, &STR_Stage36d2, &STR_Stage36d3, &STR_Stage36d3, KEEP_PLAYING, &STR_Stage36d2, &STR_Stage36d3, 105, LOW_RUMBLE};

STAGE Stage36 = {
&STR_Stage36, // 36th level movie.
&STR_Stage36b, // Dead Dirk movie.
36, // Stage ID.
0, // Checkpoint 1.
YES, // Stage has instant death scenes.
2, // Scenes.
4, // Instant death scenes.
&Stage36Scene1, &Stage36Scene2, &Stage36Scene3
};


INSTANT_DEATH_SCENE Stage36InstantDeathScene1 = {63, 64, KEEP_PLAYING, &STR_Stage36d1, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage36InstantDeathScene2 = {71, 72, KEEP_PLAYING, &STR_Stage36d1, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage36InstantDeathScene3 = {116, 122, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage36d3, KEEP_PLAYING, KEEP_PLAYING};
INSTANT_DEATH_SCENE Stage36InstantDeathScene4 = {129, 133, KEEP_PLAYING, KEEP_PLAYING, KEEP_PLAYING, &STR_Stage36d3, KEEP_PLAYING, KEEP_PLAYING};

// -------------------------------------------------------------------------------------------

// Stage 38: Dragon's lair.

SCENE Stage38Scene1 = {78, DEFAULT_FRAMES, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, KEEP_PLAYING, &STR_Stage38d1, &STR_Stage38d1, NULL, NULL};
SCENE Stage38Scene2 = {221, DEFAULT_FRAMES, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, KEEP_PLAYING, &STR_Stage38d1, &STR_Stage38d1, 90, LOW_RUMBLE};
SCENE Stage38Scene3 = {318, DEFAULT_FRAMES, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, KEEP_PLAYING, &STR_Stage38d1, &STR_Stage38d1, NULL, NULL};
SCENE Stage38Scene4 = {591, DEFAULT_FRAMES, &STR_Stage38d2, &STR_Stage38d2, &STR_Stage38d2, KEEP_PLAYING, &STR_Stage38d2, &STR_Stage38d2, 336, LOW_RUMBLE};
SCENE Stage38Scene5 = {635, DEFAULT_FRAMES, &STR_Stage38d1, KEEP_PLAYING, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, 604, MEDIUM_RUMBLE};
SCENE Stage38Scene6 = {677, DEFAULT_FRAMES, &STR_Stage38d5, &STR_Stage38d5, KEEP_PLAYING, &STR_Stage38d5, &STR_Stage38d5, &STR_Stage38d5, NULL, NULL};
SCENE Stage38Scene7 = {736, DEFAULT_FRAMES, &STR_Stage38d1, KEEP_PLAYING, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, 693, BIG_RUMBLE};
SCENE Stage38Scene8 = {745, DEFAULT_FRAMES, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, KEEP_PLAYING, &STR_Stage38d1, NULL, NULL};
SCENE Stage38Scene9 = {788, DEFAULT_FRAMES, &STR_Stage38d3, KEEP_PLAYING, &STR_Stage38d3, &STR_Stage38d3, &STR_Stage38d3, &STR_Stage38d3, 760, LOW_RUMBLE};
SCENE Stage38Scene10 = {806, DEFAULT_FRAMES, &STR_Stage38d3, &STR_Stage38d3, &STR_Stage38d3, &STR_Stage38d3, KEEP_PLAYING, &STR_Stage38d3, NULL, NULL};
SCENE Stage38Scene11 = {826, DEFAULT_FRAMES, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, &STR_Stage38d1, KEEP_PLAYING, NULL, NULL};
SCENE Stage38Scene12 = {850, DEFAULT_FRAMES, &STR_Stage38d4, &STR_Stage38d4, &STR_Stage38d4, &STR_Stage38d4, &STR_Stage38d4, KEEP_PLAYING, 839, LOW_RUMBLE};
SCENE Stage38Scene13 = {896, DEFAULT_FRAMES, &STR_Stage38d6, KEEP_PLAYING, &STR_Stage38d6, &STR_Stage38d6, &STR_Stage38d6, &STR_Stage38d6, 863, LOW_RUMBLE};
SCENE Stage38Scene14 = {910, DEFAULT_FRAMES, &STR_Stage38d4, &STR_Stage38d4, &STR_Stage38d4, &STR_Stage38d4, &STR_Stage38d4, KEEP_PLAYING, 909, LOW_RUMBLE};

STAGE Stage38 = {
&STR_Stage38, // 38th level movie.
&STR_Stage38b, // Dead Dirk movie.
38, // Stage ID.
565, // Checkpoint 1.
NO, // Stage has instant death scenes.
13, // Scenes.
0, // Instant death scenes.
&Stage38Scene1, &Stage38Scene2, &Stage38Scene3, &Stage38Scene4, &Stage38Scene5, &Stage38Scene6, &Stage38Scene7, &Stage38Scene8, &Stage38Scene9, &Stage38Scene10, &Stage38Scene11, &Stage38Scene12, &Stage38Scene13, &Stage38Scene14
};

// -------------------------------------------------------------------------------------------

// Variable for shuffling regular or mirrored levels.

STAGE Game_Stages[MAX_STAGES];

STAGE Current_Stage, Previous_Stage;

//STAGE Default_Stages[MAX_STAGES];

//Comprobar magnetic fields, horseman, 
//En las instant death que pone keep playing se cuelga.
// **** ARREGLADO **** Restaurar las escenas modificadas. Se puede usar la copia del fuente de 31/08.