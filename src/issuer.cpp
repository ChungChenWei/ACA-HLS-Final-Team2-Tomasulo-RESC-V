#include "common.hpp"
#include "riscv_instr.hpp"
#include "issuer.hpp"
namespace Issuer {

void __decode (Register_file &rf, instr_t instr_i, op_enum &op_o, reg_stat_t &rs1_o, reg_stat_t &rs2_o) {
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
	RISCV_code_t funct  = (funct7 << 3) | funct3;

	int rd_addr  = (instr_i >> 7) & 0b11111;
	int rs1_addr = (instr_i >> 15) & 0b11111;
	int rs2_addr = (instr_i >> 20) & 0b11111;

	// TODO
	switch(opcode) {
	case OP_R_type:
		// operation
		if (funct3 == F3_ADD && funct7 == F7_ADD) {
			op_o = OP_ADD;
		} else if (funct3 == F3_SUB && funct7 == F7_SUB) {
			op_o = OP_SUB;
		} else if (funct3 == F3_MUL && funct7 == F7_MUL) {
			op_o = OP_MUL;
		} else if (funct3 == F3_DIV && funct7 == F7_DIV) {
			op_o = OP_DIV;
		} else {
			op_o = OP_NUL;
		}
		// registers
		rf.read(rs1_addr, rs1_o);
		rf.read(rs2_addr, rs2_o);
		break;
	case OP_I_type:
		break;
	}
}

void issue (Register_file &rf, Reservation_stations &rs, instr_t instr_i, bool &success_o) {
    op_enum op;
    reg_stat_t rs1, rs2;
    __decode(rf, instr_i, op, rs1, rs2);
    if (!rs.get_valid(op)) {
        success_o = false;
        return;
    }
    rs.issue(op, rs1, rs2);
    success_o = true;
}

} // namespace Issuer
