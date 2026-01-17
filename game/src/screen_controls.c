#include <stddef.h>

#include "inst_box.h"
#include "main.h"
#include "raygui.h"

void draw_screen_controls(GameState* state)
{
    const float left_x = (float)get_inst_box_width();
    const float height = 0.05f * (float)GetScreenHeight();

    int tmp_pc = state->program_counter;
    GuiSetStyle(DEFAULT, TEXT_SIZE, 24);
    GuiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_RIGHT);
    const float width = height * 3.0f;
    if (GuiValueBox((Rectangle){left_x, (float)GetScreenHeight() - height, width, height}, " Program Counter",
                    &tmp_pc, 0,
                    255, state->pc_textbox_editing))
    {
        state->pc_textbox_editing = !state->pc_textbox_editing;
    }
    if (tmp_pc < 0)
    {
        tmp_pc = 0;
    }
    state->program_counter = tmp_pc % 256;

    GuiSetStyle(VALUEBOX, TEXT_ALIGNMENT, TEXT_ALIGN_LEFT);
    if (GuiValueBox((Rectangle){(float)GetScreenWidth() - width, (float)GetScreenHeight() - height, width, height},
                    "Output ",
                    &state->output, -256,
                    255, state->output_textbox_editing))
    {
        state->output_textbox_editing = !state->output_textbox_editing;
    }
}
