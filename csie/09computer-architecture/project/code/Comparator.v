module Comparator(data0,data1,res);
input	[31:0]	data0,data1;
output			res;
reg				res;

always@(data0 or data1) begin
	if(data0==data1) 
		res <=	1;
	else 
		res	<=	0;
end
endmodule
