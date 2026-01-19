#include <stdio.h>
#include <string.h>

#include "alu.h"
#include "comparator.h"
#include "inst_box.h"
#include "main.h"
#include "raylib.h"
#include "registers.h"
#include "styles.h"

int decoder_x()
{
    return get_cmp_left_edge();
}

int decoder_y()
{
    return get_alu_top_edge();
}

int decoder_width()
{
    return GetScreenWidth() / 8;
}

int decoder_height()
{
    return GetScreenHeight() / 6;
}

void draw_decoder(const GameState* state)
{
    DrawRectangle(decoder_x(), decoder_y(), decoder_width(), decoder_height(), CG_DECODER_COLOR);

    const int text_size = 28;
    const int text_width = MeasureTextFont(state->font, "Decoder", text_size);
    DrawTextFont(state->font, "Decoder", decoder_x() + (decoder_width() - text_width) / 2, decoder_height() / 3,
                 text_size);
}

void DrawLineThickness(const int start_x, const int start_y, const int end_x, const int end_y, const Color color,
                       const int thickness)
{
    DrawLineEx((Vector2){(float)start_x, (float)start_y}, (Vector2){(float)end_x, (float)end_y}, (float)thickness,
               color);
}

void draw_control_data_lines(const GameState* state)
{
    const struct Instruction inst = state->program[state->program_counter];

    const int control_line_width = 4;
    const int data_line_width = 8;

    // Since the bus is entirely on or off, everything will be just one color
    Color bus_color = CG_DATA_LINE_ACTIVE_COLOR;
    Color control_bus_color = CG_CONTROL_LINE_ACTIVE_COLOR;
    if ((inst.type >= JLT && inst.type <= JNE && state->cmp_answer != 1) || inst.type == NOOP)
    {
        bus_color = CG_DATA_LINE_INACTIVE_COLOR;
        control_bus_color = CG_CONTROL_LINE_INACTIVE_COLOR;
    }

    // Draw control lines

    const int dec_inst_midpoint_x = get_inst_box_width() + (decoder_x() - get_inst_box_width()) / 2;
    // Decoder to instruction
    DrawLineThickness(get_inst_box_width() - 4, state->cur_draggable_inst_height + get_inst_box_height() / 2,
                      dec_inst_midpoint_x + control_line_width / 2,
                      state->cur_draggable_inst_height + get_inst_box_height() / 2,
                      CG_CONTROL_LINE_ACTIVE_COLOR, control_line_width);
    DrawLineThickness(decoder_x() + 4, decoder_y() + decoder_height() / 2,
                      dec_inst_midpoint_x - control_line_width / 2, decoder_y() + decoder_height() / 2,
                      CG_CONTROL_LINE_ACTIVE_COLOR, control_line_width);
    DrawLineThickness(dec_inst_midpoint_x,
                      state->cur_draggable_inst_height + get_inst_box_height() / 2, dec_inst_midpoint_x,
                      decoder_y() + decoder_height() / 2, CG_CONTROL_LINE_ACTIVE_COLOR, control_line_width);

    // Decoder to comparator
    Color cmp_control_color = CG_CONTROL_LINE_INACTIVE_COLOR;
    if (inst.type >= JLT && inst.type <= JNE) cmp_control_color = CG_CONTROL_LINE_ACTIVE_COLOR;
    DrawLineThickness(decoder_x() + decoder_width() / 16, decoder_y() + decoder_height(),
                      decoder_x() + decoder_width() / 16, get_cmp_top_edge(), cmp_control_color, control_line_width);

    // Decoder to ALU
    Color alu_control_color = CG_CONTROL_LINE_INACTIVE_COLOR;
    if (inst.type >= ADD && inst.type <= XOR) alu_control_color = CG_CONTROL_LINE_ACTIVE_COLOR;
    DrawLineThickness(decoder_x() + decoder_width(), decoder_y() + decoder_height() / 2,
                      get_alu_left_edge(), decoder_y() + decoder_height() / 2, alu_control_color, control_line_width);

    // Decoder to output
    Color output_color = CG_CONTROL_LINE_INACTIVE_COLOR;
    if (inst.type == LOAD)
    {
        if (8 == inst.second_operand)
        {
            output_color = CG_CONTROL_LINE_ACTIVE_COLOR;
        }
    }
    if (inst.type == MOVE)
    {
        if (8 == inst.first_operand || 8 == inst.second_operand)
        {
            output_color = CG_CONTROL_LINE_ACTIVE_COLOR;
        }
    }
    DrawLineThickness(decoder_x() + decoder_width(), decoder_y() + decoder_height() - decoder_height() / 8,
                      get_alu_left_edge() - 20 + control_line_width / 2,
                      decoder_y() + decoder_height() - decoder_height() / 8, output_color,
                      control_line_width);
    DrawLineThickness(get_alu_left_edge() - 20, decoder_y() + decoder_height() - decoder_height() / 8,
                      get_alu_left_edge() - 20, GetScreenHeight() - control_line_width, output_color,
                      control_line_width);
    DrawLineThickness(get_alu_left_edge() - 20 - control_line_width / 2, GetScreenHeight() - control_line_width,
                      (int)((float)GetScreenWidth() - 0.09f * (float)GetScreenHeight()),
                      GetScreenHeight() - control_line_width, output_color, control_line_width);

    // Decoder to program counter
    Color pc_color = CG_CONTROL_LINE_INACTIVE_COLOR;
    if (state->cmp_answer == 1)
    {
        pc_color = CG_CONTROL_LINE_ACTIVE_COLOR;
    }

    DrawLineThickness(decoder_x() + decoder_width(),
                      decoder_y() + decoder_height() - decoder_height() / 8 + 2 * control_line_width,
                      get_alu_left_edge() - 20 - 2 * control_line_width + control_line_width / 2,
                      decoder_y() + decoder_height() - decoder_height() / 8 + 2 * control_line_width, pc_color,
                      control_line_width);
    DrawLineThickness(get_alu_left_edge() - 20 - 2 * control_line_width,
                      decoder_y() + decoder_height() - decoder_height() / 8 + 2 * control_line_width,
                      get_alu_left_edge() - 20 - 2 * control_line_width, GetScreenHeight() - control_line_width,
                      pc_color,
                      control_line_width);
    DrawLineThickness(get_alu_left_edge() - 20 - control_line_width - control_line_width / 2,
                      GetScreenHeight() - control_line_width,
                      (int)(0.09f * (float)GetScreenHeight()) + get_inst_box_width(),
                      GetScreenHeight() - control_line_width, pc_color, control_line_width);

    // Decoder to registers
    int register_count = 3;
    const int register_bus_x = registers_start_x() - data_line_width * 4;
    int last_bus_register_y = 0;
    if (state->sim_stage >= STAGE_SIX_MEMORY_AND_CLOCK) register_count = 8;
    for (int i = 0; i < register_count; i++)
    {
        const int initial_x = decoder_x() + decoder_width() - decoder_width() / 16;
        const int line_separation = control_line_width * 2;
        Color control_color = CG_CONTROL_LINE_INACTIVE_COLOR;
        if (inst.type == LOAD)
        {
            if (i == inst.second_operand)
            {
                control_color = CG_CONTROL_LINE_ACTIVE_COLOR;
            }
        }
        if (inst.type == MOVE)
        {
            if (i == inst.first_operand || i == inst.second_operand)
            {
                control_color = CG_CONTROL_LINE_ACTIVE_COLOR;
            }
        }
        if (i <= 2 && ((inst.type >= ADD && inst.type <= XOR) || (inst.type >= JLT && inst.type <= JNE)))
        {
            control_color = CG_CONTROL_LINE_ACTIVE_COLOR;
        }

        // First line, down from decoder
        const int first_x = initial_x - line_separation * i;
        const int horizontal_y = GetScreenHeight() / 2 + line_separation * i;
        DrawLineThickness(first_x, decoder_y() + decoder_height(), first_x, horizontal_y, control_color,
                          control_line_width);

        // Line across
        int separation = line_separation * i;
        if (i >= 5)
        {
            separation = line_separation * (register_count - i);
        }
        if (separation < 0)
        {
            separation *= -1;
        }
        const int second_x = get_alu_left_edge() + get_alu_width() + 4 * line_separation + separation;
        DrawLineThickness(first_x - control_line_width / 2, horizontal_y, second_x + control_line_width / 2,
                          horizontal_y, control_color,
                          control_line_width);

        // Line up or down
        const int register_y = registers_start_y() + (single_register_height() + single_register_height() / 8) * i +
            single_register_height() / 3;
        DrawLineThickness(second_x, horizontal_y, second_x, register_y, control_color, control_line_width);

        // Final line across
        DrawLineThickness(second_x - control_line_width / 2, register_y, registers_start_x(), register_y, control_color,
                          control_line_width);

        // Might as well draw the bus lines too
        const int data_line_y = register_y + single_register_height() / 3;
        last_bus_register_y = data_line_y;
        DrawLineThickness(register_bus_x, data_line_y, registers_start_x(), data_line_y, bus_color,
                          data_line_width);
    }

    // Now for data lines

    // Vertical register one
    DrawLineThickness(register_bus_x, registers_start_y() +
                      2 * single_register_height() / 3 - data_line_width / 2 - 1, register_bus_x,
                      last_bus_register_y + data_line_width / 2, bus_color,
                      data_line_width);

    // Control line to bus
    const int middle_bus_x = get_alu_left_edge() + get_alu_width() / 2 - data_line_width / 2;
    DrawLineThickness(decoder_x() + decoder_width() / 2, decoder_y() + decoder_height(),
                      decoder_x() + decoder_width() / 2, 2 * (GetScreenHeight() / 5), control_bus_color,
                      control_line_width);
    DrawLineThickness(decoder_x() + decoder_width() / 2, 2 * (GetScreenHeight() / 5),
                      middle_bus_x, 2 * (GetScreenHeight() / 5), control_bus_color, control_line_width);

    // Vertical one right down the middle
    const int bottom_bus_y = GetScreenHeight() - 3 * control_line_width;
    DrawLineThickness(middle_bus_x, get_alu_top_edge() + get_alu_height(), middle_bus_x, bottom_bus_y, bus_color,
                      data_line_width);

    // Line connect PC and output to bus
    DrawLineThickness((int)((float)GetScreenWidth() - 0.09f * (float)GetScreenHeight()), bottom_bus_y,
                      (int)(0.09f * (float)GetScreenHeight()) + get_inst_box_width(), bottom_bus_y, bus_color,
                      data_line_width);

    // Connect registers
    DrawLineThickness(middle_bus_x, last_bus_register_y, register_bus_x, last_bus_register_y, bus_color,
                      data_line_width);

    // Connect comparator
    DrawLineThickness(get_cmp_left_edge() + get_cmp_width(), get_cmp_top_edge() + get_cmp_height() / 2, middle_bus_x,
                      get_cmp_top_edge() + get_cmp_height() / 2, bus_color,
                      data_line_width);

    // Bus value text
    char bus_text[32];
    if (state->bus_value > 0)
    {
        sprintf(bus_text, " Bus Value: %i", state->bus_value);
    }
    else
    {
        strcpy(bus_text, " Bus Value: None");
    }

    DrawTextEx(state->font, bus_text, (Vector2){(float)middle_bus_x, (float)(bottom_bus_y - 24)}, (float)24, 2,
               bus_color);
}
