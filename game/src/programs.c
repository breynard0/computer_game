#include "instructions.h"

#define inst(type, o1, o2) (struct Instruction) {type, o1, o2, 1}
#define inst_noop(type) (struct Instruction) {type, 0, 0, 0}
#define OUT 8

struct Instruction fibonacci[256] = {
    inst(LOAD, 13, 3),
    inst(LOAD, 1, 4),

    inst(MOVE, 4, 1),
    inst(MOVE, 5, 2),
    inst_noop(ADD),
    inst(MOVE, 5, 4),
    inst(MOVE, 0, 5),

    inst(MOVE, 3, 1),
    inst(LOAD, 1, 2),
    inst_noop(SUB),
    inst(MOVE, 0, 3),
    inst(LOAD, 2, 0),
    inst(MOVE, 3, 1),
    inst(LOAD, 0, 2),
    inst_noop(JGT),

    inst(LOAD, 19, 0),
    inst(LOAD, 1, 1),
    inst(LOAD, 2, 2),
    inst(MOVE, 5, OUT),
    inst_noop(JNE)
};

struct Instruction factorial[256] = {
    inst(LOAD, 5, 6),
    inst(LOAD, 1, 7),
    inst(LOAD, 2, 4),

    inst(MOVE, 4, 3),
    inst(LOAD, 0, 5),

    inst(MOVE, 5, 1),
    inst(MOVE, 7, 2),
    inst_noop(ADD),
    inst(MOVE, 0, 5),

    inst(MOVE, 3, 1),
    inst(LOAD, 1, 2),
    inst_noop(SUB),
    inst(MOVE, 0, 3),

    inst(MOVE, 3, 1),
    inst(LOAD, 0, 2),
    inst(LOAD, 5, 0),
    inst_noop(JGT),

    inst(MOVE, 5, 7),

    inst(MOVE, 4, 1),
    inst(LOAD, 1, 2),
    inst_noop(ADD),
    inst(MOVE, 0, 4),

    inst(MOVE, 4, 1),
    inst(MOVE, 6, 2),
    inst(LOAD, 3, 0),
    inst_noop(JLE),
    
    inst(LOAD, 1, 1),
    inst(LOAD, 2, 2),
    inst(LOAD, 30, 0),
    inst(MOVE, 7, OUT),
    inst_noop(JNE)
};

struct Instruction gcd[256] = {
    inst(LOAD, 105, 3),
    inst(LOAD, 252, 4),
    
    inst(MOVE, 3, 1),
    inst(MOVE, 4, 2),
    inst(LOAD, 10, 0),
    inst_noop(JGT),
    
    inst(MOVE, 2, 3),
    inst(MOVE, 1, 4),
    inst(LOAD, 12, 0),
    inst_noop(JLE),
    
    inst(MOVE, 1, 3),
    inst(MOVE, 2, 4),
    
    inst(MOVE, 3, 1),
    inst(MOVE, 4, 2),
    inst_noop(SUB),
    inst(MOVE, 0, 1),
    inst(LOAD, 14, 0),
    inst_noop(JGT),
    
    inst(MOVE, 1, 3),
    inst(MOVE, 2, 4),
    inst(LOAD, 0, 2),
    inst(LOAD, 2, 0),
    inst_noop(JNE),
    
    inst(LOAD, 27, 0),
    inst(LOAD, 1, 1),
    inst(LOAD, 2, 2),
    inst(MOVE, 4, OUT),
    inst_noop(JNE)
};
