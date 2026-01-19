#ifndef COMPUTER_GAME_TEXT_H
#define COMPUTER_GAME_TEXT_H
const char* FIRST =
    "Stage 1:\nWelcome! This space will eventually come to hold your very own computer, but you've got to do some work first! Right now, there is a list of instructions along the left side of your screen. You will also notice the program counter and output number displays. The program counter tells us which instruction is currently being processed. In this simulation, the spacebar increments the program counter, bringing us to the next instruction.\n"\
    "Your task is simple: there are two instructions right now, \"ADD\" and \"SUB\". You will either add the two numbers following the instruction code (they're called operands), or subtract the second operand from the first one, depending on which instruction. Place your sum or difference into the output, then increment the program counter with the spacebar. This will give you money, which you can use to upgrade your computer.\n"\
    "You can refer back to this manual at any time through the button in the top right.";
const char* SECOND =
    "Stage 2:\nGreat work! But we've only had a basic calculator, nowhere near a computer. Let's work on fixing that!\n"\
    "There are now three registers, numbered 0, 1, and 2. You can think of these as boxes in which can store numbers for later use. The \"LOAD\" instruction loads the first operand into the register referenced by the second operand. For example, \"LOAD 19 1\" would load the value 19 into register 1. There is also now the \"MOVE\" instruction, which copies what is in the register of the first operand into the register referenced by the second operand. For example, \"MOVE 2 1\" would copy whatever's in register 2 into register 1. Note that register 2 is not modified here, only its value is copied into register 1.\n"\
    "Also, from now on, \"ADD\" and \"SUB\" do not have any operands. If one of them comes up, either add or subtract registers 1 and 2, and store the result in register 0. For now, if a subtraction operation would result in a negative number, just put the positive version.";

const char* THIRD =
    "Stage 3:\nAlright, now you've unlocked the Arithmetic and Logic Unit, or ALU. This component is responsible for all mathematical and logic functions of the computer. In this simulation, you can drag any ALU commands directly over and it will automatically tell you the answer.\n"\
    "As for ALU commands, these include \"ADD\" and \"SUB\". However, there are four new commands, \"AND\", \"OR\", \"NAND\", and \"XOR\". You do not need to concern yourself with exactly what they do, since grabbing instructions and dragging them over the ALU will automatically compute them. If you are interested, these are called \"bitwise operations\", similar to regular math operations just more computer-y. Just like addition and subtraction, they work on the values in registers 1 and 2 with the answer being stored in register 0.";

const char* FOURTH =
    "Stage 4:\nThe comparator is now unlocked! As the name implies, this component compares two values, specifically those in registers 1 and 2. There have also been several \"JUMP\" instructions added, with modifiers \"LT\" (less than), \"LE\" (less than or equal), \"GT\" (greater than), \"GE\", (greater than or equal), \"EQ\" (equal), \"NE\" (not equal). If a jump instruction is dragged over the comparator, it will tell you if the condition is true or not.\n"\
    "If the condition is true, then the program counter should be set to the value of register 0. Otherwise, do nothing and move on to the next instruction.\n"\
    "It is now possible for the generated instructions to form an infinite loop. If this happens, press 'R' to reset the instructions list.";

const char* FIFTH =
    "Stage 5:\nYou have now added the decoder and bus. The bus is a bunch of wires that connect all registers, the ALU, the comparator, the program counter, and the output. It will automatically carry values between them. However, the bus is directly connected to all of them, so how do we know where the value on the bus is meant to go? This is where the decoder comes in. It will look at the current instruction and send control signals to configure things where needed. These signals mean that you no longer have to manually drag and set things, all of that is handled automatically. Your only task now is incrementing the program counter, until you can automate that too!";

const char* SIXTH =
    "Stage 6:\nCongratulations! You have now fully upgraded your computer, and you can press the period key to enable the automatic clock. There are also five more registers, expanding what this computer is able to calculate tremendously.\n"\
    "Also unlocked are some actual programs to run on the computer. Fibonacci computes the 13th Fibonacci number, Factorial computes the value of 5!, and GCD computes the greatest common divisor between 252 and 105 using the Euclidean algorithm.\n"\
    "This computer can still be upgraded in many ways, but I hope this gives a glimpse into how deceptively simple a computing machine is when built step-by-step. They really are just calculators that can remember numbers to pass them around later.\n"\
    "One last though to leave you with: what if I linked something like the brightness of a light bulb to the value in one of the registers? Then, I could control something in the real world with this computer. This technique is called memory mapping, and it is used everywhere without most people realizing it.";
#endif //COMPUTER_GAME_TEXT_H
