#ifndef __FUNCTIONAL_UNIT_HPP__
#define __FUNCTIONAL_UNIT_HPP__

class Adders;
class Multipliers;

#include "common.hpp"
#include "CDB.hpp"

class Adders {
private:
	CDB *cdb;
	bool busy[FUNC_UNIT_ADD_NUM];

public:
	Adders (CDB *cdb_);
	bool get_busy ();
	void assign_task (res_sta_symbol_t src, op_t op, data_t r1, data_t r2);
};

class Multipliers {
private:
	CDB *cdb;
	bool busy[FUNC_UNIT_MUL_NUM];

public:
	Multipliers (CDB *cdb_);
	bool get_busy ();
	void assign_task (res_sta_symbol_t src, op_t op, data_t r1, data_t r2);
};

#endif
