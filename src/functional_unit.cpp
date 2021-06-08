#include <iostream>
#include "functional_unit.hpp"
#include "CDB.hpp"

Adders_status::Adders_status () {
    for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i) {
        busy[i] = false;
    }
}

bool Adders_status::get_busy (int &index_o) {
    for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i)
#pragma HLS UNROLL
        if (!busy[i]) {
            index_o = i;
            return false;
        }
    return true;
}

void Adders_status::set_busy (int index) {
    busy[index] = true;
}

void Adders_status::unset_busy (int index) {
    busy[index] = false;
}

void Adders_status::print_debug () {
    std::cout << "    adders_status: ";
    for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i)
        std::cout << busy[i];
    std::cout << std::endl;
}

Adders::Adders () {}

void Adders::run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta) {
//#pragma HLS PIPELINE
    if (from_res_sta.empty())
    	return;

    auto input = from_res_sta.read();

    __func_unit_finish_task_interface_t result;
    result.src = input.src;
    switch (input.op) {
    case OP_ADD:
    case OP_ADDI:
        result.value.int_data = input.r1.int_data + input.r2.int_data;
        break;

    case OP_SUB:
        result.value.int_data = input.r1.int_data - input.r2.int_data;
        break;

    default:
        result.value.int_data = 0;
    }

    to_res_sta.write(result); // CDB.write()
}

Multipliers_status::Multipliers_status () {
    for (int i = 0; i < FUNC_UNIT_MUL_NUM; ++i) {
        busy[i] = false;
    }
}

bool Multipliers_status::get_busy (int &index_o) {
    for (int i = 0; i < FUNC_UNIT_MUL_NUM; ++i)
#pragma HLS UNROLL
        if (!busy[i]) {
            index_o = i;
            return false;
        }
    return true;
}

void Multipliers_status::set_busy (int index) {
    busy[index] = true;
}

void Multipliers_status::unset_busy (int index) {
    busy[index] = false;
}

void Multipliers_status::print_debug () {
    std::cout << "    multipliers_status: ";
    for (int i = 0; i < FUNC_UNIT_MUL_NUM; ++i)
        std::cout << busy[i];
    std::cout << std::endl;
}

Multipliers::Multipliers () {}

void Multipliers::run_task (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta) {
//#pragma HLS PIPELINE
    if (from_res_sta.empty())
    	return;

    auto input = from_res_sta.read();

    __func_unit_finish_task_interface_t result;
    result.src = input.src;
    switch (input.op) {
    case OP_MUL:
        result.value.int_data = input.r1.int_data * input.r2.int_data;
        break;

    // case OP_DIV:
    //     result.value.int_data = input.r1.int_data / input.r2.int_data;
    //     break;

    default:
        result.value.int_data = 0;
    }

    to_res_sta.write(result); // CDB.write()
}
