#include <raylib.h>
#include <stdio.h>
#include <string.h>

#include "inst_drag.h"
#include "styles.h"

int get_inst_box_width(void)
{
    return (int)(GetScreenWidth() * 0.2);
}

int get_inst_box_height(void)
{
    return get_inst_box_width() / 5;
}

void draw_inst_box(const struct InstDrag* drag, const int width, const int height, const Color bg)
{
    DrawRectangle(drag->x, drag->y, width, height, bg);
    DrawRectangleLines(drag->x, drag->y, width, height, CG_WINDOW_BORDER_COLOR);

    const int font_height = 3 * (height / 5);
    const char* op_text = "NOOP";

    switch (drag->inst.type)
    {
    case ADD:
        op_text = "ADD";
        break;
    case SUB:
        op_text = "SUB";
        break;
    case MOVE:
        op_text = "MOVE";
        break;
    case AND:
        op_text = "AND";
        break;
    case OR:
        op_text = "OR";
        break;
    case XOR:
        op_text = "XOR";
        break;
    case NAND:
        op_text = "NAND";
        break;
    case JLT:
        op_text = "JUMP LT";
        break;
    case JLE:
        op_text = "JUMP LE";
        break;
    case JGT:
        op_text = "JUMP GT";
        break;
    case JGE:
        op_text = "JUMP GE";
        break;
    case JEQ:
        op_text = "JUMP EQ";
        break;
    case JNE:
        op_text = "JUMP NE";
        break;
    case NOOP:
        op_text = "NO OPERATION";
        break;
    case LOAD:
        op_text = "LOAD";
        break;
    }

    char text_buf[16];
    char first_buf[16];
    sprintf(first_buf, "%i", drag->inst.first_operand);
    char second_buf[16];
    sprintf(second_buf, "%i", drag->inst.second_operand);

    if (drag->inst.type == MOVE)
    {
        if (drag->inst.first_operand == 8)
        {
            strcpy(first_buf, "OUT");
        }
        if (drag->inst.second_operand == 8)
        {
            strcpy(second_buf, "OUT");
        }
    }

    if (drag->inst.type == NOOP || drag->inst.show_ops == 0)
    {
        strcpy(text_buf, op_text);
    }
    else
    {
        sprintf(text_buf, "%s  %s  %s", op_text, first_buf, second_buf);
    }
    DrawText(text_buf, drag->x + width / 16, drag->y + (height - font_height) / 2, font_height, WHITE);
}
