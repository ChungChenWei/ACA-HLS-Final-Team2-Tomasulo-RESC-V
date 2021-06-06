#include "functional_unit.hpp"
#include "CDB.hpp"

Adders::Adders () {}

bool Adders::get_busy () {
	for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i)
		if (!busy[i])
			return false;
	return true;
}

void Adders::assign_task (res_sta_symbol_t src, op_enum op, data_t r1, data_t r2, Register_file &rf, Reservation_stations &rs) {
	data_t result;
	switch (op) {
	case OP_ADD:
	case OP_ADDI:
		result.int_data = r1.int_data + r2.int_data;
		break;

	case OP_SUB:
		result.int_data = r1.int_data - r2.int_data;
		break;

	default:
		result.int_data = 0;
	}

	CDB_broadcast(rf, rs, src, result);
}

Multipliers::Multipliers () {}

bool Multipliers::get_busy () {
	for (int i = 0; i < FUNC_UNIT_MUL_NUM; ++i)
		if (!busy[i])
			return false;
	return true;
}

void Multipliers::assign_task (res_sta_symbol_t src, op_enum op, data_t r1, data_t r2, Register_file &rf, Reservation_stations &rs) {
	data_t result;
	switch (op) {
	case OP_MUL:
		result.int_data = r1.int_data * r2.int_data;
		break;

	case OP_DIV:
		result.int_data = r1.int_data / r2.int_data;
		break;

	default:
		result.int_data = 0;
	}

	CDB_broadcast(rf, rs, src, result);
}
