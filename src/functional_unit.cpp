#include "functional_unit.hpp"
#include "common.hpp"

Adders::Adders (CDB *cdb_) {
	cdb = cdb_;
}

bool Adders::get_busy () {
	for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i)
		if (!busy[i])
			return false;
	return true;
}

void Adders::assign_task (res_sta_symbol_t src, op_t op, data_t r1, data_t r2) {
	data_t result;
	switch (op) {
	case OP_ADD:
		result.int_data = r1.int_data + r2.int_data;
		break;

	case OP_SUB:
		result.int_data = r1.int_data - r2.int_data;
		break;

	default:
		result.int_data = 0;
	}

	cdb->broadcast(src, result);
}

Multipliers::Multipliers (CDB *cdb_) {
	cdb = cdb_;
}

bool Multipliers::get_busy () {
	// TODO
	return false;
}

void Multipliers::assign_task (res_sta_symbol_t src, op_t op, data_t r1, data_t r2) {
	// TODO
}
