module Forwarding_unit(data0_i, data1_i, data2_i, data3_i, data4_i, data5_i, 
			data0_o, data1_o);

input	[4:0]	data0_i, data1_i, data2_i, data4_i;
input		data3_i, data5_i;
output	[1:0]	data0_o, data1_o;

reg	[1:0]	temp0_o, temp1_o;

assign	data0_o = temp0_o[1:0];
assign	data1_o = temp1_o[1:0];

//	data0_i:	ID/EX.Rs
//	data1_i:	ID/EX.Rt
//	data2_i:	EX/MEM.Rd
//	data3_i:	EX/MEM.RegWrite
//	data4_i:	MEM/WB.Rd
//	data5_i:	MEM/WB.RegWrite

always@(data0_i or data1_i or data2_i or data3_i or data4_i or data5_i)	begin
	temp0_o = 2'b00;
	temp1_o = 2'b00;
	if(data3_i && (data2_i != 0))	begin
		if(data2_i == data0_i)	begin
			temp0_o = 2'b10;
		end
		else if(data2_i == data1_i)	begin
			temp1_o = 2'b10;
		end
	end
	if(data5_i && (data4_i != 0))	begin
		if((data2_i != data0_i) && (data4_i == data0_i))	begin
			temp0_o = 2'b01;
		end
		else if((data2_i != data1_i) && (data4_i == data1_i))	begin
			temp1_o = 2'b01;
		end
	end
end

endmodule
