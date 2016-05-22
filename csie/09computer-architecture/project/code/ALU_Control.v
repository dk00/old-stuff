module ALU_Control(func,ALUOp,ALUCtrl);
parameter f_Add=6'b100000,f_Sub=6'b100010,f_And=6'b100100,f_Or=6'b100101,f_Mul=6'b011000;
parameter And=3'b000,Or=3'b001,Add=3'b010,Mul=3'b011,Sub=3'b110;
input	[5:0]	func;
input	[1:0]	ALUOp;
output	[2:0]	ALUCtrl;
reg		[2:0]	ALUCtrl;

always@(func or ALUOp) begin
	if(ALUOp == 2)
		case(func)
				f_Add:	ALUCtrl		<=	Add;
				f_Sub:	ALUCtrl		<=	Sub;
				f_And:	ALUCtrl		<=	And;
				f_Or:	ALUCtrl		<=	Or;
				f_Mul:	ALUCtrl		<=	Mul;
		endcase
	case(ALUOp)
		0:	ALUCtrl		<=	Add;
		1:	ALUCtrl		<=	Sub;
	endcase
end
endmodule
