#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <cstdint>

// CPU related
union data_t {
	uint32_t int_data; // TODO
	float float_data; // TODO: use ap_fixed
};
const int REGISTER_NUM = 32;

// instruction memory related
const int INSTR_MEM_SIZE = 256;
typedef uint32_t instr_t;

// register status
typedef int res_sta_symbol_t;
struct reg_stat_t {
	bool stat;
	union {
		data_t scalar;
		res_sta_symbol_t symbol;
	} value;
};
const bool REG_STAT_SYMBOL = 0;
const bool REG_STAT_SCALAR = 1;

// functional unit related
typedef int op_t;
const op_t OP_ADD = 0;
const op_t OP_SUB = 1;
const op_t OP_MUL = 2;
const op_t OP_DIV = 3;
const int FUNC_UNIT_ADD_NUM = 1;
const int FUNC_UNIT_MUL_NUM = 1;

// reservation stations related
const int RES_STA_ADD_NUM = 3;
const int RES_STA_MUL_NUM = 3;
const int RES_STA_ADD_START_INDEX = 0;
const int RES_STA_MUL_START_INDEX = RES_STA_ADD_START_INDEX + RES_STA_ADD_NUM;
const int RES_STA_TOTAL_NUM = RES_STA_ADD_NUM + RES_STA_MUL_NUM;
struct res_sta_entry_t {
	bool valid;
	op_t op;
	reg_stat_t r1;
	reg_stat_t r2;
};

#endif
