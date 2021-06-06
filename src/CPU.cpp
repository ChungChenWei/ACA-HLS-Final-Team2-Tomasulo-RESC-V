#include <iostream>
#include "common.hpp"
#include "CDB.hpp"
#include "register_file.hpp"
#include "functional_unit.hpp"
#include "reservation_stations.hpp"
#include "issuer.hpp"

void cpu (instr_t instruction_memory[INSTR_MEM_SIZE]) {
	Register_file rf;
	Adders adders;
	Multipliers multipliers;
	Reservation_stations rs;

	int cycle = 0;
	unsigned PC = 0;

	while (PC < INSTR_MEM_SIZE) {
#ifndef __SYNTHESIS__
		std::cout << " # cycle = " << cycle << std::endl;
#endif

		bool success = true;
		Issuer::issue(rf, rs, instruction_memory[PC], success);
		rs.try_assign_task(adders, multipliers, rf);

#ifndef __SYNTHESIS__
		std::cout << "    success = " << success << std::endl;
#endif
		// Temporary for debug
		// if (success) PC += 1;
		PC += 1;
		cycle += 1;
	}
}
