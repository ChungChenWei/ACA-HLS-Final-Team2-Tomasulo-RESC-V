############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2021 Xilinx, Inc. All Rights Reserved.
############################################################
open_project final-project-hls
set_top cpu
add_files src/riscv_instr.hpp
add_files src/riscv_instr.cpp
add_files src/reservation_stations.hpp
add_files src/reservation_stations.cpp
add_files src/register_file.hpp
add_files src/register_file.cpp
add_files src/issuer.hpp
add_files src/issuer.cpp
add_files src/functional_unit.hpp
add_files src/functional_unit.cpp
add_files src/common.hpp
add_files src/CPU.hpp
add_files src/CPU.cpp
add_files src/CDB.hpp
add_files src/CDB.cpp
add_files -tb src/testbench.cpp -cflags "-Wno-unknown-pragmas" -csimflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 5 -name default
source "./final-project-hls/solution1/directives.tcl"
csim_design
csynth_design
cosim_design -trace_level port
export_design -format ip_catalog
