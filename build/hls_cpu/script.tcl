############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
############################################################
open_project tomasulo-riscv-cpu
set_top cpu
add_files ../../src/kernel/riscv_instr.hpp
add_files ../../src/kernel/riscv_instr.cpp
add_files ../../src/kernel/reservation_stations.hpp
add_files ../../src/kernel/reservation_stations.cpp
add_files ../../src/kernel/register_file.hpp
add_files ../../src/kernel/register_file.cpp
add_files ../../src/kernel/issuer.hpp
add_files ../../src/kernel/issuer.cpp
add_files ../../src/kernel/functional_unit.hpp
add_files ../../src/kernel/functional_unit.cpp
add_files ../../src/kernel/common.hpp
add_files ../../src/kernel/CPU.hpp
add_files ../../src/kernel/CPU.cpp
add_files -tb ../../src/kernel/testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 15 -name default
config_export -format ip_catalog -output ../cpu.zip -rtl verilog
source "./directives.tcl"
csim_design
csynth_design
cosim_design -trace_level all
export_design -rtl verilog -format ip_catalog -output ../cpu.zip
