#ifndef __RISCV_INSTR_HPP__
#define __RISCV_INSTR_HPP__

#include "common.hpp"
#include <string>
#include <iostream>

namespace RISCV {

// opcode
const RISCV_code_t OP_R_type = 0b0110011; // 0x0c 0x3
const RISCV_code_t OP_I_type = 0b0010011; // 0x04 0x3
const RISCV_code_t OP_S_tpye = 0b0100011; // 0x08 0x3
const RISCV_code_t OP_L_tpye = 0b0000011; // 0x00 0x3
const RISCV_code_t OP_B_tpye = 0b1100011; // 0x18 0x3

// rv32i
// funct3
// I type
const RISCV_code_t F3_ADDI = 0b000; // 0x0
const RISCV_code_t F3_SLLI = 0b001; // 0x1
const RISCV_code_t F3_SLTI = 0b010; // 0x2
const RISCV_code_t F3_XORI = 0b100; // 0x4
const RISCV_code_t F3_SRLI = 0b101; // 0x5
const RISCV_code_t F3_SRAI = 0b101; // 0x5
const RISCV_code_t F3_ORI  = 0b110; // 0x6
const RISCV_code_t F3_ANDi = 0b111; // 0x7
// R type
const RISCV_code_t F3_ADD = 0b000; // 0x0
const RISCV_code_t F3_SUB = 0b000; // 0x0
const RISCV_code_t F3_SLL = 0b001; // 0x1
const RISCV_code_t F3_SLT = 0b010; // 0x2
const RISCV_code_t F3_XOR = 0b100; // 0x4
const RISCV_code_t F3_SRL = 0b101; // 0x5
const RISCV_code_t F3_SRA = 0b101; // 0x5
const RISCV_code_t F3_OR  = 0b110; // 0x6
const RISCV_code_t F3_AND = 0b111; // 0x7
// S type
const RISCV_code_t F3_SW = 0b010; // 0x2
// L type
const RISCV_code_t F3_LW = 0b010; // 0x2
// B type
const RISCV_code_t F3_BEQ = 0b000; // 0x0
const RISCV_code_t F3_BNE = 0b001; // 0x1
const RISCV_code_t F3_BLT = 0b100; // 0x4
const RISCV_code_t F3_BGE = 0b101; // 0x5

// funct7
// I type
const RISCV_code_t F7_SLLI = 0b0000000; // 0x00
const RISCV_code_t F7_SRLI = 0b0000000; // 0x00
const RISCV_code_t F7_SRAI = 0b0100000; // 0x20
// R type
const RISCV_code_t F7_ADD = 0b0000000; // 0x00
const RISCV_code_t F7_SUB = 0b0100000; // 0x20
const RISCV_code_t F7_SLL = 0b0000000; // 0x00
const RISCV_code_t F7_SLT = 0b0000000; // 0x00
const RISCV_code_t F7_XOR = 0b0000000; // 0x00
const RISCV_code_t F7_SRL = 0b0000000; // 0x00
const RISCV_code_t F7_SRA = 0b0100000; // 0x20
const RISCV_code_t F7_OR  = 0b0000000; // 0x00
const RISCV_code_t F7_AND = 0b0000000; // 0x00

// rv32m
// funct3
const RISCV_code_t F3_MUL = 0b000; // 0x0
const RISCV_code_t F3_DIV = 0b100; // 0x4
// funct7
const RISCV_code_t F7_MUL = 0b0000001; // 0x01
const RISCV_code_t F7_DIV = 0b0000001; // 0x01

void set_instr (std::string instruction_str, instr_t instruction_memory[INSTR_MEM_SIZE]) {
    std::cout << instruction_str;
}

}
#endif
