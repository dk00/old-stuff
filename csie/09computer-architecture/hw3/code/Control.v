module Control(Op,RegDst,ALUOp,ALUSrc,RegWrite);
parameter ALU=6'b000000,Imm=6'b001000;
input	[5:0]	Op;
output		RegDst;
output	[1:0]	ALUOp;
output		ALUSrc;
output		RegWrite;

assign RegDst=(Op==Imm)?0:1;
assign ALUOp=(Op==Imm)?1:0;
assign ALUSrc=(Op==Imm)?1:0;
assign RegWrite=1;

endmodule
