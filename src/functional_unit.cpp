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

void Adders::run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta, Register_file &rf, Reservation_stations &rs) {
//#pragma HLS PIPELINE
    if (from_res_sta.empty())
    	return;

    auto input = from_res_sta.read();

    int index;
    get_busy(index);
    busy[index] = true;

    data_t result;
    switch (input.op) {
    case OP_ADD:
    case OP_ADDI:
        result.int_data = input.r1.int_data + input.r2.int_data;
        break;

    case OP_SUB:
        result.int_data = input.r1.int_data - input.r2.int_data;
        break;

    default:
        result.int_data = 0;
    }

    to_res_sta.write(input.src);
    CDB_broadcast(rf, rs, input.src, result);
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

void Multipliers::run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta, Register_file &rf, Reservation_stations &rs) {
//#pragma HLS PIPELINE
    if (from_res_sta.empty())
    	return;

    auto input = from_res_sta.read();

    int index;
    get_busy(index);
    busy[index] = true;

    data_t result;
    switch (input.op) {
    case OP_MUL:
        result.int_data = input.r1.int_data * input.r2.int_data;
        break;

//    case OP_DIV:
//        result.int_data = input.r1.int_data / input.r2.int_data;
//        break;

    default:
        result.int_data = 0;
    }

    to_res_sta.write(input.src);
    CDB_broadcast(rf, rs, input.src, result);
    busy[index] = false;
}
