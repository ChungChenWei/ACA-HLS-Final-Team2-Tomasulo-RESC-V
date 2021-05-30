#ifndef __ISSUER_HPP__
#define __ISSUER_HPP__

#include "common.hpp"
#include "riscv_instr.hpp"
#include "register_file.hpp"
#include "reservation_stations.hpp"

class Issuer {
private:
    Register_file *rf;
    Reservation_stations *rs;

public:
    Issuer (Register_file *rf_, Reservation_stations *rs_);
    void __decode (instr_t instr_i, op_t &op_o, reg_stat_t &rs1_o, reg_stat_t &rs2_o);
    void issue (instr_t instr_i, bool &success_o);
};

#endif
