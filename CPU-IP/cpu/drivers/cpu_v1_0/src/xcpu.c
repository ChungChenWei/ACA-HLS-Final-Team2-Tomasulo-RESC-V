// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
/***************************** Include Files *********************************/
#include "xcpu.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XCpu_CfgInitialize(XCpu *InstancePtr, XCpu_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XCpu_Start(XCpu *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_AP_CTRL) & 0x80;
    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XCpu_IsDone(XCpu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XCpu_IsIdle(XCpu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XCpu_IsReady(XCpu *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XCpu_EnableAutoRestart(XCpu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XCpu_DisableAutoRestart(XCpu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XCpu_Get_instruction_memory_i_BaseAddress(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE);
}

u32 XCpu_Get_instruction_memory_i_HighAddress(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_HIGH);
}

u32 XCpu_Get_instruction_memory_i_TotalBytes(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_HIGH - XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + 1);
}

u32 XCpu_Get_instruction_memory_i_BitWidth(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCPU_CONTROL_WIDTH_INSTRUCTION_MEMORY_I;
}

u32 XCpu_Get_instruction_memory_i_Depth(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCPU_CONTROL_DEPTH_INSTRUCTION_MEMORY_I;
}

u32 XCpu_Write_instruction_memory_i_Words(XCpu *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_HIGH - XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XCpu_Read_instruction_memory_i_Words(XCpu *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_HIGH - XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + (offset + i)*4);
    }
    return length;
}

u32 XCpu_Write_instruction_memory_i_Bytes(XCpu *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_HIGH - XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XCpu_Read_instruction_memory_i_Bytes(XCpu *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_HIGH - XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_INSTRUCTION_MEMORY_I_BASE + offset + i);
    }
    return length;
}

u32 XCpu_Get_final_register_file_o_BaseAddress(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE);
}

u32 XCpu_Get_final_register_file_o_HighAddress(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_HIGH);
}

u32 XCpu_Get_final_register_file_o_TotalBytes(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_HIGH - XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + 1);
}

u32 XCpu_Get_final_register_file_o_BitWidth(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCPU_CONTROL_WIDTH_FINAL_REGISTER_FILE_O;
}

u32 XCpu_Get_final_register_file_o_Depth(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCPU_CONTROL_DEPTH_FINAL_REGISTER_FILE_O;
}

u32 XCpu_Write_final_register_file_o_Words(XCpu *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_HIGH - XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XCpu_Read_final_register_file_o_Words(XCpu *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_HIGH - XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + (offset + i)*4);
    }
    return length;
}

u32 XCpu_Write_final_register_file_o_Bytes(XCpu *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_HIGH - XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XCpu_Read_final_register_file_o_Bytes(XCpu *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_HIGH - XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XCPU_CONTROL_ADDR_FINAL_REGISTER_FILE_O_BASE + offset + i);
    }
    return length;
}

void XCpu_InterruptGlobalEnable(XCpu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_GIE, 1);
}

void XCpu_InterruptGlobalDisable(XCpu *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_GIE, 0);
}

void XCpu_InterruptEnable(XCpu *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_IER);
    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_IER, Register | Mask);
}

void XCpu_InterruptDisable(XCpu *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_IER);
    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_IER, Register & (~Mask));
}

void XCpu_InterruptClear(XCpu *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XCpu_WriteReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_ISR, Mask);
}

u32 XCpu_InterruptGetEnabled(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_IER);
}

u32 XCpu_InterruptGetStatus(XCpu *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XCpu_ReadReg(InstancePtr->Control_BaseAddress, XCPU_CONTROL_ADDR_ISR);
}

