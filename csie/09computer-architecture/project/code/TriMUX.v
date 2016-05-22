module TriMUX(data0,data1,data2,sel,data);
input	[31:0]	data0,data1,data2;
input	[1:0]	sel;
output	[31:0]	data;

assign	data=sel==0?data0:(sel==1?data1:data2);
endmodule
