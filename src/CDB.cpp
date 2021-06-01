#include "CDB.hpp"

void CDB_broadcast (Register_file &rf, Reservation_stations &rs, res_sta_symbol_t sym, data_t value) {
    rf.write_from_CDB(sym, value);
    rs.write_from_CDB(sym, value);
}
