#include "common.hpp"
#include "riscv_instr.hpp"
#include "issuer.hpp"

Issuer::Issuer (Register_file *rf_, Reservation_stations *rs_) {
    rf = rf_;
    rs = rs_;
}

void Issuer::__decode (instr_t instr_i, op_t &op_o, reg_stat_t &rs1_o, reg_stat_t &rs2_o) {
    // TODO
}

void Issuer::issue (instr_t instr_i, bool &success_o) {
    op_t op;
    reg_stat_t rs1, rs2;
    __decode(instr_i, op, rs1, rs2);
    if (!rs->get_valid(op)) {
        success_o = false;
        return;
    }
    rs->issue(op, rs1, rs2);
}
