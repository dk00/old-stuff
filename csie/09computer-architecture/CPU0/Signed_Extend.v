module Signed_Extend(i,o);
input	[15:0]	i;
output	[31:0]	o;

assign o = {i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i[15],i};

endmodule
