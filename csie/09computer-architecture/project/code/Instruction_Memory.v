module Instruction_Memory(addr,instr);

input   [31:0]		addr;
output  [31:0]		instr;

reg     [31:0]		memory[0:255];

assign  instr=memory[addr>>2];

endmodule
