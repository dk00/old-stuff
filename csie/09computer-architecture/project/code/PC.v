module PC(clk,rst,start,pc_i,pc_o,Stall,Enable);

input               clk,rst,start,Stall,Enable;
input   [31:0]      pc_i;
output  [31:0]      pc_o;

reg     [31:0]      pc_o;

always@(posedge clk or negedge rst) begin
    if(~rst)
        pc_o <= 0;
    else begin
		if(start) begin
			if(Enable && !Stall)
				pc_o <= pc_i;
		end
        else
            pc_o <= 0;
    end
end

endmodule
