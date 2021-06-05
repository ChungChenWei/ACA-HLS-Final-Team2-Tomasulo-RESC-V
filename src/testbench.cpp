#include <string>
#include "CPU.hpp"
#include "common.hpp"
#include "riscv_instr.hpp"

int main () {
    // TODO
    std::string instruction_str = "\
    ADDI x1, x1, 10\
    ADDI x2, x2, 20\
    ADD x1, x1, x2\
    ";
    
    instr_t instruction_memory[INSTR_MEM_SIZE] = {0};

    RISCV::set_instr(instruction_str, instruction_memory);

    // cpu(instruction_memory);

    return 0;
}
