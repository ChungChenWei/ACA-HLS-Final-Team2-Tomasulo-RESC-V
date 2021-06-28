# opcode
OP_R_type = 0b0110011; # 0x0c 0x3
OP_I_type = 0b0010011; # 0x04 0x3
OP_S_tpye = 0b0000011; # 0x00 0x3
# funct3
F3_ADD  = 0b000; # 0x0
F3_ADDI = 0b000; # 0x0
F3_SUB  = 0b000; # 0x0
F3_MUL  = 0b000; # 0x0
F3_DIV  = 0b100; # 0x4
F3 = {
    "ADD" : F3_ADD,
    "SUB" : F3_SUB,
    "MUL" : F3_MUL,
    "DIV" : F3_DIV,
    "ADDI" : F3_ADDI
}

# funct7
F7_ADD = 0b0000000; # 0x00
F7_SUB = 0b0100000; # 0x20
F7_MUL = 0b0000001; # 0x01
F7_DIV = 0b0000001; # 0x01
F7 = {
    "ADD" : F7_ADD,
    "SUB" : F7_SUB,
    "MUL" : F7_MUL,
    "DIV" : F7_DIV
}
# control
output_format = "c++"


def reg(regname) :
    return int(regname.replace('x', ''))
def instr_gen(instr_str) :
    instr_list = []
    for k, line in enumerate(instr_str.strip().split('\n')) :
        op  = line.strip().partition(' ')[0]
        arg = line.strip().partition(' ')[2].split(', ')
        
        if (op == "ADD" or op == "SUB" or op == "MUL" or op == "DIV") :
            instr_type = "R"
        elif (op == "ADDI") :
            imm = reg(arg[2])
            instr_type = "I"
        else :
            raise KeyError(f"operation {op} not defined")

        if (instr_type == "R") :
            inst = f"{F7[op]:07b}_{reg(arg[2]):05b}_{reg(arg[1]):05b}_{F3[op]:03b}_{reg(arg[0]):05b}_{OP_R_type:07b}"
        elif (instr_type == "I") :
            inst = f"{imm:012b}_{reg(arg[1]):05b}_{F3[op]:03b}_{reg(arg[0]):05b}_{OP_I_type:07b}"

        instr_list.append(int(f"0b{inst.replace('_','')}", 2))

    return instr_list

if __name__ == '__main__':
    inst = """
    ADDI x0, x0, 0
    ADDI x1, x1, 10
    ADDI x2, x2, 20
    ADD x1, x1, x2
    """
    instr_list = instr_gen(inst)
    print(instr_list)