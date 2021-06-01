#include "common.hpp"
#include "riscv_instr.hpp"
#include "issuer.hpp"
namespace Issuer {

void __decode (Register_file &rf, instr_t instr_i, op_t &op_o, reg_stat_t &rs1_o, reg_stat_t &rs2_o) {
    // TODO
    op_o = 0;
    rs1_o.stat = REG_STAT_SCALAR;
    rs1_o.value.scalar.int_data = 0;
    rs2_o.stat = REG_STAT_SCALAR;
    rs2_o.value.scalar.int_data = 0;
}

void issue (Register_file &rf, Reservation_stations &rs, instr_t instr_i, bool &success_o) {
    op_t op;
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
