#include <iostream>
#include "functional_unit.hpp"

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

Adders::Adders () {
    for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i) {
        counter[i] = 0;
        busy[i] = 0;
    }
}

void Adders::every_cycle (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta) {
//#pragma HLS PIPELINE
    if (!from_res_sta.empty()){
        auto input = from_res_sta.read();
        int index = input.func_unit_index;
        busy[index] = true;

        result[index].src = input.src;
        switch (input.op) {
        case OP_ADD:
        case OP_ADDI:
            result[index].value.int_data = input.r1.int_data + input.r2.int_data;
            break;

        case OP_SUB:
            result[index].value.int_data = input.r1.int_data - input.r2.int_data;
            break;

        default:
            result[index].value.int_data = 0;
        }
    }

    for (int i = 0; i < FUNC_UNIT_ADD_NUM; ++i) {
        if (busy[i]) {
            counter[i] += 1;
            if (counter[i] == FUNC_UNIT_ADD_DURATION) {
                counter[i] = 0;
                to_res_sta.write(result[i]); // CDB.write()
                busy[i] = false;
            }
        }
    }
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

Multipliers::Multipliers () {
    for (int i = 0; i < FUNC_UNIT_MUL_NUM; ++i) {
        counter[i] = 0;
        busy[i] = 0;
    }
}

void Multipliers::every_cycle (res_sta_assign_task_stream_t &from_res_sta, func_unit_finish_task_stream_t &to_res_sta) {
//#pragma HLS PIPELINE
    if (!from_res_sta.empty()) {
        auto input = from_res_sta.read();
        int index = input.func_unit_index;
        busy[index] = true;

        result[index].src = input.src;
        switch (input.op) {
        case OP_MUL:
            result[index].value.int_data = input.r1.int_data * input.r2.int_data;
            break;

        default:
            result[index].value.int_data = 0;
        }
    }

    for (int i = 0; i < FUNC_UNIT_MUL_NUM; ++i) {
        if (busy[i]) {
            counter[i] += 1;
            if (counter[i] == FUNC_UNIT_MUL_DURATION) {
                counter[i] = 0;
                to_res_sta.write(result[i]); // CDB.write()
                busy[i] = false;
            }
        }
    }
}
