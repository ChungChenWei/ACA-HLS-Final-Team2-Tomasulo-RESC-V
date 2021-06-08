#include <iostream>
#include "reservation_stations.hpp"

Reservation_stations::Reservation_stations () {
    for (int i = 0; i < RES_STA_TOTAL_NUM; ++i) {
#pragma HLS UNROLL
        entry[i].valid = true;
    }
}

bool Reservation_stations::get_valid (op_enum op_i, res_sta_symbol_t &sym_o) {
    int start, size;
    switch (op_i) {
    case OP_ADD:
    case OP_SUB:
    case OP_ADDI:
        start = RES_STA_ADD_START_INDEX;
        size = RES_STA_ADD_NUM;
        for (int i = start; i < start + size; ++i) {
#pragma HLS UNROLL
            if (entry[i].valid) {
                sym_o = i;
                return true;
            }
        }
        break;

    case OP_MUL:
    case OP_DIV:
        start = RES_STA_MUL_START_INDEX;
        size = RES_STA_MUL_NUM;
        for (int i = start; i < start + size; ++i) {
#pragma HLS UNROLL
            if (entry[i].valid) {
                sym_o = i;
                return true;
            }
        }
        break;

    default:
        break;
    }

    return false;
}

void Reservation_stations::issue (op_enum op, res_sta_symbol_t rd_index, reg_stat_t r1, reg_stat_t r2) {
    entry[rd_index].valid = false;
    entry[rd_index].op = op;
    entry[rd_index].r1 = r1;
    entry[rd_index].r2 = r2;
}

void Reservation_stations::try_assign_task (res_sta_assign_task_stream_t &to_adder, res_sta_assign_task_stream_t &to_multiplier) {
#pragma HLS ARRAY_PARTITION variable=entry complete dim=1

    // // debug
    // std::cout << "    valid: ";
    // for (int i = 0; i < RES_STA_TOTAL_NUM; ++i)
    //     std::cout << entry[i].valid;
    // std::cout << std::endl;
    // adders_status.print_debug();
    // multipliers_status.print_debug();

    for (int i = 0; i < RES_STA_TOTAL_NUM; ++i) {
#pragma HLS UNROLL
        if (!entry[i].valid && entry[i].r1.stat == REG_STAT_SCALAR && entry[i].r2.stat == REG_STAT_SCALAR) {
            int index;
            switch (entry[i].op) {
            case OP_ADD:
            case OP_ADDI:
            case OP_SUB:
                if (!adders_status.get_busy(index)) {
                    adders_status.set_busy(index);
                    entry[i].assigned_func_unit_index = index;
                    to_adder.write({index, i, entry[i].op, entry[i].r1.value.scalar, entry[i].r2.value.scalar});
#ifndef __SYNTHESIS__
                    std::cout << "    assign task of entry " << i << " to adder " << index << std::endl;
#endif
                }
                break;

            case OP_MUL:
            case OP_DIV:
                if (!multipliers_status.get_busy(index)) {
                    multipliers_status.set_busy(index);
                    entry[i].assigned_func_unit_index = index;
                    to_multiplier.write({index, i, entry[i].op, entry[i].r1.value.scalar, entry[i].r2.value.scalar});
#ifndef __SYNTHESIS__
                    std::cout << "    assign task of entry " << i << " to multiplier " << index << std::endl;
#endif
                }
                break;

            case OP_NUL:
            default:
                break;
            }
        }
    }
}

void Reservation_stations::write_from_CDB (res_sta_symbol_t sym, data_t value) {
    if (RES_STA_ADD_START_INDEX <= sym && sym < RES_STA_ADD_START_INDEX + RES_STA_ADD_NUM) {
        adders_status.unset_busy(entry[sym].assigned_func_unit_index);
    }
    if (RES_STA_MUL_START_INDEX <= sym && sym < RES_STA_MUL_START_INDEX + RES_STA_MUL_NUM) {
        multipliers_status.unset_busy(entry[sym].assigned_func_unit_index);
    }
    entry[sym].valid = true;

    for (int i = 0; i < RES_STA_TOTAL_NUM; ++i) {
#pragma HLS UNROLL
        if (entry[i].r1.stat == REG_STAT_SYMBOL && entry[i].r1.value.symbol == sym) {
            entry[i].r1.stat = REG_STAT_SCALAR;
            entry[i].r1.value.scalar = value;
        }
        if (entry[i].r2.stat == REG_STAT_SYMBOL && entry[i].r2.value.symbol == sym) {
            entry[i].r2.stat = REG_STAT_SCALAR;
            entry[i].r2.value.scalar = value;
        }
    }
}
