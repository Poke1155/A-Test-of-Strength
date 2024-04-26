#include "logic.h"
#include "gba.h"
#include "images/mother3.h"
#include "images/saladrom2.h"
#include "images/RSE_Strength.h"
#include "images/HM04.h"
#include "images/tent.h"
#include "main.h"
#include "images/blackmage1.h"
#include "images/blackmage2.h"

void animation(int frame) {
  if (frame % 60 == 0)
  {
    drawImageDMA(0, 0, BLACKMAGEVICTORY1_WIDTH, BLACKMAGEVICTORY1_HEIGHT, BlackMageVictory1);
  }
  else if (frame % 30 == 0)
  {
    drawImageDMA(0, 0, BLACKMAGEVICTORY_WIDTH, BLACKMAGEVICTORY_HEIGHT, BlackMageVictory);
  }
}
void resetGameState(Player *p1, Player *oldplayer, Rock *rocks, Rock *initial_state, enum gba_state *state, int *init, int *frame, int *frameCount, int level_length, Rock *initial_state2, Rock *rocks2, int level_length2) {
  for (int i = 0; i < level_length; i++)
  {
    rocks[i].row = initial_state[i].row;
    rocks[i].column = initial_state[i].column;
  }
  for (int i = 0; i < level_length2; i++)
  {
    rocks2[i].row = initial_state2[i].row;
    rocks2[i].column = initial_state2[i].column;
  }
  
  *state = HEALTH;

  *init = 0;
  *frame = 0;
  *frameCount = 0;
  UNUSED(p1);
  UNUSED(oldplayer);
}

int collision(Player *p1, Rock *rocks, struct object hidden_machine, u32 button, int rocksLength, enum gba_state *state)
{
  if (p1->row == hidden_machine.row && p1->column == hidden_machine.column)
  {
    if (*state == LEVEL1)
    {
      *state = LEVEL2;
      return 0;
    }
    else if (*state == LEVEL2)
    {
      *state = WIN;
      return 0;
    }
  }
  for (int i = 0; i < rocksLength; i++)
  {
    Rock oldrock = {rocks[i].row, rocks[i].column, rocks[i].width, rocks[i].height};
    if (p1->row == rocks[i].row && p1->column == rocks[i].column)
    {
      int new_pos_row = rocks[i].row;
      int new_pos_col = rocks[i].column;
      
      if (KEY_DOWN(BUTTON_UP, button) && rocks[i].row - 16 >= 0)
      {
        new_pos_row -= 16;
      }    
      if (KEY_DOWN(BUTTON_DOWN, button) && rocks[i].row + 16 <= 160 - rocks[i].height)
      {
        new_pos_row += 16;
      }  
      if (KEY_DOWN(BUTTON_RIGHT, button) && rocks[i].column + 16 <= 240 - rocks[i].width)
      {
        new_pos_col += 16;
      }      
      if (KEY_DOWN(BUTTON_LEFT, button) && rocks[i].column - 16 >= 0)
      {
        new_pos_col -= 16;
      }      
      for (int j = 0; j < rocksLength; j++)
      {
        if (i != j && new_pos_row == rocks[j].row && new_pos_col == rocks[j].column)
        {
          return 1;
        }
      }
      drawRectDMA(oldrock.row, oldrock.column, oldrock.width, oldrock.height, BLACK);
      rocks[i].row = new_pos_row;
      rocks[i].column = new_pos_col;
      drawImageDMA(rocks[i].row, rocks[i].column, rocks[i].width, rocks[i].height, RSE_Strength);
      return 1;
    }
  }
  return 0;
}

void playermovement(Player *oldplayer, Player *p1, u32 button, int *frame, Rock *rocks, struct object hidden_machine, int rocksLength, enum gba_state *state)
{
  
  if (*frame >= 10)
  {
    enum gba_state *temp = state;
    int moved = 0;
    drawRectDMA(oldplayer->row, oldplayer->column, oldplayer->width, oldplayer->height, BLACK);
    oldplayer->column = p1->column;
    oldplayer->row = p1->row;
    if (KEY_DOWN(BUTTON_UP, button) && p1->row -16 >= 0 && checkKey(KEY_DOWN(BUTTON_DOWN, button), KEY_DOWN(BUTTON_LEFT, button), KEY_DOWN(BUTTON_RIGHT, button)) ) {
      p1->row -= 16;
      if (collision(p1, rocks, hidden_machine, button, rocksLength, state) == 1)
      {
        p1->row += 16;
      }
      if (WINCOND(state, temp)) return;      
      moved = 1;
    }
    if (KEY_DOWN(BUTTON_DOWN, button) && p1->row  + 16 <= 160 - p1->height && checkKey(KEY_DOWN(BUTTON_LEFT, button), KEY_DOWN(BUTTON_UP, button), KEY_DOWN(BUTTON_RIGHT, button)) ) {
      p1->row += 16;
      if (collision(p1, rocks, hidden_machine, button, rocksLength, state) == 1)
      {
        p1->row -= 16;
      }
      if (WINCOND(state, temp)) return;
      moved = 1;
    }
    if (KEY_DOWN(BUTTON_LEFT, button) && p1->column - 16 >= 0 && checkKey(KEY_DOWN(BUTTON_DOWN, button), KEY_DOWN(BUTTON_UP, button), KEY_DOWN(BUTTON_RIGHT, button)) ) {
      p1->column -= 16;
       if (collision(p1, rocks, hidden_machine, button, rocksLength, state) == 1)
      {
        p1->column += 16;
      }
      if (WINCOND(state, temp)) return;
      moved = 1;
    }
    if (KEY_DOWN(BUTTON_RIGHT, button) && p1->column + 16 <= 240 - p1->width && checkKey(KEY_DOWN(BUTTON_DOWN, button), KEY_DOWN(BUTTON_LEFT, button), KEY_DOWN(BUTTON_UP, button)) ) {
      p1->column += 16;
      if (collision(p1, rocks, hidden_machine, button, rocksLength, state) == 1)
      {
        p1->column -= 16;
      }
      if (WINCOND(state, temp)) return;
      moved = 1;
    }

    if (moved) {
      oldplayer->column = p1->column;
      oldplayer->row = p1->row;
      *frame = 0;
    }
  }
  drawImageDMA(p1->row, p1->column, p1->width, p1->height, tent);
}
