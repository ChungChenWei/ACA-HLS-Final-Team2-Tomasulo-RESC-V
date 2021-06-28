#ifndef __ISSUER_HPP__
#define __ISSUER_HPP__

#include "common.hpp"
#include "register_file.hpp"
#include "reservation_stations.hpp"

namespace Issuer {

void issue (Register_file &rf, Reservation_stations &rs, instr_t instr_i, bool &success_o);

} // namespace Issuer

#endif
