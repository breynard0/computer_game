#ifndef COMPUTER_GAME_REGISTERS_H
#define COMPUTER_GAME_REGISTERS_H
int registers_start_x();
int registers_start_y();
int single_register_width();
int single_register_height();

#include "main.h"
void draw_registers(GameState* state);
#endif //COMPUTER_GAME_REGISTERS_H
