PS Homebrew Dragon's Lair

https://archive.org/details/@qbl


1. What's this?
2. PAL version.
3. Source code.

----------------

1. What's this?

This is a homebrew port of Dragon's Lair for the first PlayStation developed in the year 2024. This is no cancelled beta or leaked prototype. If you see pirates selling "limited editions", "reproductions" or other bootlegs with fancy names, I have nothing to do with them. Please, do not buy illegal copies. Dragon's Lair is still available on many current generation systems, buy a legit copy instead.

This is not a verbatim conversion of the original game. The original binaries were not reverse engineered or anything. The program was coded after figuring out how the game worked so do not expect an accurate adaptation. More details on version differences are explained in the attached manual.

Picture quality could be much better. When converting movies to the PlayStation format, source files should be uncompressed to obtain optimal results. However, in this case, the source video files were already compressed AVI movies from an early Windows 95 port. Playing on an old CRT TV it does not look that bad and enabling scanlines on emulators improves the quality a bit.

----------------

2. PAL version.

The game runs in NTSC video mode by default. Most PAL systems also support the NTSC format. However, a PAL version is also included just in case. There are several ways to enable it:

- Holding down the SELECT button while the game is booting (before the red loading screen).

- Using a file browser such as Unirom and launching the file "DRAGONSL.PAL".

- Hex editing the iso file and searching for the line that says:

	BOOT = cdrom:\DRAGONSL.AIR;1
	and replacing "AIR" by "PAL" so it says
	BOOT = cdrom:\DRAGONSL.PAL;1

- Using an iso editor to replace the contents of the file SYSTEM.CNF and make the same change as above.

I know there's a way to detect the region of the console and set up the matching video mode, but doing so, players can't choose which version to play and many PAL users prefer the NTSC versions.

The PAL version is not optimized. Movie resolution is 320x240 and frame rate is 12 frames per second as in the PC version. The additional 16 lines are enough for adding a heads-up display, but in this case it's identical to the NTSC version.

----------------

3. Source code.

Source code is provided with the game. It is a very short and simple program and it is mostly based on the movie player example made by Vince Diesi included with the official SDK. I like the Net Yaroze and its community, but unfortunately, currently the only SDK with movie decoder support is Psy-Q.

Psy-Q 4.6 is required for compiling the source. Required assets can be extracted from the iso file. Remember that the original Dragon's Lair source code may be completely different as this is only a reinterpretation of the classic game.

To build the binary, just run PSYMAKE. For building a PAL version, edit MAIN.H and comment line 21 (#define NTSC). Optionally, edit MAKEFILE.MAK, comment line 8 and uncomment line 9. This is just the area specification (America or Europe), but leaving the default value is fine.

Keep in mind I'm just an amateur and the sole purpose of this program was to make a playable port of Dragon's Lair based on the PC version I own. The source code is pretty basic stuff. There are far more interesting sources than this one.

A copy of this source should be available at https://github.com/netyarouze/dragonslair
