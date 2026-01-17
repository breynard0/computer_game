#ifndef COMPUTER_GAME_MAIN_H
#define COMPUTER_GAME_MAIN_H

enum Stage
{
    STAGE_FIRST_PC_ADD_SUB,
    STAGE_SECOND_REGISTERS,
    STAGE_THIRD_ALU,
    STAGE_FOURTH_JUMP,
    STAGE_FIVE_DECODER_BUS,
    STAGE_SIX_MEMORY_AND_CLOCK,
};

#include "instructions.h"
#include "raylib.h"

typedef struct
{
    struct Instruction program[256];
    int program_counter;
    int registers[8];
    enum Stage sim_stage;
    int pc_textbox_editing;
    int output_textbox_editing;
    int output;
    int output_changed;
    int alu_answer;
    int cmp_answer;
    Font font;
} GameState;

void DrawTextFont(Font font, const char* text, int x, int y, int size);
int MeasureTextFont(Font font, const char* text, int size);
#endif //COMPUTER_GAME_MAIN_H
