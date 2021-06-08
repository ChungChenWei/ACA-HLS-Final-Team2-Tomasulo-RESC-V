#include "riscv_instr.hpp"
#include "common.hpp"
#include <bitset>

namespace RISCV {
void split (std::string &input, std::string &output, std::string delimiter) {
    size_t pos  = 0;
    std::string num;

    pos = input.find(delimiter);
    output = input.substr(0, pos);
    input.erase(0, pos + delimiter.length());
}
void split (std::string &input, int &output, std::string delimiter) {
    std::string reg;
    split(input, reg, delimiter);
    if (reg[0] == REG_PREFIX) {
        output = atoi(reg.erase(0,1).c_str());
    } else {
        output = atoi(reg.c_str());
    }
}
void instr_gen (op_enum &ope, int rd, int rs1, int rs2, instr_t &instr) {
    int imm = rs2;
    RISCV_code_t F7;
    RISCV_code_t F3;
    RISCV_code_t OP;

    switch (ope) {
        case OP_ADD:
            OP = OP_R_type;
            F7 = F7_ADD;
            F3 = F3_ADD;
            break;
        case OP_SUB:
            OP = OP_R_type;
            F7 = F7_SUB;
            F3 = F3_SUB;
            break;
        case OP_MUL:
            OP = OP_R_type;
            F7 = F7_MUL;
            F3 = F3_MUL;
            break;
        case OP_DIV:
            OP = OP_R_type;
            F7 = F7_DIV;
            F3 = F3_DIV;
            break;
        case OP_ADDI:
            OP = OP_I_type;
            F3 = F3_ADDI;
            break;
        default:
            OP = OP_NULL_tpye;
            break;
    }
    switch (OP) {
        case OP_R_type:
            instr = (F7 << 25) | (rs2 << 20) | (rs1 << 15) | (F3 << 12) | (rd << 7) | OP_R_type;
            break;
        case OP_I_type:
            instr = (imm << 20) | (rs1 << 15) | (F3 << 12) | (rd << 7) | OP_I_type;
            break;
        case OP_NULL_tpye:
            instr = 0;
            break;
    }

}


void set_instr (std::string instruction_str, instr_t instruction_memory[INSTR_MEM_SIZE]) {
    std::string line_del = "    ";
    std::string arg_del  = ", ";
    std::string cmdline;
    std::string op;

    size_t pos_line = 0;
    int instr_cnt = 0;
    int rd_addr;
    int rs1_addr;
    int rs2_addr;
    int immediate;
    op_enum opcode;

    while ((pos_line = instruction_str.find(line_del)) != std::string::npos) {
        cmdline = instruction_str.substr(0, pos_line);
        instruction_str.erase(0, pos_line + line_del.length());

        if (cmdline.length() != 0) {
            split(cmdline, op, " ");
            if ((op == "ADD" && (opcode = OP_ADD)) || (op == "SUB" && (opcode = OP_SUB)) || (op == "MUL" && (opcode = OP_MUL)) || (op == "DIV" && (opcode = OP_DIV))) {
                split(cmdline, rd_addr, arg_del);
                split(cmdline, rs1_addr, arg_del);
                split(cmdline, rs2_addr, arg_del);
                instr_gen(opcode, rd_addr, rs1_addr, rs2_addr, instruction_memory[instr_cnt]);
            } else if (op == "ADDI" && (opcode = OP_ADDI)) {
                split(cmdline, rd_addr, arg_del);
                split(cmdline, rs1_addr, arg_del);
                split(cmdline, immediate, arg_del);
                instr_gen(opcode, rd_addr, rs1_addr, immediate, instruction_memory[instr_cnt]);
            }
            instr_cnt++;
        }
    }
}

} // namespace RISCV
