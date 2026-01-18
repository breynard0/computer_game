#include "main.h"

void eval_computer(GameState* state)
{
    state->bus_value = -1;
    state->alu_answer = -1000;
    state->cmp_answer = -1;
    state->output = 0;
    state->output_changed = 0; // TODO output changed
    
    // TODO simulate an entire computer from scratch
}
