#ifndef __RESERVATION_STATIONS_HPP__
#define __RESERVATION_STATIONS_HPP__

class Reservation_stations;

#include "common.hpp"
#include "functional_unit.hpp"
#include "register_file.hpp"

class Reservation_stations {
private:
    res_sta_entry_t entry[RES_STA_TOTAL_NUM];

public:
    Reservation_stations ();
    bool get_valid (op_enum op_i, res_sta_symbol_t &sym_o);
    void issue (op_enum op, res_sta_symbol_t rd_index, reg_stat_t r1, reg_stat_t r2);
    void try_assign_task (Adders &adders, Multipliers &multipliers, res_sta_assign_task_stream_t &to_adder, func_unit_finish_task_stream_t &from_adder, res_sta_assign_task_stream_t &to_multiplier, func_unit_finish_task_stream_t &from_multiplier);
    void write_from_CDB (res_sta_symbol_t sym, data_t value);
};

#endif
