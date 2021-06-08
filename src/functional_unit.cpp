#include "functional_unit.hpp"
#include "CDB.hpp"

Adders::Adders () {}

bool Adders::get_busy (int &index_o) {
    for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i)
#pragma HLS UNROLL
        if (!busy[i]) {
            index_o = i;
            return false;
        }
    return true;
}

void Adders::assign_task (int index, res_sta_symbol_t src, op_enum op, data_t r1, data_t r2, Register_file &rf, Reservation_stations &rs) {
// #pragma HLS PIPELINE
    busy[index] = true;
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
    busy[index] = false;
}

Multipliers::Multipliers () {}

bool Multipliers::get_busy (int &index_o) {
    for (int i = 0; i < FUNC_UNIT_MUL_NUM; ++i)
#pragma HLS UNROLL
        if (!busy[i]) {
            index_o = i;
            return false;
        }
    return true;
}

void Multipliers::assign_task (int index, res_sta_symbol_t src, op_enum op, data_t r1, data_t r2, Register_file &rf, Reservation_stations &rs) {
// #pragma HLS PIPELINE
    busy[index] = true;
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
    busy[index] = false;
}
