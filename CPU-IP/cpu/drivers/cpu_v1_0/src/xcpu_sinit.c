// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2020.2 (64-bit)
// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#include "xparameters.h"
#include "xcpu.h"

extern XCpu_Config XCpu_ConfigTable[];

XCpu_Config *XCpu_LookupConfig(u16 DeviceId) {
	XCpu_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XCPU_NUM_INSTANCES; Index++) {
		if (XCpu_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XCpu_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XCpu_Initialize(XCpu *InstancePtr, u16 DeviceId) {
	XCpu_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XCpu_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XCpu_CfgInitialize(InstancePtr, ConfigPtr);
}

#endif

