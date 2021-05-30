#ifndef __CDB_HPP__
#define __CDB_HPP__

class CDB;

#include "common.hpp"
#include "register_file.hpp"
#include "reservation_stations.hpp"


class CDB {
private:
	Register_file *rf;
	Reservation_stations *rs;

public:
	CDB ();
	void register_listeners (Register_file *rf_, Reservation_stations *rs_);
	void broadcast (res_sta_symbol_t sym, data_t value_i);
};

#endif
