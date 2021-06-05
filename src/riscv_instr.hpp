#ifndef __RISCV_INSTR_HPP__
#define __RISCV_INSTR_HPP__

typedef uint32_t RISCV_code_t;
// opcode
const RISCV_code_t OP_R_type = 0b0110011; // 0x0c 0x3
const RISCV_code_t OP_I_type = 0b0010011; // 0x04 0x3
const RISCV_code_t OP_S_tpye = 0b0000011; // 0x00 0x3
// funct3
const RISCV_code_t F3_ADD = 0b000; // 0x0
const RISCV_code_t F3_SUB = 0b000; // 0x0
const RISCV_code_t F3_MUL = 0b000; // 0x0
const RISCV_code_t F3_DIV = 0b100; // 0x4
// funct7
const RISCV_code_t F7_ADD = 0b0000000; // 0x00
const RISCV_code_t F7_SUB = 0b0100000; // 0x20
const RISCV_code_t F7_MUL = 0b0000001; // 0x01
const RISCV_code_t F7_DIV = 0b0000001; // 0x01

#endif
