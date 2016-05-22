module Adder(data0,data1,res);
input	[31:0]	data0;
input	[31:0]	data1;
output	[31:0]	res;

assign res=data0+data1;

endmodule
