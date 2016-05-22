module MUX32(a,b,sel,o);
input	[31:0]	a,b;
input	[0:0]	sel;
output	[31:0]	o;

assign o=(sel)?b:a;

endmodule
