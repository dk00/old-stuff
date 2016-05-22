module Pipeline_Registers(clk,Flush,Stall,
	Control_i,Instr_i,data0_i,data1_i,data2_i,RegAddr_i,
	Control,Instr,data0,data1,data2,RegAddr);
parameter	nop=32'b00000000000000000000000000100000; // add r0,r0,r0
input		clk,Flush,Stall;
input	[31:0]	Control_i,Instr_i,data0_i,data1_i,data2_i;
input	[4:0]	RegAddr_i;
output	[31:0]	Control,Instr,data0,data1,data2;
output	[4:0]	RegAddr;
reg	[31:0]	Control,Instr,data0,data1,data2;
reg	[4:0]	RegAddr;

always@(posedge clk) begin
	if(Flush == 1) begin	//Only for IF_ID
		Instr	<=	nop;
		data2	<=	data2_i;
	end
	else if(Stall != 1)begin
		Control	<=	Control_i;
		Instr	<=	Instr_i;
		data0	<=	data0_i;
		data1	<=	data1_i;
		data2	<=	data2_i;
		RegAddr	<=	RegAddr_i;
	end
	//else Stall
end
endmodule
