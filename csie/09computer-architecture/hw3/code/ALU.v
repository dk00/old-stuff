module ALU(a,b,func,res,Zero);
parameter Add=3'd0,Sub=3'd1,And=3'd2,Or=3'd3,Mul=3'd4;
input	[31:0]	a;
input	[31:0]	b;
input	[2:0]	func;
output	[31:0]	res;
output	[31:0]	Zero;

assign Zero=0;
assign res=(func==Add)?(a+b):
    (func==Sub)?(a-b):
    (func==And)?(a&b):
    (func==Or)?(a|b):
    (func==Mul)?(a*b):0;

endmodule
