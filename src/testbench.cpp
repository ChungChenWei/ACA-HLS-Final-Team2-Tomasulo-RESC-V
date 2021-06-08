#include <string>
#include "CPU.hpp"
#include "common.hpp"
#include "riscv_instr.hpp"

int main () {
    // TODO
    std::string instruction_str = "\
    ADDI x1, x1, 10\
    ADDI x2, x2, 20\
    MUL x1, x1, x2\
    MUL x2, x2, x2\
    ADDI x3, x3, 10\
    ADDI x4, x4, 20\
    ADDI x5, x5, 30\
    ADDI x6, x6, 40\
    ADDI x7, x7, 50\
    ADDI x8, x8, 60\
    ADDI x9, x9, 70\
    ADDI x10, x10, 80\
    ADDI x11, x11, 90\
    ADDI x12, x12, 100\
    ADDI x13, x13, 110\
    ";

    instr_t instruction_memory[INSTR_MEM_SIZE] = {0};
    data_t final_register_file[REGISTER_NUM];

    RISCV::set_instr(instruction_str, instruction_memory);

    cpu(instruction_memory, final_register_file);

    std::cout << " # final register status" << std::endl;
    for (int i = 0; i < REGISTER_NUM; i += 4) {
        std::cout << "    x" << i << " = " << final_register_file[i].int_data << " , "
                  << "x" << i+1 << " = " << final_register_file[i+1].int_data << " , "
                  << "x" << i+2 << " = " << final_register_file[i+2].int_data << " , "
                  << "x" << i+3 << " = " << final_register_file[i+3].int_data << std::endl;
    }

    return 0;
}
