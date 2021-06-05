#ifndef __RISCV_CODE_RV32I_HPP__
#define __RISCV_CODE_RV32I_HPP__

#include "common.hpp"

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

#endif
