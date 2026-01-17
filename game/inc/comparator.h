#ifndef COMPUTER_GAME_COMPARATOR_H
#define COMPUTER_GAME_COMPARATOR_H
#include "main.h"
int get_cmp_left_edge(void);
int get_cmp_top_edge(void);
int get_cmp_width(void);
int get_cmp_height(void);
int eval_cmp_inst(struct Instruction inst, const GameState* state);
void draw_cmp(const GameState* state);
#endif //COMPUTER_GAME_COMPARATOR_H