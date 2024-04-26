#ifndef LOGIC_H
#define LOGIC_H

#include "main.h"

void resetGameState(Player *p1, Player *oldplayer, Rock *rocks, Rock *initial_state, enum gba_state *state, int *init, int *frame, int *frameCount, int level_length, Rock *initial_state2, Rock *rocks2, int level_length2);
int collision(Player *p1, Rock *rocks, struct object hidden_machine, u32 button, int rocksLength, enum gba_state *state);
void playermovement(Player *oldplayer, Player *p1, u32 button, int *frame, Rock *rocks, struct object hidden_machine, int rocksLength, enum gba_state *state);
void animation(int frame);
#endif // LOGIC_H