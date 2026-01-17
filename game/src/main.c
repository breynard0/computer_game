#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include "inst_drag.h"
#include "alu.h"
#include "styles.h"
#include "main.h"
#include "inst_list.h"
#include "gen_inst.h"
#include "screen_controls.h"

int main(void)
{
    const int screenWidth = 1200;
    const int screenHeight = 800;

    InitWindow(screenWidth, screenHeight, "Computer Game");

    SetTargetFPS(60);

    GameState state = {
        .program = {}, .program_counter = 0, .sim_stage = STAGE_SEVEN_CLOCK, .pc_textbox_editing = 0,
        .output_textbox_editing = 0, .output = 0, .alu_answer = -1000
    };
    regen_instructions(&state);

    struct InstDrag drag = (struct InstDrag){(struct Instruction){JLE, 12, 4}, 0, 0, 0};
    int last_program_counter = -1;

    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF); // NOLINT(*-narrowing-conversions)

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            state.output = 0;
            state.alu_answer = -1000;
            state.program_counter++;
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
