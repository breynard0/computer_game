#include <stdio.h>

#include "alu.h"
#include "main.h"
#include "raylib.h"
#include "raygui.h"
#include "styles.h"

int registers_start_x()
{
    return 4 * (GetScreenWidth() / 5);
}

int registers_start_y()
{
    return get_alu_top_edge();
}

int single_register_width()
{
    return 6 * (GetScreenWidth() / 33);
}

int single_register_height()
{
    return GetScreenHeight() / 10;
}

void draw_registers(GameState* state)
{
    int num_registers = 3;
    if (state->sim_stage >= STAGE_SIX_MEMORY_AND_CLOCK)
    {
        num_registers = 8;
    }

    GuiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_RIGHT);
    const float valbox_height = (float)single_register_height() / 2;

    for (int i = 0; i < num_registers; i++)
    {
        const int reg_pos_y = registers_start_y() + (single_register_height() + single_register_height() / 8) * i;
        DrawRectangle(registers_start_x(),
                      reg_pos_y,
                      single_register_width(), single_register_height(), CG_REG_COLOR);

        int tmp_reg = state->registers[i];
        char reg_title_text[16];

        sprintf(reg_title_text, " Reg %i", i);
        if (GuiValueBox((Rectangle){
                            (float)registers_start_x() + (float)single_register_width() * 0.1f,
                            (float)reg_pos_y + (float)single_register_height() / 2 - (float)valbox_height /
                            2,
                            valbox_height * 2, valbox_height
                        }, reg_title_text, &tmp_reg, 0, 255, state->registers_editing[i]))
        {
            state->registers_editing[i] = !state->registers_editing[i];
        }

        if (tmp_reg < 0)
        {
            tmp_reg = 0;
        }
        state->registers[i] = tmp_reg;
    }
}
