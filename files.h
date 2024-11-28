
// Files containing textures and sounds.

typedef struct {
	int Position;// Sector position.
	int Size;// File size (in sectors, not bytes).
} ASSETS_FILE;


// STR movie files.

typedef struct{
short Type; // Movie type, defined in MOVIES.H
int Position; // Sector position in cd structure.
int Frames; // Total frames.
} MOVIE_FILE;

