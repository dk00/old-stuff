`default_nettype none
module CPU(clk,rst,start,
ReadData,MemAck,WriteData,MemAddr,MemEnable,MemWrite);

input			clk,rst,start,MemAck;
input	[255:0]	ReadData;
output			MemEnable,MemWrite;
output	[255:0]	WriteData;
output	[31:0]	MemAddr;
wire	[31:0]	InstrAddr,NextPC,NextPC_IF,Instr;

Adder Add_PC(
    .data0	(InstrAddr),
    .data1	(4),
    .res	(NextPC_IF)
);

wire	MemStall;

PC PC(
    .clk	(clk),
    .rst	(rst),
    .start	(start),
    .pc_i   (NextPC),
    .pc_o   (InstrAddr),
	.Stall	(Stall|MemStall),
	.Enable	(1)
);

wire	[31:0]	BranchNextPC;
wire	[27:0]	Jaddr;

MUX32 mux1(NextPC_IF,Baddr,Branch&eq,BranchNextPC);

ShiftLeftTwo26 ShlJ(Instr_ID[25:0],Jaddr);

MUX32 mux2(BranchNextPC,{NextPC_IF[31:28],Jaddr},Jump,NextPC);//acceptable

Instruction_Memory InstrMem(
	.addr	(InstrAddr),
	.instr	(Instr)
);

wire 			Stall, MUXSel;
Hazard_Detection_unit HD(Instr_ID, Control_EX[8:8], Instr_EX[20:16], Stall, MUXSel);

wire	[31:0]	Instr_ID,NextPC_ID;

Pipeline_Registers IF_ID(
	.clk		(clk),
	.Flush		(Jump||(Branch&eq)),
	.Stall		(Stall|MemStall),
	.Control_i	(),
	.Control	(),
	.Instr_i	(Instr),
	.Instr		(Instr_ID),
	.data0_i	(),
	.data0		(),
	.data1_i	(),
	.data1		(),
	.data2_i	(NextPC_IF),
	.data2		(NextPC_ID),
	.RegAddr_i	(),
	.RegAddr	()
);

wire			RegWrite,RegDst,ALUSrc,Branch,Jump,MemWrite_ID,MemRead,MemtoReg;
wire	[1:0]	ALUOp;
wire	[31:0]	RSdata,RTdata,RDdata,ALURes_WB,Control_WB,Imm;
wire	[4:0]	RegAddr_WB;

Control Control(
	.Op			(Instr_ID[31:26]),
	.RegWrite	(RegWrite),
	.RegDst		(RegDst),
	.ALUSrc		(ALUSrc),
	.ALUOp		(ALUOp),
	.Branch		(Branch),
	.Jump		(Jump),
	.MemWrite	(MemWrite_ID),
	.MemRead	(MemRead),
	.MemtoReg	(MemtoReg)
);

Registers Registers(
	.clk		(clk),
	.RegWrite	(Control_WB[0:0]),
	.RSaddr		(Instr_ID[25:21]),
	.RTaddr		(Instr_ID[20:16]),
	.RDaddr		(RegAddr_WB),
	.RSdata		(RSdata),
	.RTdata		(RTdata),
	.RDdata		(RDdata)
);

wire eq;
Comparator cmp(
	.data0(RSdata),
	.data1(RTdata),
	.res(eq)
);

wire	 [31:0]	Offset,Baddr;

Signed_Extend Sign_extend(Instr_ID[15:0],Imm);

ShiftLeftTwo32 ShlB(Imm,Offset);

Adder ADD(NextPC_ID,Offset,Baddr);

wire	[31:0]	Control_ID;

MUX32 mux8({22'b0,MemtoReg,MemRead,MemWrite_ID,Jump,Branch,ALUOp,ALUSrc,RegDst,RegWrite},0,MUXSel,Control_ID);

wire	[31:0]	Instr_EX,Control_EX,RSdata_EX,RTdata_EX,Imm_EX;

Pipeline_Registers ID_EX(
	.clk		(clk),
	.Flush		(0),
	.Stall		(MemStall),
	.Control_i	(Control_ID),
	.Control	(Control_EX),
	.Instr_i	(Instr_ID),
	.Instr		(Instr_EX),
	.data0_i	(RSdata),
	.data0		(RSdata_EX),
	.data1_i	(RTdata),
	.data1		(RTdata_EX),
	.data2_i	(Imm),
	.data2		(Imm_EX),
	.RegAddr_i	(),
	.RegAddr	()
);

wire	[2:0]	ALUCtrl;
wire	[31:0]	ALUdata0,ALUdata1,ALURes,RTdata_FW;

ALU ALU(
	.data0		(ALUdata0),
	.data1		(ALUdata1),
	.ALUCtrl	(ALUCtrl),
	.res		(ALURes)
);

ALU_Control ALU_Control(
	.func		(Instr_EX[5:0]),
	.ALUOp		(Control_EX[4:3]),
	.ALUCtrl	(ALUCtrl)
);

wire	[4:0]	RegAddr;

wire	[1:0]	Ci_m6, Ci_m7;

Forwarding_unit FW(
	.data0_i	(Instr_EX[25:21]),
	.data1_i	(Instr_EX[20:16]),
	.data2_i	(RegAddr_MEM),
	.data3_i	(Control_MEM[0:0]),
	.data4_i	(RegAddr_WB),
	.data5_i	(Control_WB[0:0]),
	.data0_o	(Ci_m6),
	.data1_o	(Ci_m7)
);

TriMUX mux6(RSdata_EX,RDdata,ALURes_MEM,Ci_m6,ALUdata0);
TriMUX mux7(RTdata_EX,RDdata,ALURes_MEM,Ci_m7,RTdata_FW);

MUX5 mux3(Instr_EX[15:11],Instr_EX[20:16],Control_EX[1:1],RegAddr);

MUX32 mux4(RTdata_FW,Imm_EX,Control_EX[2:2],ALUdata1);

wire	[31:0]	Control_MEM,ALURes_MEM,RTdata_MEM;
wire	[4:0]	RegAddr_MEM;

Pipeline_Registers EX_MEM(
	.clk		(clk),
	.Flush		(0),
	.Stall		(MemStall),
	.Control_i	(Control_EX),
	.Control	(Control_MEM),
	.Instr_i	(),
	.Instr		(),
	.data0_i	(ALURes),
	.data0		(ALURes_MEM),
	.data1_i	(RTdata_FW),
	.data1		(RTdata_MEM),
	.data2_i	(),
	.data2		(),
	.RegAddr_i	(RegAddr),
	.RegAddr	(RegAddr_MEM)
);

wire	[31:0]	MemData,MemData_WB;

dcache_top dcache
(
	.clk_i(clk),
	.rst_i(rst),
	.mem_data_i(ReadData),
	.mem_ack_i(MemAck), 	
	.mem_data_o(WriteData),
	.mem_addr_o(MemAddr),
	.mem_enable_o(MemEnable),
	.mem_write_o(MemWrite),

	.p1_data_i(RTdata_MEM),
	.p1_addr_i(ALURes_MEM),
	.p1_MemRead_i(Control_MEM[8]),
	.p1_MemWrite_i(Control_MEM[7]),
	.p1_data_o(MemData),
	.p1_stall_o(MemStall)
);

Pipeline_Registers MEM_WB(
	.clk		(clk),
	.Flush		(0),
	.Stall		(MemStall),
	.Control_i	(Control_MEM),
	.Control	(Control_WB),
	.Instr_i	(),
	.Instr		(),
	.data0_i	(ALURes_MEM),
	.data0		(ALURes_WB),
	.data1_i	(MemData),
	.data1		(MemData_WB),
	.data2_i	(),
	.data2		(),
	.RegAddr_i	(RegAddr_MEM),
	.RegAddr	(RegAddr_WB)
);

MUX32 mux5(ALURes_WB,MemData_WB,Control_WB[9:9],RDdata);
integer i;
parameter	nop=32'b00000000000000000000000000100000; // add r0,r0,r0
initial begin
	for(i=0;i<32;i=i+1)
		Registers.register[i]=0;
	//CPU.Registers.register[1]=1;

	Control.Jump=0;
	Control.Branch=0;
	cmp.res=0;

	HD.stall=0;
	HD.MUXsel=0;
	IF_ID.Instr=nop;
	ID_EX.Instr=nop;
	ID_EX.Control=0;
	EX_MEM.Control=0;
	MEM_WB.Control=0;
end
endmodule
