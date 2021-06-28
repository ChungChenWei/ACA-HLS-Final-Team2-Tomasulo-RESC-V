
# coding: utf-8

# # ACA HLS Team2 Final Project
# ## RISC-V Tomasulo CPU

# In[1]:



from __future__ import print_function

import sys
import numpy as np
from time import time

from pynq import Overlay
from pynq import allocate

from inst_creator import instr_gen


# ```
# // ==============================================================
# // Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
# // Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
# // ==============================================================
# // control
# // 0x00 : Control signals
# //        bit 0  - ap_start (Read/Write/COH)
# //        bit 1  - ap_done (Read/COR)
# //        bit 2  - ap_idle (Read)
# //        bit 3  - ap_ready (Read)
# //        bit 7  - auto_restart (Read/Write)
# //        others - reserved
# // 0x04 : Global Interrupt Enable Register
# //        bit 0  - Global Interrupt Enable (Read/Write)
# //        others - reserved
# // 0x08 : IP Interrupt Enable Register (Read/Write)
# //        bit 0  - enable ap_done interrupt (Read/Write)
# //        bit 1  - enable ap_ready interrupt (Read/Write)
# //        others - reserved
# // 0x0c : IP Interrupt Status Register (Read/TOW)
# //        bit 0  - ap_done (COR/TOW)
# //        bit 1  - ap_ready (COR/TOW)
# //        others - reserved
# // 0x40 ~
# // 0x7f : Memory 'instruction_memory_i' (16 * 32b)
# //        Word n : bit [31:0] - instruction_memory_i[n]
# // 0x80 ~
# // 0xff : Memory 'final_register_file_o' (32 * 32b)
# //        Word n : bit [31:0] - final_register_file_o[n]
# // (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)
# ```

# In[2]:


# path
ROOT_PATH = '/home/xilinx/final/bit'
BIT_PATH = ROOT_PATH + '/cpu.bit'
# const
INSTR_MAX = 16 # 16 * 32b
REG_MAX = 32   # 32 * 32b
# mem
AP_CONTR = 0x00
AP_START = 0x1
AP_DONE  = 0x2
AP_IDLE  = 0x4
AP_READY = 0x8

INSTR_I  = 0x40 # 0x40 ~ 0x7f (16 * 32b)
REG_O    = 0x80 # 0x80 ~ 0xff (32 * 32b)


# In[3]:


ol = Overlay(BIT_PATH)
cpuIP = ol.cpu_0


# In[25]:


inst = """
ADDI x1, x1, 10
ADDI x2, x2, 20
MUL x1, x1, x2
MUL x2, x2, x2
ADDI x3, x2, 10
MUL x4, x3, x1
ADD x5, x4, x4
ADDI x6, x6, 5
ADDI x7, x7, 6
MUL x8, x7, x6
MUL x9, x7, x6
MUL x10, x7, x6
"""
instr_list = np.asarray(instr_gen(inst), dtype=np.int32)

if (len(instr_list) > INSTR_MAX) :
    raise IndexError("too many instructions")

instrBuffer = np.zeros(shape=(INSTR_MAX,), dtype=np.int32)
regBuffer = np.zeros(shape=(REG_MAX,), dtype=np.int32)

# Setup Instr
for i in range(len(instr_list)) :
    instrBuffer[i] = int(instr_list[i])


# In[27]:


timeKernelStart = time()
# write instruction
for i in range(len(instrBuffer)) :
    cpuIP.write(INSTR_I + i * 4, int(instrBuffer[i]))

# start signal
cpuIP.write(AP_CONTR, AP_START)
# until idle
while (cpuIP.read(AP_CONTR) & AP_IDLE) == 0x0:
    continue

timeKernelEnd = time()
print(f"Kernel execution time: {str(timeKernelEnd - timeKernelStart)} s")


# In[28]:


for i in range(len(regBuffer)) :
    if (i%5 == 0 and i != 0) :
        regBuffer[i] = cpuIP.read(REG_O + i * 4)
        print(f"\nx{i:<2d} = {regBuffer[i]:5d}", end='\t')
    else :
        regBuffer[i] = cpuIP.read(REG_O + i * 4)
        print(f"x{i:<2d} = {regBuffer[i]:5d}", end='\t')

