/*
PROB:twofive
LANG:C++
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 5

FILE   *in, *out;
long    numways[MAX + 1][MAX + 1][MAX + 1][MAX + 1][MAX + 1];

void
get_ways (void)
{
    int     ind[MAX], a;
    long    curways;
    numways[MAX][MAX][MAX][MAX][MAX] = 1;
    for (ind[0] = MAX; ind[0] >= 0; ind[0]--)
	for (ind[1] = ind[0]; ind[1] >= 0; ind[1]--)
	    for (ind[2] = ind[1]; ind[2] >= 0; ind[2]--)
		for (ind[3] = ind[2]; ind[3] >= 0; ind[3]--)
		    for (ind[4] = ind[3]; ind[4] >= 0; ind[4]--) {
			curways = 0;
			for (a = 0; a < MAX; a++)
			    if (ind[a] < MAX) {
				ind[a]++;
				curways += numways[ind[0]][ind[1]][ind[2]][ind[3]][ind[4]];
				ind[a]--;
			    }
			numways[ind[0]][ind[1]][ind[2]][ind[3]][ind[4]] += curways;
		    }
}

void
solve_for_num (void)
{
    int     a, b;
    long    num = 1;
    char    string[MAX * MAX + 1];
    int     wid[MAX] = {0};
    fscanf (in, "%s", &string);
    for (a = 0; a < MAX * MAX; a++) {
	for (b = 0; b < MAX; b++)
	    if (wid[b] < MAX) {
		if (int (string[b * MAX + wid[b]] - 'A') == a)
		    break;
		else {
		    wid[b]++;
		    num += numways[wid[0]][wid[1]][wid[2]][wid[3]][wid[4]];
		    wid[b]--;
		}
	    }
	wid[b]++;
    }
    fprintf (out, "%ld\n", num);
}

void
solve_for_string (void)
{
    char    string[MAX * MAX + 1] = {0};
    int     a, b, last;
    int     wid[MAX] = {0}, found;
    long    num, totalsum, tempsum;
    fscanf (in, "%ld", &num);
    totalsum = 0;
    for (a = 0; a < MAX * MAX; a++) {
	for (b = 0; b < MAX; b++)
	    if (wid[b] + 1 <= MAX && (b == 0 || (wid[b] + 1 <= wid[b - 1]))) {
		wid[b]++;
		tempsum = numways[wid[0]][wid[1]][wid[2]][wid[3]][wid[4]];
		wid[b]--;
		if (tempsum + totalsum >= num)
		    break;
		totalsum += tempsum;
	    }
	string[MAX * b + wid[b]] = char (a + 'A');
	wid[b]++;
    }
    for (a = 0; a < MAX * MAX; a++)
	fprintf (out, "%c", string[a]);
    fprintf (out, "\n");
    exit (0);
}

int
main ()
{
    in = fopen ("twofive.in", "r");
    out = fopen ("twofive.out", "w");
    get_ways ();
    char    option;
    fscanf (in, "%c", &option);
    if (option == 'W')
	solve_for_num ();
    else
	solve_for_string ();
    return 0;
}
