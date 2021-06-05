#include "common.hpp"
#include "riscv_instr.hpp"
#include "issuer.hpp"
namespace Issuer {

void __decode (Register_file &rf, instr_t instr_i, op_enum &op_o, int &rd_index_o, reg_stat_t &rs1_o, reg_stat_t &rs2_o) {
#pragma HLS inline
    /* RISC-V instruction set
     * [6:0]   opcode
     * [11:7]  rd
     * [14:12] funct3
     * [19:15] rs1
     * [24:20] rs2
     * [31:25] funct7
     */
	RISCV_code_t opcode = instr_i & 0b1111111;
	RISCV_code_t funct3 = (instr_i >> 12) & 0b111;
	RISCV_code_t funct7 = (instr_i >> 25) & 0b1111111;

	int rd_addr  = (instr_i >> 7) & 0b11111;
	int rs1_addr = (instr_i >> 15) & 0b11111;
	int rs2_addr = (instr_i >> 20) & 0b11111;

#ifndef __SYNTHESIS__
	std::cout << "    rd = " << rd_addr << "\t rs1 = " << rs1_addr << "\t rs2 = " << rs2_addr << std::endl;
#endif
	// TODO
	switch (opcode) {
	case RISCV::OP_R_type:
		// operation
		if (funct3 == RISCV::F3_ADD && funct7 == RISCV::F7_ADD) {
			op_o = OP_ADD;
		} else if (funct3 == RISCV::F3_SUB && funct7 == RISCV::F7_SUB) {
			op_o = OP_SUB;
		} else if (funct3 == RISCV::F3_MUL && funct7 == RISCV::F7_MUL) {
			op_o = OP_MUL;
		} else if (funct3 == RISCV::F3_DIV && funct7 == RISCV::F7_DIV) {
			op_o = OP_DIV;
		} else {
			op_o = OP_NUL;
		}
		// registers
		rf.read(rs1_addr, rs1_o);
		rf.read(rs2_addr, rs2_o);
		rd_index_o = rd_addr;
		break;
	case RISCV::OP_I_type:
		if (funct3 == RISCV::F3_ADDI) {
			op_o = OP_ADD;

			rf.read(rs1_addr, rs1_o);
			rs2_o.stat = REG_STAT_SCALAR;
			rs2_o.value.scalar.int_data = (instr_i >> 20) & 0b111111111111;
			rd_index_o = rd_addr;
		}
		break;
	}
}

void issue (Register_file &rf, Reservation_stations &rs, instr_t instr_i, bool &success_o) {
    op_enum op;
	int rd_index;
    reg_stat_t rs1, rs2;
	res_sta_symbol_t rd_sym;
    __decode(rf, instr_i, op, rd_index, rs1, rs2);
    if (!rs.get_valid(op, rd_sym)) {
        success_o = false;
        return;
    }
    rs.issue(op, rd_sym, rs1, rs2);
	rf.write_from_issuer(rd_index, rd_sym);
    success_o = true;
}

} // namespace Issuer
