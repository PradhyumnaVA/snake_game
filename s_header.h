#ifndef S_HEADER_H
#define S_HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

// using struct to hold the variables for coordinates of head and []
typedef struct {
	int x,y;
	int rand_x, rand_y;
	char bone[9];
}coord;

/////// functions initialisation /////// 

extern coord *pos(coord*);
extern coord *move(coord*, char, int, int);
extern char* keep_score(char*, int);

////////////////////////////////////////

#endif
