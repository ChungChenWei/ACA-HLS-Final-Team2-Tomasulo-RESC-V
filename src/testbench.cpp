#include "CPU.hpp"
#include "common.hpp"

int main () {
    // TODO
    instr_t instruction_memory[INSTR_MEM_SIZE] = {0};

    cpu(instruction_memory);

    return 0;
}
