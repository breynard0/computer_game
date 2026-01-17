#ifndef COMPUTER_GAME_INST_DRAG_H
#define COMPUTER_GAME_INST_DRAG_H
#include "instructions.h"
struct InstDrag
{
    struct Instruction inst;
    int x;
    int y;
    int dragging;
};
#include "main.h"
void update_draw_inst_drag(struct InstDrag* drag, GameState* state);
#endif //COMPUTER_GAME_INST_DRAG_H