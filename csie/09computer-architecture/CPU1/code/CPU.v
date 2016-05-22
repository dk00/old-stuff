module CPU
(
    clk_i, 
    rst_i,
    start_i
);

// Ports
input			clk_i;
input           rst_i;
input           start_i;
wire	[31:0]	Instr,Imm,PC_i,PC_o,ALU_i1,ALURes,RegDat_i,RegDat_o0,RegDat_o1,
				DataMem_o,BranchOffset,BranchAddress,BranchAddress1,PC_Next;
wire	[27:0]	JumpAddress;
wire	[4:0]	RDaddr;
wire	[2:0]	ALUCtrl;
wire	[1:0]	ALUOp;
wire			Jump,RegDst,Branch,MemRead,MemtoReg,MemWrite,ALUSrc,RegWrite;

Control Control(
    .Op_i       (Instr[31:26]),
	.Jump_o		(Jump),
    .RegDst_o   (RegDst),
	.Branch_o	(Branch),
	.MemRead_o	(MemRead),
	.MemtoReg_o	(MemtoReg),
	.ALUOp_o    (ALUOp),
	.MemWrite_o	(MemWrite),
	.ALUSrc_o   (ALUSrc),
    .RegWrite_o (RegWrite)
);

Adder Add_PC(
    .data1_in   (PC_o),
    .data2_in   (4),
    .data_o     (PC_Next)
);

PC PC(
    .clk_i      (clk_i),
    .rst_i      (rst_i),
    .start_i    (start_i),
    .pc_i       (PC_i),
    .pc_o       (PC_o)
);

Instruction_Memory Instruction_Memory(
    .addr_i     (PC_o), 
    .instr_o    (Instr)
);

Data_Memory Data_Memory(
    .clk_i      (clk_i),
    .addr_i     (ALURes),
    .data_i     (RegDat_o1),
    .MemRead_i  (MemRead),
    .MemWrite_i (MemWrite),
    .data_o     (DataMem_o)
);

Registers Registers(
    .clk_i      (clk_i),
    .RSaddr_i   (Instr[25:21]),
    .RTaddr_i   (Instr[20:16]),
    .RDaddr_i   (RDaddr), 
    .RDdata_i   (RegDat_i),
    .RegWrite_i (RegWrite),
    .RSdata_o   (RegDat_o0), 
    .RTdata_o   (RegDat_o1) 
);

MUX5 MUX_RegDst(
    .data1_i    (Instr[20:16]),
    .data2_i    (Instr[15:11]),
    .select_i   (RegDst),
    .data_o     (RDaddr)
);


MUX32 MUX_ALUSrc(
    .data1_i    (RegDat_o1),
    .data2_i    (Imm),
    .select_i   (ALUSrc),
    .data_o     (ALU_i1)
);

Signed_Extend Signed_Extend(
    .data_i     (Instr[15:0]),
    .data_o     (Imm)
);
  
ALU ALU(
    .data1_i    (RegDat_o0),
    .data2_i    (ALU_i1),
    .ALUCtrl_i  (ALUCtrl),
    .data_o     (ALURes),
    .Zero_o     (Zero)
);

ALU_Control ALU_Control(
    .funct_i    (Instr[5:0]),
    .ALUOp_i    (ALUOp),
    .ALUCtrl_o  (ALUCtrl)
);

MUX32 MUX_RegSrc(
    .data1_i    (ALURes),
    .data2_i    (DataMem_o),
    .select_i   (MemtoReg),
    .data_o     (RegDat_i)
);

ShiftLeftTwo26 Shift_JmpAddr(
	.data_i(Instr[25:0]),
	.data_o(JumpAddress)
);

ShiftLeftTwo32 Shift_BranchAddr(
	.data_i(Imm),
	.data_o(BranchOffset)
);

Adder Add_BranchAddr(
	.data1_in(PC_Next),
	.data2_in(BranchOffset),
	.data_o(BranchAddress)
);

MUX32 MUX_Branch(
	.data1_i(PC_Next),
	.data2_i(BranchAddress),
	.select_i(Branch&Zero),
	.data_o(BranchAddress1)
);

MUX32 MUX_Jump(
	.data1_i(BranchAddress1),
	.data2_i({PC_Next[31:28],JumpAddress}),
	.select_i(Jump),
	.data_o(PC_i)
);

endmodule
