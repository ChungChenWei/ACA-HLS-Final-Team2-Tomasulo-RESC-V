## Advanced CA 2021 HLS Final Project

### RISC-V CPU with Tomasulo Algorithm

#### Introduction

We are using `Vitits HLS` to implement a RISC-V CPU with Tomasulo Algorithm and generate a CPU IP then make a simple design to run on pynq

#### Folder structure
```
./
├── README.md
├── build/
    ├── hls_cpu/        # scripts for building CPU IP
    ├── vvd_cpu/        # scripts for building bitstream
├── docs/               # references and vivado project guide
├── src/
    ├── host/           # host code for pynq
    ├── kernel/         # kernel code for HLS
├── impl_result/ 
    ├── IP/             # cpu IP
    ├── opt1_bitstream/ # bitstream and hwh for pynq to run
└── LICENSE
```


#### Build Setup

**CPU IP**

1. under `build/vts_cpu` folder, run `Vitis HLS 2020.2 Command Prompt` then run `vitis_hls script.tcl`
2. the cpu ip ( `cpu.zip` ) will be generate under `build` 

**Bitstream**

- follow [vivado build](https://github.com/ChungChenWei/ACA-HLS-Final-Team2-Tomasulo-RISC-V/blob/master/docs/vivado build.md) guide

