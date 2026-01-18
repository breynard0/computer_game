#include <stdio.h>
#include <string.h>

#include "alu.h"
#include "main.h"
#include "raygui.h"
#include "styles.h"
#include "text.h"

void draw_manual_button(GameState* state)
{
    const int button_size = 2 * get_alu_top_edge() / 3;

    GuiSetStyle(BUTTON, BASE_COLOR_NORMAL, 0x222224);
    GuiSetStyle(BUTTON, BASE_COLOR_FOCUSED, 0x555556);
    if (GuiButton((Rectangle){7 * (float)GetScreenWidth() / 8 - 2, 2, (float)GetScreenWidth() / 8, (float)button_size},
                  "Open Manual"))
    {
        state->help_window_open = true;
    }
}

void draw_manual_window(GameState* state)
{
    const float base_unit_x = (float)GetScreenWidth() / 6;
    const float base_unit_y = (float)GetScreenHeight() / 8;

    GuiSetStyle(DEFAULT, BACKGROUND_COLOR, ColorToInt(CG_INNER_WINDOW_BACKGROUND_COLOR));
    GuiSetStyle(DEFAULT, LINE_COLOR, ColorToInt(CG_INNER_WINDOW_BACKGROUND_COLOR));
    GuiSetStyle(STATUSBAR, BASE_COLOR_NORMAL, ColorToInt(CG_INNER_WINDOW_BACKGROUND_COLOR));
    GuiSetStyle(STATUSBAR, BORDER_COLOR_NORMAL, ColorToInt(CG_INNER_WINDOW_BACKGROUND_COLOR));

    const float width = (float)GetScreenWidth() - 2 * base_unit_x;
    const float height = (float)GetScreenHeight() - 2 * base_unit_y;
    const Rectangle window_rect = (Rectangle){
        base_unit_x, base_unit_y, width,
        height
    };

    if (GuiWindowBox(window_rect, "")) state->help_window_open = false;

    GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_WORD);
    GuiSetStyle(DEFAULT, TEXT_LINE_SPACING, 32);
    GuiSetStyle(DEFAULT, TEXT_ALIGNMENT_VERTICAL, TEXT_ALIGN_TOP);

    state->scroll_pos += GetMouseWheelMoveV().y * 40;
    if (state->scroll_pos > 0)
    {
        state->scroll_pos = 0;
    }

    const Rectangle label_rect = (Rectangle){
        base_unit_x + 0.1f * width, window_rect.y + state->scroll_pos, width * 0.8f, 6 * height
    };

    char content[16384];
    int content_len = 0;
    const int stage = state->sim_stage;
    char* newlines = "\n\n";
    
    if (stage >= STAGE_SIX_MEMORY_AND_CLOCK)
    {
        strcpy(content + content_len, SIXTH);
        content_len += (int)strlen(SIXTH);
        strcpy(content + content_len, newlines);
        content_len += (int)strlen(newlines);
    }
    if (stage >= STAGE_FIVE_DECODER_BUS)
    {
        strcpy(content + content_len, FIFTH);
        content_len += (int)strlen(FIFTH);
        strcpy(content + content_len, newlines);
        content_len += (int)strlen(newlines);
    }
    if (stage >= STAGE_FOURTH_JUMP)
    {
        strcpy(content + content_len, FOURTH);
        content_len += (int)strlen(FOURTH);
        strcpy(content + content_len, newlines);
        content_len += (int)strlen(newlines);
    }
    if (stage >= STAGE_THIRD_ALU)
    {
        strcpy(content + content_len, THIRD);
        content_len += (int)strlen(THIRD);
        strcpy(content + content_len, newlines);
        content_len += (int)strlen(newlines);
    }
    if (stage >= STAGE_SECOND_REGISTERS)
    {
        strcpy(content + content_len, SECOND);
        content_len += (int)strlen(SECOND);
        strcpy(content + content_len, newlines);
        content_len += (int)strlen(newlines);
    }
    if (stage >= STAGE_FIRST_PC_ADD_SUB)
    {
        strcpy(content + content_len, FIRST);
        content_len += (int)strlen(FIRST);
        strcpy(content + content_len, newlines);
    }

    BeginScissorMode((int)label_rect.x, (int)window_rect.y, (int)label_rect.width, (int)window_rect.height);
    GuiLabel(label_rect, content);
    EndScissorMode();

    GuiSetStyle(DEFAULT, TEXT_WRAP_MODE, TEXT_WRAP_NONE);
}
