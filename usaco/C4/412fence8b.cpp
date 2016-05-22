/*
ID: s0000151
PROG: fence8
LANG: C++
*/


#include <stdio.h>
#include <stdlib.h>

#define MAXBOARDS 50
#define MAXRAILS 1024

int nboards;
int boards[MAXBOARDS];
int next_board;

int nrails;
int rails[MAXRAILS];
int used[MAXRAILS];
int nused;

int best;

int num_V, num_L, num_R;

int comp_func( const void *a, const void *b );
int rev_comp_func( const void *a, const void *b );
void search( void );
int maximal( int k, int next, int other, int smin, int smax,
			 int remain[], int origid[], int bound );

inline int max( int a, int b )
{
	return (a < b) ? b : a;
}

int main( void )
{
	FILE *input = fopen( "fence8.in", "r" );
	fscanf( input, "%d", &nboards );
	for (int i = 0; i < nboards; i++)
		fscanf( input, "%d", &boards[i] );
	fscanf( input, "%d", &nrails );
	for (int i = 0; i < nrails; i++)
		fscanf( input, "%d", &rails[i] );
	rails[nrails++] = 1000000;
	qsort( boards, nboards, sizeof(int), comp_func );
	qsort( rails, nrails, sizeof(int), comp_func );

	int ans;
	if (boards[nboards-1] >= 1000000)
		// the answer might be off by one if we could supply the big rail.
		// but then we could supply all the other rails, so no need to search.
		ans = nrails - 1;
	else
	{
		next_board = 0;
		search();
		ans = best;
	}

	FILE *output = fopen( "fence8.out", "w" );
	fprintf( output, "%d\n", ans );

	//fprintf( stderr, "%d %d %d %d\n", ans, num_V, num_L, num_R );

	return 0;
}

int comp_func( const void *a, const void *b )
{
	const int *p = (const int *)a;
	const int *q = (const int *)b;
	if (*p < *q)
		return -1;
	else if (*p > *q)
		return 1;
	else
		return 0;
}

int rev_comp_func( const void *a, const void *b )
{
	return -comp_func( a, b );
}


void search( void )
{
	if (next_board == nboards)
	{
		if (best < nused)
			best = nused;
//		fprintf( stderr, "nused = %d best = %d\n", nused, best );
		return;
	}

int nremain;
int remain[MAXRAILS];
int origid[MAXRAILS];

	// find remaining rails,
	// as well as max # for this board, all remaining boards
	int boardsum = 0;
	for (int j = next_board; j < nboards; j++)
		boardsum += boards[j];

	nremain = 0;
	int k = 0, l = 0;
	for (int j = 0, sum = 0; j < nrails; j++)
		if (used[j] == 0)
		{
			remain[nremain] = rails[j];
			origid[nremain] = j;
			nremain++;
			sum += rails[j];
			if (sum <= boards[next_board])
				k++;
			if (sum <= boardsum)
				l++;
		}

	int bound;
	if ((bound = nused + l) <= best)
		return;
	// try all maximal m-subsets of remaining boards
	for (int m = k; m >= 0; m--)
		maximal( m, l-1, nremain-1, 0, boards[next_board],
				 remain, origid, bound );
}

int maximal( int k, int next, int other, int smin, int smax,
			 int remain[], int origid[], int bound )
{
	if (k == 0)
	{
		if ((smin <= 0) && (0 <= smax))
		{
			next_board++;
			search();
			next_board--;
		}
		return 0;
	}

	if (k > next+1)
		return 0;		// not enough boards left

	num_V++;

	int low_sum = 0;
	for (int j = 0; j < k; j++)
		low_sum += remain[j];
	if (low_sum > smax)
	{
		num_L++;
		return 0;
	}
	int hi_sum = 0;
	for (int j = 0; j < k; j++)
		hi_sum += remain[next-j];
	if (hi_sum < smin)
	{
		num_R++;
		return 0;
	}

	int last = other;
	for (int m = next; m >= k-1; m--)
	{
		if (remain[m] != remain[last] && (low_sum - remain[k-1] + remain[m]) <= smax)
		{
			int new_min = max( smin - remain[m], smax - remain[last] + 1 );
			used[origid[m]] = 1;
			nused++;
			int x = maximal( k-1, m-1, last, new_min, smax - remain[m],
							 remain, origid, bound );
			used[origid[m]] = 0;
			nused--;

			if (k == 1)
				return 0;

			if (bound <= best)
				return 0;
		}
		last = m;
	}

	return 0;
}
