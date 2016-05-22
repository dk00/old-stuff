module Data_Memory
(
    clk_i,
    addr_i,
    data_i,
    MemRead_i,
    MemWrite_i,
    data_o
);

// Interface
input               clk_i;
input   [31:0]      addr_i;
input	[31:0]		data_i;
input               MemRead_i;
input               MemWrite_i;
output  [31:0]      data_o;


// Memory
reg	    [7:0]       memory  [0:32];	// address: 0x00~0x80


// Write Data      
always@(posedge clk_i) begin
    if(MemWrite_i) begin
        memory[addr_i+3] <= data_i[31:24];
        memory[addr_i+2] <= data_i[23:16];
        memory[addr_i+1] <= data_i[15:8];
        memory[addr_i]   <= data_i[7:0];
    end
end

// Read Data      
assign  data_o = (MemRead_i) ? {memory[addr_i+3], memory[addr_i+2], memory[addr_i+1], memory[addr_i]} : 32'b0;


endmodule
