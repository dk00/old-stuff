`define CYCLE_TIME 5
module TestBench;

reg	[31:0]	n0;
reg	[31:0]	n1;
reg	[2:0]	sel;
reg		clk;
wire	[31:0]	res;
wire	[31:0]	ground;
integer		count;

always #(`CYCLE_TIME/2) clk = ~clk;

//Adder Add(n0,res);
//Signed_Extend conv(n0,res);
//MUX5 mtest(n0,n1,sel,res);
//MUX32 mtest(n0,n1,sel,res);
ALU ALUtest(n0,n1,sel,res,ground);

parameter Add=3'd0,Sub=3'd1,And=3'd2,Or=3'd3,Mul=3'd4;
initial begin
    n0=123;
    n1=456;
    sel=Add;
    #1 $display("%d+%d = %d\n",n0,n1,res);
    sel=Sub;
    #1 $display("%d-%d = %d\n",n0,n1,res);
    sel=And;
    #1 $display("%d&%d = %d\n",n0,n1,res);
    sel=Or;
    #1 $display("%d|%d = %d\n",n0,n1,res);
    sel=Mul;
    #1 $display("%d*%d = %d\n",n0,n1,res);
    $stop;
end

endmodule
