#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "inst_drag.h"
#include "alu.h"
#include "comparator.h"
#include "styles.h"
#include "main.h"
#include "inst_list.h"
#include "gen_inst.h"
#include "screen_controls.h"
#include "registers.h"

#include "../deps/jetbrainmono.h" // font made with xxd

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(screenWidth, screenHeight, "Computer Game");
    SetWindowMinSize(1100, 600);

    SetTargetFPS(60);

    // Set font
    const Font jetbrains_mono = LoadFontFromMemory(".ttf", deps_JetBrainsMono_Regular_ttf,
                                                   (int)deps_JetBrainsMono_Regular_ttf_len,
                                                   48,
                                                   NULL, 0);
    GuiSetFont(jetbrains_mono);

    GameState state = {
        .program = {}, .program_counter = 0, .sim_stage = STAGE_SIX_MEMORY_AND_CLOCK, .pc_textbox_editing = 0,
        .output_textbox_editing = 0, .output = 0, .alu_answer = -1000, .output_changed = 0, .cmp_answer = -1,
        .registers = {}, .font = jetbrains_mono, .registers_editing = {}
    };
    regen_instructions(&state);

    struct InstDrag drag = (struct InstDrag){(struct Instruction){JLE, 12, 4}, 0, 0, 0};
    int last_program_counter = -1;

    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF); // NOLINT(*-narrowing-conversions)

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_R))
        {
            state.output = 0;
            state.alu_answer = -1000;
            state.cmp_answer = -1;
            state.output_changed = 0;
            state.program_counter++;
        }

        if (IsKeyPressed(KEY_R))
        {
            state.program_counter = 0;
            regen_instructions(&state);
        }

        if (IsKeyPressed(KEY_K))
        {
            state.sim_stage++;
            regen_instructions(&state);
        }

        BeginDrawing();

        ClearBackground(CG_MAINWINDOW_BACKGROUND_COLOR);

        // Draw ALU and comparator and friends
        if (state.sim_stage >= STAGE_THIRD_ALU)
        {
            draw_alu(&state);
        }
        if (state.sim_stage >= STAGE_FOURTH_JUMP)
        {
            draw_cmp(&state);
        }
        if (state.sim_stage >= STAGE_SECOND_REGISTERS)
        {
            draw_registers(&state);
        }

        const int cur_draggable_inst_height = draw_inst_list(state);
        if (state.program_counter != last_program_counter)
        {
            drag.x = 0;
            drag.y = cur_draggable_inst_height;
        }
        last_program_counter = state.program_counter;
        drag.inst = state.program[state.program_counter];
        update_draw_inst_drag(&drag, &state);

        draw_screen_controls(&state);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void DrawTextFont(const Font font, const char* text, const int x, const int y, const int size)
{
    DrawTextEx(font, text, (Vector2){(float)x, (float)y}, (float)size, 2, WHITE);
}

int MeasureTextFont(const Font font, const char* text, const int size)
{
    return (int)MeasureTextEx(font, text, (float)size, 2).x;
}
