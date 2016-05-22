module MUX5(a,b,sel,o);
input	[4:0]	a,b;
input		sel;
output	[4:0]	o;
reg	[4:0]	tmp;

assign o=(sel)?b:a;

endmodule
