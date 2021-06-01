#ifndef __FUNCTIONAL_UNIT_HPP__
#define __FUNCTIONAL_UNIT_HPP__

class Adders;
class Multipliers;

#include "common.hpp"
#include "register_file.hpp"
#include "reservation_stations.hpp"

class Adders {
private:
	bool busy[FUNC_UNIT_ADD_NUM];

public:
	Adders ();
	bool get_busy ();
	void assign_task (res_sta_symbol_t src, op_enum op, data_t r1, data_t r2, Register_file &rf, Reservation_stations &rs);
};

class Multipliers {
private:
	bool busy[FUNC_UNIT_MUL_NUM];

public:
	Multipliers ();
	bool get_busy ();
	void assign_task (res_sta_symbol_t src, op_enum op, data_t r1, data_t r2, Register_file &rf, Reservation_stations &rs);
};

#endif
