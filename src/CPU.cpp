#include <iostream>
#include "common.hpp"
#include "CDB.hpp"
#include "register_file.hpp"
#include "functional_unit.hpp"
#include "reservation_stations.hpp"
#include "issuer.hpp"

void cpu (instr_t instruction_memory[INSTR_MEM_SIZE]) {
	CDB cdb;
	Register_file rf;
	Adders adders {&cdb};
	Multipliers multipliers {&cdb};
	Reservation_stations rs {&adders, &multipliers};
	Issuer issuer {&rf, &rs};

	cdb.register_listeners(&rf, &rs);

	int cycle = 0;
	unsigned PC = 0;

	while (PC < INSTR_MEM_SIZE) {
		std::cout << " # cycle = " << cycle << std::endl;

		bool success;
		issuer.issue(instruction_memory[PC], success);
		rs.try_assign_task();

		std::cout << "success = " << success << std::endl;

		if (success) PC += 1;
		cycle += 1;
	}
}
