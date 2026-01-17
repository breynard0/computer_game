#include <raylib.h>
#include <stdio.h>

#include "main.h"
#include "styles.h"

int eval_alu_inst(const struct Instruction inst)
{
    switch (inst.type)
    {
    case ADD:
        return inst.first_operand + inst.second_operand;
    case SUB:
        return inst.first_operand - inst.second_operand;
    case AND:
        return inst.first_operand & inst.second_operand;
    case OR:
        return inst.first_operand | inst.second_operand;
    case NAND:
        return ~(inst.first_operand & inst.second_operand);
    case XOR:
        return inst.first_operand ^ inst.second_operand;
    default: return -1000;
    }
}

int get_alu_left_edge(void)
{
    return 7 * (GetScreenWidth() / 10);
}

int get_alu_top_edge(void)
{
    return GetScreenHeight() / 20;
}

int get_alu_width(void)
{
    return GetScreenWidth() / 5;
}

int get_alu_height(void)
{
    return GetScreenHeight() / 4;
}

void draw_alu(const GameState* state)
{
    const int left_edge = get_alu_left_edge();
    const int top_edge = get_alu_top_edge();
    const int width = get_alu_width();
    const int height = get_alu_height();
    DrawRectangle(left_edge, top_edge, width, height,
                  CG_ALU_COLOR);

    const char* title_text = "ALU";
    const int title_size = 28;
    const int title_width = MeasureTextFont(state->font, title_text, title_size);
    DrawTextFont(state->font, title_text, left_edge + (width - title_width) / 2, top_edge + height / 10, title_size);

    // Draw answer
    if (state->alu_answer >= -256 && state->alu_answer <= 256)
    {
        char answer_text[32];
        sprintf(answer_text, "Answer: %i", state->alu_answer);
        const int answer_size = 24;
        const int answer_width = MeasureTextFont(state->font, answer_text, answer_size);
        DrawTextFont(state->font, answer_text, left_edge + (width - answer_width) / 2, top_edge + height / 2,
                     answer_size);
    }
}
