#ifndef __REGISTER_FILE_HPP__
#define __REGISTER_FILE_HPP__

class Register_file;

#include "common.hpp"

class Register_file {
private:
	reg_stat_t reg[REGISTER_NUM];

public:
	Register_file ();
	void read (int index, reg_stat_t &reg_o);
	void write_from_issuer (int index, res_sta_symbol_t reg_i);
	void write_from_CDB (res_sta_symbol_t sym, data_t value);
};

#endif
