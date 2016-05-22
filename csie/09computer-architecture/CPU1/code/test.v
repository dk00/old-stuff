`define CYCLE_TIME 5
module TestBench;

reg		[31:0]	i0;
reg		[31:0]	i1;
wire	[31:0]	o0;
reg		[2:0]	sel;
reg		clk;
wire	[31:0]	res;
wire	[31:0]	ground;
integer		count;

always #(`CYCLE_TIME/2) clk = ~clk;

//ShiftLeftTwo26 Sh(i0,o0);
//ShiftLeftTwo32 Sh(i0,o0);
//Adder Add(n0,res);
//Signed_Extend conv(n0,res);
//MUX5 mtest(n0,n1,sel,res);
//MUX32 mtest(n0,n1,sel,res);
ALU ALUtest(i0,i1,sel,o0,ground);

parameter And=3'd0,Or=3'd1,Add=3'd2,Mul=3'd3,Sub=3'd6,Slt=3'd7;
initial begin
	i0=20;
	i1=3;
    sel=Add;
    #1 $display("%d+%d = %d\n",i0,i1,o0);
    sel=Sub;
    #1 $display("%d-%d = %d\n",i0,i1,o0);
    sel=And;
    #1 $display("%d&%d = %d\n",i0,i1,o0);
    sel=Or;
    #1 $display("%d|%d = %d\n",i0,i1,o0);
    sel=Mul;
    #1 $display("%d*%d = %d\n",i0,i1,o0);
    sel=Slt;
    #1 $display("%d<<%d = %d\n",i0,i1,o0);
	$stop;
end

endmodule
