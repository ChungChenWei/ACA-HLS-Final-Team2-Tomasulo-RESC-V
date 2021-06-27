#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <cstdint>
#include "hls_stream.h"

// CPU related
const int MAX_CYCLE_NUM = 40;
union data_t {
    uint32_t int_data; // TODO
    float float_data; // TODO: use ap_fixed
};
const int REGISTER_NUM = 32;

// instruction memory related
const int INSTR_MEM_SIZE = 16; // TODO: tmp
typedef uint32_t instr_t;
typedef uint32_t RISCV_code_t;

// register status
typedef int res_sta_symbol_t; // value range: [0, RES_STA_TOTAL_NUM)
enum reg_stat_enum {
    REG_STAT_SYMBOL,
    REG_STAT_SCALAR,
};
struct reg_stat_t {
    reg_stat_enum stat;
    union {
        data_t scalar;
        res_sta_symbol_t symbol;
    } value;
};
const char REG_PREFIX = 'x';

// functional unit related
enum op_enum {
    OP_NUL,
    OP_ADD,
    OP_ADDI,
    OP_SUB,
    OP_MUL,
    OP_DIV,
};
const int FUNC_UNIT_ADD_NUM = 1;
const int FUNC_UNIT_MUL_NUM = 1;
const int FUNC_UNIT_ADD_DURATION = 1;
const int FUNC_UNIT_MUL_DURATION = 3;

// reservation stations related
const int RES_STA_ADD_NUM = 3;
const int RES_STA_MUL_NUM = 3;
const int RES_STA_ADD_START_INDEX = 0;
const int RES_STA_MUL_START_INDEX = RES_STA_ADD_START_INDEX + RES_STA_ADD_NUM;
const int RES_STA_TOTAL_NUM = RES_STA_ADD_NUM + RES_STA_MUL_NUM;
struct res_sta_entry_t {
    bool valid;
    int assigned_func_unit_index;
    op_enum op;
    reg_stat_t r1;
    reg_stat_t r2;
};
struct __res_sta_assign_task_interface_t {
    int func_unit_index;
    res_sta_symbol_t src;
    op_enum op;
    data_t r1;
    data_t r2;
};
typedef hls::stream<__res_sta_assign_task_interface_t, 1> res_sta_assign_task_stream_t;
struct __func_unit_finish_task_interface_t {
    res_sta_symbol_t src;
    data_t value;
};
typedef hls::stream<__func_unit_finish_task_interface_t, 1> func_unit_finish_task_stream_t;


#endif
