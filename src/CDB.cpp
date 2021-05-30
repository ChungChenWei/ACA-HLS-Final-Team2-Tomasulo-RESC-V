#include "common.hpp"
#include "CDB.hpp"

CDB::CDB () {}

void CDB::register_listeners (Register_file *rf_, Reservation_stations *rs_) {
    rf = rf_;
    rs = rs_;
}

void CDB::broadcast (res_sta_symbol_t sym, data_t value) {
    rf->write_from_CDB(sym, value);
    rs->write_from_CDB(sym, value);
}
