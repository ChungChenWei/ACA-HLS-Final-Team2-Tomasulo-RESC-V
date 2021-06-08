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

void Reservation_stations::try_assign_task (Adders &adders, Multipliers &multipliers, res_sta_assign_task_stream_t &to_adder, func_unit_finish_task_stream_t &from_adder, res_sta_assign_task_stream_t &to_multiplier, func_unit_finish_task_stream_t &from_multiplier) {
#pragma HLS ARRAY_PARTITION variable=entry complete dim=1

	if (!from_adder.empty()) {
        res_sta_symbol_t i = from_adder.read();
        entry[i].valid = true;
	}
	if (!from_multiplier.empty()) {
        res_sta_symbol_t i = from_multiplier.read();
        entry[i].valid = true;
	}

    for (int i = 0; i < RES_STA_TOTAL_NUM; ++i) {
#pragma HLS UNROLL
        if (!entry[i].valid && entry[i].r1.stat == REG_STAT_SCALAR && entry[i].r2.stat == REG_STAT_SCALAR) {
            int index;
            switch (entry[i].op) {
            case OP_ADD:
            case OP_ADDI:
            case OP_SUB:
                if (!adders.get_busy(index)) {
                    to_adder.write({i, entry[i].op, entry[i].r1.value.scalar, entry[i].r2.value.scalar});
#ifndef __SYNTHESIS__
                    std::cout << "    assign task of entry " << i << " to adder" << std::endl;
#endif
                }
                break;

            case OP_MUL:
            case OP_DIV:
                if (!multipliers.get_busy(index)) {
                    to_multiplier.write({i, entry[i].op, entry[i].r1.value.scalar, entry[i].r2.value.scalar});
#ifndef __SYNTHESIS__
                    std::cout << "    assign task of entry " << i << " to multiplier" << std::endl;
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
