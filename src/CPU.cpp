#include <iostream>
#include "common.hpp"
#include "CDB.hpp"
#include "register_file.hpp"
#include "functional_unit.hpp"
#include "reservation_stations.hpp"
#include "issuer.hpp"

void front_end (instr_t instruction_i, bool &success_o, Register_file &rf, func_unit_finish_task_stream_t &from_adder, func_unit_finish_task_stream_t &from_multiplier, res_sta_assign_task_stream_t &to_adder, res_sta_assign_task_stream_t &to_multiplier) {
    static Reservation_stations rs;

    if (!from_adder.empty()) {
        auto tmp = from_adder.read();
        rs.write_from_CDB(tmp.src, tmp.value);
        rf.write_from_CDB(tmp.src, tmp.value);
        std::cout << "    adder finish task, entry = " << tmp.src << ", data = " << tmp.value.int_data << std::endl;
	}
	if (!from_multiplier.empty()) {
        auto tmp = from_multiplier.read();
        rs.write_from_CDB(tmp.src, tmp.value);
        rf.write_from_CDB(tmp.src, tmp.value);
        std::cout << "    multiplier finish task, entry = " << tmp.src << ", data = " << tmp.value.int_data << std::endl;
	}

    Issuer::issue(rf, rs, instruction_i, success_o);
    rs.try_assign_task(to_adder, to_multiplier);
}

void every_cycle (instr_t instruction_i, bool &success_o, Register_file &rf) {
    static Adders adders;
    static Multipliers multipliers;
    static res_sta_assign_task_stream_t front_end_to_adder("stream_to_adder"), front_end_to_multiplier("stream_to_multiplier");
    static func_unit_finish_task_stream_t adder_to_front_end("stream_from_adder"), multiplier_to_frontend("stream_from_multiplier");

    // dataflow optimization
    front_end(instruction_i, success_o, rf, adder_to_front_end, multiplier_to_frontend, front_end_to_adder, front_end_to_multiplier);
    adders.every_cycle(front_end_to_adder, adder_to_front_end);
    multipliers.every_cycle(front_end_to_multiplier, multiplier_to_frontend);
}

void cpu (instr_t instruction_memory_i[INSTR_MEM_SIZE], data_t final_register_file_o[REGISTER_NUM]) {
#pragma HLS INTERFACE s_axilite port=return
	Register_file rf;

    int cycle = 0;
    unsigned PC = 0;

    while (PC < INSTR_MEM_SIZE && cycle < MAX_CYCLE_NUM) {
#ifndef __SYNTHESIS__
        std::cout << " # cycle = " << cycle << " , PC = " << PC << std::endl;
        std::cout << "    intruction :  " << instruction_memory_i[PC] << std::endl;
#endif

        bool success = true;
        every_cycle(instruction_memory_i[PC], success, rf);

        cycle += 1;
        if (success) {
#ifndef __SYNTHESIS__
        std::cout << "    success = " << success << std::endl;
#endif
            PC += 1;
        }
    }

    rf.get_final_status(final_register_file_o);
}
