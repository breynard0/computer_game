#include "inst_drag.h"
#include "inst_box.h"

#include "raylib.h"
#include "styles.h"

void update_draw_inst_drag(struct InstDrag* drag)
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
