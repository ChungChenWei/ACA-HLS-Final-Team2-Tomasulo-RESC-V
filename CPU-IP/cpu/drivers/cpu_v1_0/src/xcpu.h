// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef XCPU_H
#define XCPU_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xcpu_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
    u16 DeviceId;
    u32 Control_BaseAddress;
} XCpu_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XCpu;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XCpu_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XCpu_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XCpu_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XCpu_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
int XCpu_Initialize(XCpu *InstancePtr, u16 DeviceId);
XCpu_Config* XCpu_LookupConfig(u16 DeviceId);
int XCpu_CfgInitialize(XCpu *InstancePtr, XCpu_Config *ConfigPtr);
#else
int XCpu_Initialize(XCpu *InstancePtr, const char* InstanceName);
int XCpu_Release(XCpu *InstancePtr);
#endif

void XCpu_Start(XCpu *InstancePtr);
u32 XCpu_IsDone(XCpu *InstancePtr);
u32 XCpu_IsIdle(XCpu *InstancePtr);
u32 XCpu_IsReady(XCpu *InstancePtr);
void XCpu_EnableAutoRestart(XCpu *InstancePtr);
void XCpu_DisableAutoRestart(XCpu *InstancePtr);

u32 XCpu_Get_instruction_memory_i_BaseAddress(XCpu *InstancePtr);
u32 XCpu_Get_instruction_memory_i_HighAddress(XCpu *InstancePtr);
u32 XCpu_Get_instruction_memory_i_TotalBytes(XCpu *InstancePtr);
u32 XCpu_Get_instruction_memory_i_BitWidth(XCpu *InstancePtr);
u32 XCpu_Get_instruction_memory_i_Depth(XCpu *InstancePtr);
u32 XCpu_Write_instruction_memory_i_Words(XCpu *InstancePtr, int offset, word_type *data, int length);
u32 XCpu_Read_instruction_memory_i_Words(XCpu *InstancePtr, int offset, word_type *data, int length);
u32 XCpu_Write_instruction_memory_i_Bytes(XCpu *InstancePtr, int offset, char *data, int length);
u32 XCpu_Read_instruction_memory_i_Bytes(XCpu *InstancePtr, int offset, char *data, int length);
u32 XCpu_Get_final_register_file_o_BaseAddress(XCpu *InstancePtr);
u32 XCpu_Get_final_register_file_o_HighAddress(XCpu *InstancePtr);
u32 XCpu_Get_final_register_file_o_TotalBytes(XCpu *InstancePtr);
u32 XCpu_Get_final_register_file_o_BitWidth(XCpu *InstancePtr);
u32 XCpu_Get_final_register_file_o_Depth(XCpu *InstancePtr);
u32 XCpu_Write_final_register_file_o_Words(XCpu *InstancePtr, int offset, word_type *data, int length);
u32 XCpu_Read_final_register_file_o_Words(XCpu *InstancePtr, int offset, word_type *data, int length);
u32 XCpu_Write_final_register_file_o_Bytes(XCpu *InstancePtr, int offset, char *data, int length);
u32 XCpu_Read_final_register_file_o_Bytes(XCpu *InstancePtr, int offset, char *data, int length);

void XCpu_InterruptGlobalEnable(XCpu *InstancePtr);
void XCpu_InterruptGlobalDisable(XCpu *InstancePtr);
void XCpu_InterruptEnable(XCpu *InstancePtr, u32 Mask);
void XCpu_InterruptDisable(XCpu *InstancePtr, u32 Mask);
void XCpu_InterruptClear(XCpu *InstancePtr, u32 Mask);
u32 XCpu_InterruptGetEnabled(XCpu *InstancePtr);
u32 XCpu_InterruptGetStatus(XCpu *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
