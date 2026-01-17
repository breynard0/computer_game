#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "main.h"
#include "styles.h"

int eval_cmp_inst(const struct Instruction inst, const GameState* state)
{
    switch (inst.type)
    {
    case JLT:
        return state->registers[1] < state->registers[2];
    case JLE:
        return state->registers[1] <= state->registers[2];
    case JGT:
        return state->registers[1] > state->registers[2];
    case JGE:
        return state->registers[1] >= state->registers[2];
    case JEQ:
        return state->registers[1] == state->registers[2];
    case JNE:
        return state->registers[1] != state->registers[2];
    default: return -1;
    }
}

int get_cmp_left_edge(void)
{
    return GetScreenWidth() / 4;
}

int get_cmp_top_edge(void)
{
    return 3 * (GetScreenHeight() / 5);
}

int get_cmp_width(void)
{
    return GetScreenWidth() / 5;
}

int get_cmp_height(void)
{
    return GetScreenHeight() / 6;
}

void draw_cmp(const GameState* state)
{
    const int left_edge = get_cmp_left_edge();
    const int top_edge = get_cmp_top_edge();
    const int width = get_cmp_width();
    const int height = get_cmp_height();
    DrawRectangle(left_edge, top_edge, width, height,
                  CG_CMP_COLOR);

    const char* title_text = "Comparator";
    const int title_size = 28;
    const int title_width = MeasureTextFont(state->font, title_text, title_size);
    DrawTextFont(state->font, title_text, left_edge + (width - title_width) / 2, top_edge + height / 10, title_size);

    // Draw answer
    if (state->cmp_answer >= 0)
    {
        char* answer_text;
        if (state->cmp_answer == 0)
        {
            answer_text = "Nope";
        }
        else
        {
            answer_text = "Yep";
        }

        const int answer_size = 24;
        const int answer_width = MeasureTextFont(state->font, answer_text, answer_size);
        DrawTextFont(state->font, answer_text, left_edge + (width - answer_width) / 2, top_edge + height / 2,
                     answer_size);
    }
}
