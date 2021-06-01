#ifndef __RESERVATION_STATIONS_HPP__
#define __RESERVATION_STATIONS_HPP__

class Reservation_stations;

#include "common.hpp"
#include "functional_unit.hpp"

class Reservation_stations {
private:
	res_sta_entry_t entry[RES_STA_TOTAL_NUM];

public:
	Reservation_stations ();
	bool get_valid (op_enum op);
	bool __get_valid (op_enum op_i, int &index_o);
	void issue (op_enum op, reg_stat_t r1, reg_stat_t r2);
	void try_assign_task (Adders &adders, Multipliers &multipliers);
	void write_from_CDB (res_sta_symbol_t sym, data_t value);
};

#endif
