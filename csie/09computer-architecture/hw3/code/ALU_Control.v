module ALU_Control(Instr,ALUOp,ALUCtrl);
parameter Add=6'b100000,Sub=6'b100010,And=6'b100100,Or=6'b100101,Mul=6'b011000;
parameter ALUAdd=3'd0,ALUSub=3'd1,ALUAnd=3'd2,ALUOr=3'd3,ALUMul=3'd4;
input	[5:0]	Instr;
input	[1:0]	ALUOp;
output	[2:0]	ALUCtrl;

assign ALUCtrl = ALUOp?ALUAdd:
    Instr==Add?ALUAdd:
    Instr==Sub?ALUSub:
    Instr==And?ALUAnd:
    Instr==Or?ALUOr:
    Instr==Mul?ALUMul:0;

endmodule
