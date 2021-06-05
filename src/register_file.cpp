#include "register_file.hpp"

Register_file::Register_file () {
    for (int i = 0; i < REGISTER_NUM; ++i) {
        reg[i].stat = REG_STAT_SCALAR;
        reg[i].value.scalar.int_data = 0;
    }
}

void Register_file::read (int index, reg_stat_t &reg_o) {
    reg_o = reg[index];
}

void Register_file::write_from_issuer (int index, res_sta_symbol_t reg_i) {
    reg[index].stat = REG_STAT_SYMBOL;
    reg[index].value.symbol = reg_i;
}

void Register_file::write_from_CDB (res_sta_symbol_t sym, data_t value) {
    for (int i = 0; i < REGISTER_NUM; ++i) {
        if (reg[i].stat == REG_STAT_SYMBOL && reg[i].value.symbol == sym) {
            reg[i].stat = REG_STAT_SCALAR;
            reg[i].value.scalar = value;
        }
    }
}
