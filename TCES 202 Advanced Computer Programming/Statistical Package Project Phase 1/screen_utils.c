/*
screen_utils.c
 
 Brian G. Hess
 TCES202
 Winter 2015
 
*/

#include "screen_utils.h"

/** clears the screen by scrolling text upward 
*/
void clear_screen(void) {
	int i;
	for (i=0; i<SCREEN_LINES; i++) printf("\n");
}

void press_enter(void) {
	int c;

	printf("Press ENTER to continue: ");
    while (1) {
		c=getchar();
		if (c=='\n' || c==-1) break;
	}
}

