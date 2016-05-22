module Hazard_Detection_unit(instruction, memread, RDadd, stall, MUXsel);

input [31:0]	instruction;
input [4:0]	RDadd;
input memread;
output stall, MUXsel;

reg stall, MUXsel;

always@(instruction, memread, RDadd)begin
	stall = 1'b0;
	MUXsel = 1'b0;
	if(memread == 1'b1)begin // lw
		if(instruction[31:26]==6'b0 	 /*rtype*/
		 ||instruction[31:26]==6'b000100 /*beq*/)
			if(RDadd == instruction[25:21]/*RS*/|| RDadd ==instruction[20:16] /*RT*/)  begin
				stall <= 1'b1;
				MUXsel <= 1'b1;
			end
		if(instruction[31:26]==6'b100011 //lw
		 ||instruction[31:26]==6'b101011 //sw
	 	 ||instruction[31:26]==6'b001000) //addi
		 	if(RDadd == instruction[25:21]/*RS*/)begin
				stall <= 1'b1;
				MUXsel <= 1'b1;
			end
	end
end
endmodule
