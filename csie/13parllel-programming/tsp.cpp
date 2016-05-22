#include <omp.h>
#include <stdio.h>
#include <limits.h>

#include <advisor-annotate.h>

#define SIZE 20

int N;
int min_dis = INT_MAX;
int position[SIZE];
int coordinate[SIZE][2];
int correctSolution[SIZE];

omp_lock_t lock;

int ok(int position[], int next, int test)
{
    int i;

    for (i = 0; i < next; i++)
        if (position[i] == test)
            return 0;

    return 1;
}

void tsp(int position[], int visited, int next, int dis) {

    int test;
    
    if (dis >= min_dis) {
		return;
	}
    
	if (next >= N && dis < min_dis ) {
		omp_set_lock(&lock);
        min_dis = dis;
		omp_unset_lock(&lock);
        return;
    }
    
    for (test = 0; test < N; test++) { 
        //if (ok(position, next, test)) {
		if (!(visited&(1<<test))) {
            int dx, dy;
            position[next] = test;
            dx = coordinate[position[next - 1]][0] - coordinate[position[next]][0];
            dy = coordinate[position[next - 1]][1] - coordinate[position[next]][1];
            
            dis += dx * dx + dy * dy;
   
            tsp(position, visited|(1<<test), next + 1, dis);
			                 
            dis -= dx * dx + dy * dy;
        }
    }
}


int main()
{
    // Number of citys
	N = 18;
	
	// The coordinates of a city
	coordinate[0][0]  = 6; coordinate[0][1]  = 0;
	coordinate[1][0]  = 6; coordinate[1][1]  = 5;
	coordinate[2][0]  = 8; coordinate[2][1]  = 6;
	coordinate[3][0]  = 2; coordinate[3][1]  = 5;
	coordinate[4][0]  = 9; coordinate[4][1]  = 9;
	coordinate[5][0]  = 9; coordinate[5][1]  = 6;
	coordinate[6][0]  = 5; coordinate[6][1]  = 3;
	coordinate[7][0]  = 8; coordinate[7][1]  = 0;
	coordinate[8][0]  = 5; coordinate[8][1]  = 0;
	coordinate[9][0]  = 5; coordinate[9][1]  = 6;
	coordinate[10][0] = 1; coordinate[10][1] = 1;
	coordinate[11][0] = 2; coordinate[11][1] = 0;
	coordinate[12][0] = 3; coordinate[12][1] = 1;
	coordinate[13][0] = 0; coordinate[13][1] = 0;
	coordinate[14][0] = 2; coordinate[14][1] = 6;
	coordinate[15][0] = 2; coordinate[15][1] = 8;
	coordinate[16][0] = 6; coordinate[16][1] = 2;
	coordinate[17][0] = 8; coordinate[17][1] = 5;

	// Set the expected number of solutions for each city-size for later checking.

	correctSolution[1] = 0;
	correctSolution[2] = 25;
	correctSolution[3] = 30;
	correctSolution[4] = 61;
	correctSolution[5] = 72;
	correctSolution[6] = 72;
	correctSolution[7] = 54;
	correctSolution[8] = 58;
	correctSolution[9] = 58;
	correctSolution[10] = 54;
	correctSolution[11] = 78;
	correctSolution[12] = 72;
	correctSolution[13] = 68;
	correctSolution[14] = 72;
  correctSolution[15] = 72;
	correctSolution[16] = 80;
	correctSolution[17] = 74;
	correctSolution[18] = 74;
	
	int i;
	double t;

	
	printf("Starting TSP solver for size %d\n",N);
	t = omp_get_wtime();
	
	omp_init_lock(&lock);

	#pragma omp parallel for
	for (i = 0; i < N; i++) {
		
        int dis = 0;
        int position[SIZE];
        position[0] = i;
        
		tsp(position, 0, 1, dis);
    }

	t = omp_get_wtime() - t;
	
	omp_destroy_lock(&lock);

    printf("time: %lf\n", t);
	printf("Minimum distance: %d\n", min_dis);
	if (min_dis != correctSolution[N])
		printf("!!Incorrect result!! Minimum distance should be %d\n",correctSolution[N]);
	else
		printf("Correct result!\n");
	

    return 0;
}
