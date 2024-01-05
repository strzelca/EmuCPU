# EmuCPU

<p align="center">
<img src="https://raw.githubusercontent.com/strzelca/EmuCPU/main/.github/imgs/diagram.png" width=500>
</p>

## What is EmuCPU?
EmuCPU is an emulator for a CPU I designed. 

* It's 16 bit
* It has 2 registers (A and B) and a Program Counter
* Its ISA has 6 instructions
* Program it's stored in a Memory, which size is defined at compile time.

## What is the ISA?
The ISA is the instruction set of the CPU. It has 6 instructions, MOV, ADD, SUB, MUL, DIV and INC.
Math it's done with using boolean logic, not C math operators.

## How do I use it?
There's not a method to load a program from a file, so you have to write it in the code. In main.c there's an array called 'prog' which contains the program. You can write something in an ASM-like language.