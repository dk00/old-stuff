module ALU(data1_i,data2_i,ALUCtrl_i,data_o,Zero_o);
parameter And=3'd0,Or=3'd1,Add=3'd2,Mul=3'd3,Sub=3'd6,Slt=3'd7;
input	[31:0]	data1_i,data2_i;
input	[2:0]	ALUCtrl_i;
output	[31:0]	data_o;
output			Zero_o;

assign data_o=(ALUCtrl_i==Add)?(data1_i+data2_i):
    (ALUCtrl_i==Sub)?(data1_i-data2_i):
    (ALUCtrl_i==And)?(data1_i&data2_i):
    (ALUCtrl_i==Or)?(data1_i|data2_i):
    (ALUCtrl_i==Mul)?(data1_i*data2_i):
	(ALUCtrl_i==Slt)?(data1_i<<data2_i):0;
assign Zero_o=data_o==0?1:0;

endmodule
