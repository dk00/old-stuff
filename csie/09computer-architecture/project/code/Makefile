FILES=CPU.v Adder.v PC.v Instruction_Memory.v Pipeline_Registers.v Registers.v \
Control.v ALU_Control.v ALU.v Data_Memory.v MUX32.v MUX5.v Signed_Extend.v \
ShiftLeftTwo32.v ShiftLeftTwo26.v Comparator.v Forwarding_unit.v TriMUX.v \
Hazard_Detection_unit.v dcache_data_sram.v dcache_tag_sram.v dcache_top.v

all: $(FILES) TestBench.v
	iverilog $(FILES) TestBench.v -o test
