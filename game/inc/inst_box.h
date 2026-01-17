#ifndef COMPUTER_GAME_INST_BOX_H
#define COMPUTER_GAME_INST_BOX_H
#include <raylib.h>
#include "inst_drag.h"
int get_inst_box_width(void);
int get_inst_box_height(void);
void draw_inst_box(const struct InstDrag* drag, int width, int height, Color bg, const GameState* state);
#endif //COMPUTER_GAME_INST_BOX_H
