#include "raylib.h"

#define RAYGUI_IMPLEMENTATION
#include "inst_drag.h"
#include "raygui.h"
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

    GameState state = {.program = {}, .program_counter = 0, .sim_stage = STAGE_FIRST_PC_ADD_SUB};
    regen_instructions(&state);

    struct InstDrag drag = (struct InstDrag){(struct Instruction){JLE, 12, 4}, 0, 0, 0};
    int last_program_counter = -1;
    
    GuiSetStyle(DEFAULT, TEXT_COLOR_NORMAL, 0xFFFFFFFF); // NOLINT(*-narrowing-conversions)

    while (!WindowShouldClose())
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            state.output = 0;
            state.program_counter++;
        }

        BeginDrawing();

        ClearBackground(CG_MAINWINDOW_BACKGROUND_COLOR);

        const int cur_draggable_inst_height = draw_inst_list(state);
        if (state.program_counter != last_program_counter)
        {
            drag.x = 0;
            drag.y = cur_draggable_inst_height;
        }
        last_program_counter = state.program_counter;
        drag.inst = state.program[state.program_counter];
        update_draw_inst_drag(&drag);

        draw_screen_controls(&state);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
