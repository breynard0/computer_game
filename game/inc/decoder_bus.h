#ifndef COMPUTER_GAME_DECODER_BUS_H
#define COMPUTER_GAME_DECODER_BUS_H
#include "main.h"
int decoder_x();
int decoder_y();
int decoder_width();
int decoder_height();
void draw_decoder(const GameState* state);
void draw_control_data_lines(const GameState* state);
#endif //COMPUTER_GAME_DECODER_BUS_H
