#ifndef COMPUTER_GAME_INSTRUCTIONS_H
#define COMPUTER_GAME_INSTRUCTIONS_H
#include <stdint.h>

enum InstType
{
    NOOP,
    MOVE,
    LOAD,
    ADD,
    SUB,
    AND,
    OR,
    NAND,
    XOR,
    JLT,
    JLE,
    JGT,
    JGE,
    JEQ,
    JNE,
};

struct Instruction
{
    enum InstType type;
    uint8_t first_operand;
    uint8_t second_operand;
    uint8_t show_ops;
};
#endif //COMPUTER_GAME_INSTRUCTIONS_H