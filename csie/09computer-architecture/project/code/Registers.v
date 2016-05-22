module Registers(clk,RegWrite,RSaddr,RTaddr,RDaddr,RDdata,RSdata,RTdata);

input               clk,RegWrite;
input   [4:0]       RSaddr,RTaddr,RDaddr;
input   [31:0]      RDdata;
output  [31:0]      RSdata,RTdata;

reg     [31:0]      register        [0:31];

assign  RSdata=register[RSaddr];
assign  RTdata=register[RTaddr];

initial begin
	register[0] <= 0;
end

always@(negedge clk) begin
	if(RegWrite)
		if(RDaddr != 0)
	        register[RDaddr] <= RDdata;
end
   
endmodule 
