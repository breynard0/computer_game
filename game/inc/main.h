#ifndef COMPUTER_GAME_MAIN_H
#define COMPUTER_GAME_MAIN_H

enum Stage
{
    STAGE_FIRST_PC_ADD_SUB,
    STAGE_SECOND_REGISTERS,
    STAGE_THIRD_ALU,
    STAGE_FOURTH_JUMP,
    STAGE_FIVE_DECODER_BUS,
    STAGE_SIX_MEMORY,
    STAGE_SEVEN_CLOCK
};

#include "instructions.h"

typedef struct
{
    struct Instruction program[256];
    int program_counter;
    enum Stage sim_stage;
    int pc_textbox_editing;
    int output_textbox_editing;
    int output;
} GameState;
#endif //COMPUTER_GAME_MAIN_H
