// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
// control
// 0x00 : Control signals
//        bit 0  - ap_start (Read/Write/COH)
//        bit 1  - ap_done (Read/COR)
//        bit 2  - ap_idle (Read)
//        bit 3  - ap_ready (Read)
//        bit 7  - auto_restart (Read/Write)
//        others - reserved
// 0x04 : Global Interrupt Enable Register
//        bit 0  - Global Interrupt Enable (Read/Write)
//        others - reserved
// 0x08 : IP Interrupt Enable Register (Read/Write)
//        bit 0  - enable ap_done interrupt (Read/Write)
//        bit 1  - enable ap_ready interrupt (Read/Write)
//        others - reserved
// 0x0c : IP Interrupt Status Register (Read/TOW)
//        bit 0  - ap_done (COR/TOW)
//        bit 1  - ap_ready (COR/TOW)
//        others - reserved
// 0x40 ~
// 0x7f : Memory 'instruction_memory_i' (16 * 32b)
//        Word n : bit [31:0] - instruction_memory_i[n]
// 0x80 ~
// 0xff : Memory 'final_register_file_o' (32 * 32b)
//        Word n : bit [31:0] - final_register_file_o[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XCPU_CONTROL_ADDR_AP_CTRL                    0x00
#define XCPU_CONTROL_ADDR_GIE                        0x04
#define XCPU_CONTROL_ADDR_IER                        0x08
#define XCPU_CONTROL_ADDR_ISR                        0x0c
#define XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE  0x40
#define XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_HIGH  0x7f
#define XCPU_CONTROL_WIDTH_INSTRUCTION_MEMORY_I      32
#define XCPU_CONTROL_DEPTH_INSTRUCTION_MEMORY_I      16
#define XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE 0x80
#define XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_HIGH 0xff
#define XCPU_CONTROL_WIDTH_FINAL_REGISTER_FILE_O     32
#define XCPU_CONTROL_DEPTH_FINAL_REGISTER_FILE_O     32

