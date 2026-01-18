#include "alu.h"
#include "comparator.h"
#include "main.h"

void eval_computer(GameState* state)
{
    state->bus_value = -1;
    state->alu_answer = -1000;
    state->cmp_answer = -1;
    // state->output = 0;
    state->output_changed = 0;
    state->tentative_program_counter = -1;

    const struct Instruction inst = state->program[state->program_counter];
    const int first = inst.first_operand;
    const int second = inst.second_operand;

    switch (inst.type)
    {
    case MOVE:
        state->bus_value = state->registers[first];
        if (second == 8)
        {
            state->output = state->registers[first];
            state->output_changed = 1;
            break;
        }
        state->registers[second] = state->registers[first];
        break;
    case LOAD:
        state->bus_value = first;
        if (second == 8)
        {
            state->output = first;
            state->output_changed = 1;
            break;
        }
        state->registers[second] = first;
        break;
    case ADD:
    case SUB:
    case AND:
    case OR:
    case NAND:
    case XOR:
        {
            const int answer = eval_alu_inst(inst, state);
            state->bus_value = answer;
            state->alu_answer = answer;
            state->registers[0] = answer;
        }
        break;
    case JLT:
    case JLE:
    case JGT:
    case JGE:
    case JEQ:
    case JNE:
        {
            int answer = eval_cmp_inst(inst, state);
            if (answer != 0)
            {
                answer = 1;
                state->bus_value = state->registers[0];
                state->tentative_program_counter = state->registers[0];
            }
            state->cmp_answer = answer;
        }
        break;
    case NOOP:
        break;
    }
}
