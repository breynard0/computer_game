#include "inst_drag.h"

#include "alu.h"
#include "inst_box.h"

#include "raylib.h"
#include "styles.h"

void update_draw_inst_drag(struct InstDrag* drag, GameState* state)
{
    const int width = get_inst_box_width();
    const int height = get_inst_box_height();

    draw_inst_box(drag, width, height, CG_DRAG_INST_ACTIVE_COLOR);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        const Vector2 position = GetMousePosition();
        const int pos_x = (int)position.x;
        const int pos_y = (int)position.y;
        if (drag->x <= pos_x && drag->x + width >= pos_x && drag->y < pos_y && pos_y < drag->y + height)
        {
            drag->dragging = true;
        }
    }
    if (IsMouseButtonUp(MOUSE_BUTTON_LEFT))
    {
        drag->dragging = false;

        // Calculate the ALU bounds and set the ALU value accordingly
        // Is it smart to calculate it right here? Absolutely not.
        // Will I have to touch this code ever again? Hope not!
        const int pos_x = drag->x;
        const int pos_y = drag->y;
        const int far_pos_x = drag->x + width;
        const int far_pos_y = drag->y + height;

        const int alu_pos_x = get_alu_left_edge();
        const int alu_pos_y = get_alu_top_edge();
        const int alu_far_pos_x = alu_pos_x + get_alu_width();
        const int alu_far_pos_y = alu_pos_y + get_alu_height();

        if (far_pos_x >= alu_pos_x && far_pos_y >= alu_pos_y && pos_x <= alu_far_pos_x && pos_y <= alu_far_pos_y)
        {
            state->alu_answer = eval_alu_inst(drag->inst);
        }
    }

    if (drag->dragging)
    {
        const Vector2 delta = GetMouseDelta();
        drag->x += (int)delta.x;
        drag->y += (int)delta.y;

        if (drag->x < 0)
        {
            drag->x = 0;
        }
        if (drag->x > GetScreenWidth() - width)
        {
            drag->x = GetScreenWidth() - width;
        }
        if (drag->y < 0)
        {
            drag->y = 0;
        }
        if (drag->y > GetScreenHeight() - height)
        {
            drag->y = GetScreenHeight() - height;
        }
    }
}
