module ALU_Control(funct_i,ALUOp_i,ALUCtrl_o);
parameter Add=6'b100000,Sub=6'b100010,And=6'b100100,Or=6'b100101,Mul=6'b011000,Slt=6'b101010;
parameter ALUAnd=3'd0,ALUOr=3'd1,ALUAdd=3'd2,ALUMul=3'd3,ALUSub=3'd6,ALUSlt=3'd7;
input	[5:0]	funct_i;
input	[1:0]	ALUOp_i;
output	[2:0]	ALUCtrl_o;

assign ALUCtrl_o = 
	(ALUOp_i==1?ALUSub:
	ALUOp_i==0?ALUAdd:
    funct_i==Add?ALUAdd:
    funct_i==Sub?ALUSub:
    funct_i==And?ALUAnd:
	funct_i==Or?ALUOr:
    funct_i==Mul?ALUMul:
	funct_i==Slt?ALUSlt:0);

endmodule
