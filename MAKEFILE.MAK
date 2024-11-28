# ----------------------------------------------------------------------------
# - Psymake Makefile
# ----------------------------------------------------------------------------

CC		= ccpsx
LINK		= psylink
CPE2X  		= cpe2x
AREA		= /ca
#AREA		= /ce

# ----------------------------------------------------------------------------

# Add NTSC definition to compile for NTSC (undefined for PAL).
# Add TESTING definition for debug information while playing the movie.
# Add FIND_VLCBUF definition to find maximum runlevel.


# Define to compile final version. If defined removes all pollhosts, set 2MB
# and ramsize. Else use pollhosts and 8MB for development. 
CCOPTS		= -Wunused -comments-c++ -c -O2 -DFINAL -I.. -I.


# Define to compile with debug.
#CCOPTS		= -Wunused -comments-c++ -c -g -I.. -I. -DDEBUG


LINKOPTS	= /m /c /g 

# ----------------------------------------------------------------------------

OBJS		= main.obj movie.obj control.obj font.obj game.obj bsplay.obj sound.obj syssetup.obj options.obj

# ----------------------------------------------------------------------------

all: main.cpe
	

main.cpe: $(OBJS) main.lnk makefile 
	$(LINK) $(LINKOPTS) @main.lnk,main.cpe,main.sym,main.map
	$(CPE2X) $(AREA) main.cpe

# ------------------------------------------------------------------------------

main.obj: main.c main.h game.h
	$(CC) $(CCOPTS) main.c -o main.obj


syssetup.obj: syssetup.c main.h control.h
	$(CC) $(CCOPTS) syssetup.c -o syssetup.obj


movie.obj: movie.c movie.h movies.h main.h files.h game.h assets.h
	$(CC) $(CCOPTS) movie.c -o movie.obj


control.obj: control.c control.h ctrller.h game.h font.h
	$(CC) $(CCOPTS) control.c -o control.obj


font.obj: font.c font.h
	$(CC) $(CCOPTS) font.c -o font.obj


game.obj: game.c assets.h files.h game.h bsframes.h font.h control.h main.h sound.h movies.h movie.h language.h options.h debug.h stages.h credits.h sectors.h
	$(CC) $(CCOPTS) game.c -o game.obj


bsplay.obj: bsplay.c assets.h bsframes.h
	$(CC) $(CCOPTS) bsplay.c -o bsplay.obj


sound.obj: sound.c sound.h options.h
	$(CC) $(CCOPTS) sound.c -o sound.obj


options.obj: options.c options.h language.h debug.h
	$(CC) $(CCOPTS) options.c -o options.obj


# ----------------------------------------------------------------------------

