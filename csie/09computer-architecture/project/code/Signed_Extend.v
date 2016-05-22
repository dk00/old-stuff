module Signed_Extend(data_i,data_o);
input signed	[15:0]	data_i;
output signed	[31:0]	data_o;

assign data_o=data_i;

endmodule
