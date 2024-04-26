#ifndef MAIN_H
#define MAIN_H

#include "gba.h"

// TODO: Create any necessary structs
#define WINCOND(x, y) ((x) != (y))
#define checkKey(x, y, z) (!(x) && !(y) && !(z))
enum gba_state {
  HEALTH,
  START,
  LEVEL1,
  LEVEL2,
  WIN,
};

typedef struct object {
    int row;
    int column;
    int width;
    int height;
}Rock, Player;
/*
* For example, for a Snake game, one could be:
*
* struct snake {
*   int heading;
*   int length;
*   int row;
*   int col;
* };
*
* Example of a struct to hold state machine data:
*
* struct state {
*   int currentState;
*   int nextState;
* };
*
*/


#endif
