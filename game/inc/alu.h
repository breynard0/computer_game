#ifndef COMPUTER_GAME_ALU_H
#define COMPUTER_GAME_ALU_H
#include "main.h"
int get_alu_left_edge(void);
int get_alu_top_edge(void);
int get_alu_width(void);
int get_alu_height(void);
int eval_alu_inst(struct Instruction inst, const GameState* state);
void draw_alu(const GameState* state);
#endif //COMPUTER_GAME_ALU_H
