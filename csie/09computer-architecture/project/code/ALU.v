module ALU(data0,data1,ALUCtrl,res);
parameter And=3'd0,Or=3'd1,Add=3'd2,Mul=3'd3,Sub=3'd6;
input	[31:0]	data0,data1;
input	[2:0]	ALUCtrl;
output	[31:0]	res;
reg		[31:0]	res;

always@(data0 or data1 or ALUCtrl) begin
	case(ALUCtrl)
		Add:	res		<=	data0+data1;
		Sub:	res		<=	data0-data1;
		And:	res		<=	data0&data1;
		Or:	res		<=	data0|data1;
		Mul:	res		<=	data0*data1;
		default:res		<=	0;
	endcase
end

endmodule
