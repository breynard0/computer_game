#include <raylib.h>

#include "inst_box.h"
#include "inst_drag.h"
#include "main.h"
#include "styles.h"

int draw_inst_list(const GameState state)
{
    const int pc = state.program_counter;

    const int box_height = get_inst_box_height();

    const int num_that_fit = GetScreenHeight() / box_height + 1;

    int idx = pc - num_that_fit / 2;

    if (idx < 0) idx = 0;

    int out_val = 0;

    for (int next = 0; next < GetScreenHeight(); next += box_height)
    {
        const int i = idx % 256;
        
        struct InstDrag drag = {.inst = state.program[i], .x = 0, .y = next};
        Color col = CG_DRAG_INST_INACTIVE_COLOR;
        
        if (i == pc)
        {
            out_val = next;
            col = CG_DRAG_INST_SEMIACTIVE_COLOR;
        }
        
        draw_inst_box(&drag, get_inst_box_width(), box_height, col);
        idx++;
    }

    return out_val;
}
