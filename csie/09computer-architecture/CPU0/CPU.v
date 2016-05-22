module CPU(clk_i,rst_i,start_i);

// Ports
input	clk_i;
input	rst_i;
input	start_i;

wire	[6:0]	Op;
wire		RegDst;
wire	[1:0]	ALUOp;
wire		ALUSrc;
wire		RegWrite;
wire	[31:0]	PCOut;
wire	[31:0]	PCIn;
wire	[31:0]	Instr;
wire	[31:0]	Imm;
wire	[31:0]	RSdata;
wire	[31:0]	RTdata;
wire	[4:0]	RDAddr;
wire	[31:0]	ALUIn1;
wire	[31:0]	ALURes;
wire	[2:0]	ALUCtrl;
wire	[31:0]	Zero;

Control Control(Instr[31:26],RegDst,ALUOp,ALUSrc,RegWrite);

Adder Add_PC(PCOut,4,PCIn);

PC PC(clk_i,rst_i,start_i,PCIn,PCOut);

Instruction_Memory Instruction_Memory(PCOut,Instr);

Registers Registers(
    clk_i,
    Instr[25:21],
    Instr[20:16],
    RDAddr,ALURes,RegWrite,RSdata,RTdata
);

MUX5 MUX_RegDst(Instr[20:16],Instr[15:11],RegDst,RDAddr);

MUX32 MUX_ALUSrc(RTdata,Imm,ALUSrc,ALUIn1);

Signed_Extend Signed_Extend(Instr[15:0],Imm);
  
ALU ALU(RSdata,ALUIn1,ALUCtrl,ALURes,Zero);

ALU_Control ALU_Control(Instr[5:0],ALUOp,ALUCtrl);

endmodule

