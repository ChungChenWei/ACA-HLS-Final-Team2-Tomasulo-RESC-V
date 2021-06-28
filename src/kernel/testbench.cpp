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
    ADDI x3, x2, 10\
    MUL x4, x3, x1\
    ADD x5, x4, x4\
    ADDI x6, x6, 5\
    ADDI x7, x7, 6\
    MUL x8, x7, x6\
    MUL x9, x7, x6\
    MUL x10, x7, x6\
    ADDI x0, x0, 3\
    ";
    data_t correct_final_register_file[REGISTER_NUM] = {0, 200, 400, 410, 82000, 164000, 5, 6, 30, 30, 30, 0};

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

    for (int i = 0; i < REGISTER_NUM; ++i) {
        if (final_register_file[i].int_data != correct_final_register_file[i].int_data)
            return 1;
    }

    return 0;
}
