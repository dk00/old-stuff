FILES=Adder.v ALU_Control.v ALU.v Control.v CPU.v Instruction_Memory.v \
      MUX32.v MUX5.v PC.v Registers.v Signed_Extend.v
TEST=ALU.v

all: testbench

testbench: $(FILES) testbench.v
	iverilog $(FILES) testbench.v -o test

unit: $(TEST)
	iverilog $(TEST) test.v -o test
