#include <stdio.h>

#include "alu.h"
#include "gen_inst.h"
#include "inst_box.h"
#include "main.h"
#include "styles.h"
#include "programs.h"

void draw_coins_display(const GameState* state)
{
    const int pos_x = GetScreenWidth() / 2;
    const int height = get_alu_top_edge() / 2;

    char num_text[32];
    sprintf(num_text, " $%i", state->coins);
    DrawTextFont(state->font, num_text, pos_x + height / 2, height / 2, height);
}

void draw_shop_items(GameState* state)
{
    const int height = 2 * GetScreenHeight() / 7;
    const int pos_y = GetScreenHeight() - height;

    const int width = get_inst_box_width();

    DrawRectangle(0, pos_y, width, height, CG_INNER_WINDOW_BACKGROUND_COLOR);

    const int shop_item_height = height / 4;
    int draw_height = pos_y;
    for (uint32_t i = state->sim_stage + 1; draw_height < GetScreenHeight(); i++)
    {
        Color bg_col = CG_SHOP_NAY_COLOR;

        const char* text = "x";
        int cost = 0;
        switch (i)
        {
        case STAGE_FIRST_PC_ADD_SUB:
            text = "Adding";
            cost = 0;
            break;
        case STAGE_SECOND_REGISTERS:
            text = "Registers";
            cost = 10;
            break;
        case STAGE_THIRD_ALU:
            text = "ALU";
            cost = 25;
            break;
        case STAGE_FOURTH_JUMP:
            text = "Jumps";
            cost = 70;
            break;
        case STAGE_FIVE_DECODER_BUS:
            text = "Control Logic";
            cost = 180;
            break;
        case STAGE_SIX_MEMORY_AND_CLOCK:
            text = "Automation";
            cost = 1000;
            break;
        default: break;
        }

        if (text[0] == 'x')
        {
            break;
        }

        const int can_buy = state->coins >= cost && state->sim_stage == i - 1;
        if (can_buy)
        {
            bg_col = CG_SHOP_YAY_COLOR;
        }

        char text_and_cost[64];
        sprintf(text_and_cost, "%s, $%i", text, cost);

        DrawRectangle(0, draw_height, width, shop_item_height, bg_col);
        int text_height = shop_item_height / 2;
        while (MeasureTextFont(state->font, text_and_cost, text_height) + 10 > width)
        {
            text_height--;
        }

        DrawTextFont(state->font, text_and_cost, 10, draw_height + (shop_item_height - text_height) / 2, text_height);

        const int mouse_x = GetMouseX();
        const int mouse_y = GetMouseY();
        if (mouse_x < width && mouse_y > draw_height && mouse_y < draw_height + shop_item_height)
        {
            DrawRectangleLines(0, draw_height, width, shop_item_height, WHITE);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && can_buy)
            {
                state->sim_stage = i;
                state->coins -= cost;
                regen_instructions(state);
                for (int j = 0; j < 8; j++)
                {
                    state->registers[j] = 0;
                }
                state->program_counter = 0;
                state->help_window_open = true;
                state->scroll_pos = 0;
                state->output = 0;
            }
        }

        draw_height += shop_item_height;
    }

    if (state->sim_stage >= STAGE_SIX_MEMORY_AND_CLOCK)
    {
        const int program_height = height / 3;

        const int mouse_x = GetMouseX();
        const int mouse_y = GetMouseY();

        {
            draw_height = pos_y;
            DrawRectangle(0, draw_height, width, program_height, CG_PROG_BUTTON_COLOR);
            int text_height = program_height / 2;
            while (MeasureTextFont(state->font, "Fibonacci", text_height) + 10 > width)
            {
                text_height--;
            }

            DrawTextFont(state->font, "Fibonacci", 10, draw_height + (program_height - text_height) / 3, text_height);
            if (mouse_x < width && mouse_y > draw_height && mouse_y < draw_height + program_height)
            {
                DrawRectangleLines(0, draw_height, width, program_height, WHITE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    for (int i = 0; i < 256; i++)
                    {
                        state->program[i] = fibonacci[i];
                    }
                    for (int j = 0; j < 8; j++)
                    {
                        state->registers[j] = 0;
                    }
                    state->program_counter = 0;
                    state->automatic = false;
                    state->output = 0;
                }
            }
        }
        {
            draw_height = pos_y + program_height;
            DrawRectangle(0, draw_height, width, program_height, CG_PROG_BUTTON_COLOR);
            int text_height = program_height / 2;
            while (MeasureTextFont(state->font, "Factorial", text_height) + 10 > width)
            {
                text_height--;
            }

            DrawTextFont(state->font, "Factorial", 10, draw_height + (program_height - text_height) / 3, text_height);
            if (mouse_x < width && mouse_y > draw_height && mouse_y < draw_height + program_height)
            {
                DrawRectangleLines(0, draw_height, width, program_height, WHITE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    for (int i = 0; i < 256; i++)
                    {
                        state->program[i] = factorial[i];
                    }
                    for (int j = 0; j < 8; j++)
                    {
                        state->registers[j] = 0;
                    }
                    state->program_counter = 0;
                    state->automatic = false;
                    state->output = 0;
                }
            }
        }
        {
            draw_height = pos_y + 2 * program_height;
            DrawRectangle(0, draw_height, width, program_height, CG_PROG_BUTTON_COLOR);
            int text_height = program_height / 2;
            while (MeasureTextFont(state->font, "GCD", text_height) + 10 > width)
            {
                text_height--;
            }

            DrawTextFont(state->font, "GCD", 10, draw_height + (program_height - text_height) / 3, text_height);
            if (mouse_x < width && mouse_y > draw_height && mouse_y < draw_height + program_height)
            {
                DrawRectangleLines(0, draw_height, width, program_height, WHITE);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                {
                    for (int i = 0; i < 256; i++)
                    {
                        state->program[i] = gcd[i];
                    }
                    for (int j = 0; j < 8; j++)
                    {
                        state->registers[j] = 0;
                    }
                    state->program_counter = 0;
                    state->automatic = false;
                    state->output = 0;
                }
            }
        }
    }

    DrawRectangle(0, pos_y - 2, get_inst_box_width(), 2, CG_WINDOW_BORDER_COLOR);
}
