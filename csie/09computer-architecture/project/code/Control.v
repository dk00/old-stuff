module Control(Op,RegWrite,RegDst,ALUSrc,ALUOp,Branch,Jump,MemWrite,MemRead,MemtoReg);
parameter Rtype=6'b000000,addi=6'b001000,beq=6'b000100,
		  lw=6'b100011,sw=6'b101011,J=6'b000010;
input	[5:0]	Op;
output			RegWrite,RegDst,ALUSrc,Branch,Jump,MemWrite,MemRead,MemtoReg;
output	[1:0]	ALUOp;
reg				RegWrite,RegDst,ALUSrc,Branch,Jump,MemWrite,MemRead,MemtoReg;
reg		[1:0]	ALUOp;
always@(Op) begin
	RegWrite	<=	0;
	RegDst		<=	0;
	ALUSrc		<=	0;
	ALUOp		<=	0;
	Branch		<=	0;
	Jump		<=	0;
	MemWrite	<=	0;
	MemRead		<=	0;
	MemtoReg	<=	0;
	case(Op)
	Rtype:	begin
		RegWrite	<=	1;
		ALUOp		<=	2;
	end
	addi:	begin
		ALUSrc		<=	1;
		RegDst		<=	1;
		RegWrite	<=	1;
	end
	beq:	begin
		Branch		<=	1;
		ALUOp		<=	1;
	end	
	J:
		Jump		<=	1;
	lw:		begin
		ALUSrc		<=	1;
		RegDst		<=	1;
		RegWrite	<=	1;
		MemRead		<=	1;
		MemtoReg	<=	1;
	end
	sw:		begin
		ALUSrc		<=	1;
    	MemWrite	<=	1;
	end
	endcase
end
endmodule
