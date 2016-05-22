//=======================================================================
//
// SAMPLE SOURCE CODE - SUBJECT TO THE TERMS OF END-USER LICENSE AGREEMENT FOR
// INTEL(R) PARALLEL ADVISOR 2011.
//
// Copyright 2009-2010 Intel Corporation
//
// THIS FILE IS PROVIDED "AS IS" WITH NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
// NOT LIMITED TO ANY IMPLIED WARRANTY OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS.
//
// ========================================================================

// [DESCRIPTION]
// Solve the nqueens problem  - how many positions of queens can fit on a chess board
// of a given size without attacking each other.
//
// [BUILD]
// Use a Release configuration to ensure you find a hotspot representative of a final production build.
//
// [RUN]
// To set the board size in Visual Studio, right click on the project,
// select Properies > Configuration Properties > General > Debugging.  Set
// Command Arguments to the desired value.  13 has been set as the default.
//
// [EXPECTED OUTPUT]
//
// Board Size   Number of Solutions
//     4                2
//     5               10
//     6                4
//     7               40
//     8               92
//     9              352
//    10              724
//    11             2680
//    12            14200
//    13            73712
//    14           365596
//    15          2279184

#include <iostream>
#include <omp.h>
#include <cilk/cilk.h>
#include <cilk/reducer_opadd.h>

using namespace std;

int nrOfSolutions ;  //keeps track of the number of solutions
int size = 14;  // the board-size read from command-line
int correctSolution[16]; //array of the number of correct solutions for each board size

/*
Recursive function to find all solutions on a board 
represented by the argument "queens", placing the next queen
at location (row, col)

On Return: nrOfSolutions has been increased to add solutions for this board

*/
void setQueen(int queens[], int row, int col) {
	//check all previously placed rows for attacks
	for(int i=0; i<row; i++) {
		// vertical attacks
		if (queens[i]==col) {
			return;
		}
		// diagonal attacks
		if (abs(queens[i]-col) == (row-i) ) {
			return;
		}
	}
	// column is ok, set the queen
	queens[row]=col;

	if(row==size-1) {

		nrOfSolutions++;  //Placed final queen, found a solution
	}
	else {
		// try to fill next row
		for(int i=0; i<size; i++) {

			setQueen(queens, row+1, i);
		}
	}
}

/*
Function to find all solutions for nQueens problem on size x size chessboard.

On Return: nrOfSoultions = number of solutions for size x size chessboard.
*/
void solve() {
	 //array representing queens placed on a chess board.  Index is row position, value is column.

		for(int i=0; i<size; i++) {
			int * queens = (int*) malloc(size*sizeof(int));
			// try all positions in first row
				setQueen(queens, 0, i);		
				free(queens);
		}
}


int main(int argc, char*argv[]) {
	if(argc !=2) {
		cerr << "Usage: nqueens_cilk boardSize [default is 14].\n";
		
	} else {
		size = atoi(argv[1]);
		if (size < 4 || size > 15) {
			cerr << "Boardsize should be between 4 and 15; setting it to 13. \n" << endl;
			
		}
	}
	// Set the expected number of solutions for each board-size for later checking.
	correctSolution[0] = 0;
	correctSolution[1] = 0;
	correctSolution[2] = 0;
	correctSolution[3] = 0;
	correctSolution[4] = 2;
	correctSolution[5] = 10;
	correctSolution[6] = 4;
	correctSolution[7] = 40;
	correctSolution[8] = 92;
	correctSolution[9] = 352;
	correctSolution[10] = 724;
	correctSolution[11] = 2680;
	correctSolution[12] = 14200;
	correctSolution[13] = 73712;
	correctSolution[14] = 365596;
	correctSolution[15] = 2279184;

	cout << "Starting nqueens_cilk  solver for size " << size << "...\n";
	double t =omp_get_wtime();
	solve();
	t = omp_get_wtime() - t ;
	cout << "Number of solutions: " << nrOfSolutions << endl;
	if (nrOfSolutions != correctSolution[size])
		cout << "!!Incorrect result!! Number of solutions should be " << correctSolution[size] << endl << endl;
	else
		cout << "Correct result!" << endl;

	cout << "Calculations took " << t << "s.\n";

	return 0;
}
