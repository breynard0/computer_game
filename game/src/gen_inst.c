#include <raylib.h>

#include "main.h"
#include "instructions.h"

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) < (b) ? (b) : (a))

void regen_instructions(GameState* state)
{
    for (int i = 0; i < 256; i++)
    {
        struct Instruction inst = {.type = NOOP, .first_operand = 0, .second_operand = 0, 1};
        do
        {
            switch (state->sim_stage)
            {
            case STAGE_FIRST_PC_ADD_SUB:
                if (GetRandomValue(0, 1))
                {
                    inst = (struct Instruction){
                        .type = ADD, .first_operand = GetRandomValue(0, 16), .second_operand = GetRandomValue(0, 16), 1
                    };
                }
                else
                {
                    const int first = GetRandomValue(0, 16);
                    const int second = GetRandomValue(0, 16);
                    inst = (struct Instruction){
                        .type = SUB, .first_operand = max(first, second), .second_operand = min(first, second), 1
                    };
                }
                break;
            case STAGE_SECOND_REGISTERS:
                switch (GetRandomValue(0, 3))
                {
                case 0:
                    inst = (struct Instruction){
                        .type = ADD, .first_operand = 0, .second_operand = 0, 0
                    };
                    break;
                case 1:
                    {
                        inst = (struct Instruction){
                            .type = SUB, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 2:
                    {
                        int second = GetRandomValue(0, 3);
                        if (second == 3)
                        {
                            second = 8;
                        }
                        inst = (struct Instruction){
                            .type = MOVE, .first_operand = GetRandomValue(0, 2), .second_operand = second, 1
                        };
                    }
                    break;
                case 3:
                    inst = (struct Instruction){
                        .type = LOAD, .first_operand = GetRandomValue(0, 127), .second_operand = GetRandomValue(0, 2), 1
                    };
                    break;
                default:
                    break;
                }
                break;
            case STAGE_THIRD_ALU:
                switch (GetRandomValue(0, 11))
                {
                case 0:
                    inst = (struct Instruction){
                        .type = ADD, .first_operand = 0, .second_operand = 0, 0
                    };
                    break;
                case 1:
                    {
                        inst = (struct Instruction){
                            .type = SUB, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 2:
                case 8:
                case 9:
                    {
                        int second = GetRandomValue(0, 3);
                        if (second == 3)
                        {
                            second = 8;
                        }
                        inst = (struct Instruction){
                            .type = MOVE, .first_operand = GetRandomValue(0, 2), .second_operand = second, 1
                        };
                    }
                    break;
                case 3:
                case 10:
                case 11:
                    inst = (struct Instruction){
                        .type = LOAD, .first_operand = GetRandomValue(0, 255), .second_operand = GetRandomValue(0, 2), 1
                    };
                    break;
                case 4:
                    {
                        inst = (struct Instruction){
                            .type = AND, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 5:
                    {
                        inst = (struct Instruction){
                            .type = OR, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 6:
                    {
                        inst = (struct Instruction){
                            .type = NAND, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 7:
                    {
                        inst = (struct Instruction){
                            .type = XOR, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                default:
                    break;
                }
                break;
            case STAGE_FOURTH_JUMP:
            case STAGE_FIVE_DECODER_BUS:
                switch (GetRandomValue(0, 19))
                {
                case 0:
                case 10:
                case 11:
                    inst = (struct Instruction){
                        .type = ADD, .first_operand = 0, .second_operand = 0, 0
                    };
                    break;
                case 1:
                case 12:
                case 13:
                    {
                        inst = (struct Instruction){
                            .type = SUB, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 2:
                case 14:
                case 15:
                case 19:
                    {
                        int second = GetRandomValue(0, 3);
                        if (second == 3)
                        {
                            second = 8;
                        }
                        inst = (struct Instruction){
                            .type = MOVE, .first_operand = GetRandomValue(0, 2), .second_operand = second, 1
                        };
                    }
                    break;
                case 3:
                case 16:
                case 17:
                case 18:
                    inst = (struct Instruction){
                        .type = LOAD, .first_operand = GetRandomValue(0, 255), .second_operand = GetRandomValue(0, 2), 1
                    };
                    break;
                case 4:
                    {
                        inst = (struct Instruction){
                            .type = AND, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 5:
                    {
                        inst = (struct Instruction){
                            .type = OR, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 6:
                    {
                        inst = (struct Instruction){
                            .type = NAND, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 7:
                    {
                        inst = (struct Instruction){
                            .type = XOR, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 8:
                case 9:
                    switch (GetRandomValue(0, 5))
                    {
                    case 0:
                        {
                            inst = (struct Instruction){
                                .type = JNE, .first_operand = GetRandomValue(0, 2),
                                .second_operand = GetRandomValue(0, 2),
                                0
                            };
                        }
                        break;
                    case 1:
                        {
                            inst = (struct Instruction){
                                .type = JGT, .first_operand = GetRandomValue(0, 2),
                                .second_operand = GetRandomValue(0, 2),
                                0
                            };
                        }
                        break;
                    case 2:
                        {
                            inst = (struct Instruction){
                                .type = JGE, .first_operand = GetRandomValue(0, 2),
                                .second_operand = GetRandomValue(0, 2),
                                0
                            };
                        }
                        break;
                    case 3:
                        {
                            inst = (struct Instruction){
                                .type = JLT, .first_operand = GetRandomValue(0, 2),
                                .second_operand = GetRandomValue(0, 2),
                                0
                            };
                        }
                        break;
                    case 4:
                        {
                            inst = (struct Instruction){
                                .type = JLE, .first_operand = GetRandomValue(0, 2),
                                .second_operand = GetRandomValue(0, 2),
                                0
                            };
                        }
                        break;
                    case 5:
                        {
                            inst = (struct Instruction){
                                .type = JEQ, .first_operand = GetRandomValue(0, 2),
                                .second_operand = GetRandomValue(0, 2),
                                0
                            };
                        }
                    default: break;
                    }
                    break;
                default:
                    break;
                }
                break;
            case STAGE_SIX_MEMORY_AND_CLOCK:
                switch (GetRandomValue(0, 19))
                {
                case 0:
                case 10:
                case 11:
                    inst = (struct Instruction){
                        .type = ADD, .first_operand = 0, .second_operand = 0, 0
                    };
                    break;
                case 1:
                case 12:
                case 13:
                    {
                        inst = (struct Instruction){
                            .type = SUB, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 2:
                case 14:
                case 15:
                case 16:
                    {
                        inst = (struct Instruction){
                            .type = MOVE, .first_operand = GetRandomValue(0, 7), .second_operand = GetRandomValue(0, 8),
                            1
                        };
                    }
                    break;
                case 3:
                case 17:
                case 18:
                case 19:
                    inst = (struct Instruction){
                        .type = LOAD, .first_operand = GetRandomValue(0, 255), .second_operand = GetRandomValue(0, 8), 1
                    };
                    break;
                case 4:
                    {
                        inst = (struct Instruction){
                            .type = AND, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 5:
                    {
                        inst = (struct Instruction){
                            .type = OR, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 6:
                    {
                        inst = (struct Instruction){
                            .type = NAND, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 7:
                    {
                        inst = (struct Instruction){
                            .type = XOR, .first_operand = 0, .second_operand = 0, 0
                        };
                    }
                    break;
                case 8:
                case 9:
                    switch (GetRandomValue(0, 5))
                    {
                    case 0:
                        {
                            inst = (struct Instruction){
                                .type = JNE, .first_operand = GetRandomValue(0, 7),
                                .second_operand = GetRandomValue(0, 7),
                                0
                            };
                        }
                        break;
                    case 1:
                        {
                            inst = (struct Instruction){
                                .type = JGT, .first_operand = GetRandomValue(0, 7),
                                .second_operand = GetRandomValue(0, 7),
                                0
                            };
                        }
                        break;
                    case 2:
                        {
                            inst = (struct Instruction){
                                .type = JGE, .first_operand = GetRandomValue(0, 7),
                                .second_operand = GetRandomValue(0, 7),
                                0
                            };
                        }
                        break;
                    case 3:
                        {
                            inst = (struct Instruction){
                                .type = JLT, .first_operand = GetRandomValue(0, 7),
                                .second_operand = GetRandomValue(0, 7),
                                0
                            };
                        }
                        break;
                    case 4:
                        {
                            inst = (struct Instruction){
                                .type = JLE, .first_operand = GetRandomValue(0, 7),
                                .second_operand = GetRandomValue(0, 7),
                                0
                            };
                        }
                        break;
                    case 5:
                        {
                            inst = (struct Instruction){
                                .type = JEQ, .first_operand = GetRandomValue(0, 7),
                                .second_operand = GetRandomValue(0, 7),
                                0
                            };
                        }
                        break;
                    default: break;
                    }
                default:
                    break;
                }
                break;
            }
        }
        while (i != 0 && inst.type == state->program[i - 1].type);

        state->program[i] = inst;
    }

    // Make the first few load calls
    if (state->sim_stage >= STAGE_SECOND_REGISTERS)
    {
        int used_nums[8] = {};
        int used_nums_len = 0;
        int amount = 4;
        if (state->sim_stage >= STAGE_SIX_MEMORY_AND_CLOCK)
        {
            amount = 6;
        }
        for (int idx = 0; idx < amount; idx++)
        {
            int second;
            int found = false;
            do
            {
                second = GetRandomValue(0, 3);
                if (second == 3) second = 8;
                if (state->sim_stage >= STAGE_SIX_MEMORY_AND_CLOCK && idx > amount / 2)
                {
                    second = GetRandomValue(0, 8);
                }
                found = false;
                for (int j = 0; j < used_nums_len; j++)
                {
                    if (used_nums[j] == second)
                    {
                        found = true;
                    }
                }
                used_nums[used_nums_len] = second;
                used_nums_len++;
            }
            while (found);

            int max = 255;
            if (state->sim_stage <= STAGE_SECOND_REGISTERS) max = 96;

            state->program[idx] = (struct Instruction){
                .type = LOAD, .first_operand = GetRandomValue(0, 255), .second_operand = second, 1
            };
        }
    }
    state->program_counter = 0;
}
