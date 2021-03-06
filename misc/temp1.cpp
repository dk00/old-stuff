/*
ID:s0000151
PROG:ditch
LANG:C++
*/
#include <stdio.h>
#include <string.h>

#define MAXI 200

/* total drain amount between intersection points */
int drain[MAXI][MAXI];
int nint; /* number of intersection points */

int cap[MAXI]; /* amount of flow that can get to each node */
int vis[MAXI]; /* has this node been visited by Dijkstra's yet? */
int src[MAXI]; /* the previous node on the path from the source to here */

int augment(void)
 { /* run a Dijkstra's varient to find maximum augmenting path */
  int lv;
  int mloc, max;
  int t;

  memset(cap, 0, sizeof(cap));
  memset(vis, 0, sizeof(vis));

  cap[0] = 2000000000;
  while (1)
   {
    /* find maximum unvisited node */
    max = 0;
    mloc = -1;
    for (lv = 0; lv < nint; lv++)
      if (!vis[lv] && cap[lv] > max)
       {
        max = cap[lv];
	mloc = lv;
       }
    if (mloc == -1) return 0;
    if (mloc == nint-1) break; /* max is the goal, we're done */

    vis[mloc] = -1; /* mark as visited */

    /* update neighbors, if going through this node improves the
       capacity */
    for (lv = 0; lv < nint; lv++)
      if (drain[mloc][lv] > cap[lv] && max > cap[lv])
       {
        cap[lv] = drain[mloc][lv];
	if (cap[lv] > max) cap[lv] = max;
	src[lv] = mloc;
       }
   }
  max = cap[nint-1];

  /* augment path, starting at end */
  for (lv = nint-1; lv > 0; lv = src[lv])
   {
    t = src[lv];
    drain[t][lv] -= max;
    drain[lv][t] += max;
   }
  return max;
 }

int main(int argc, char **argv)
 {
  FILE *fout, *fin;
  int lv;
  int num;
  int p1, p2, c;

  if ((fin = fopen("ditch.in", "r")) == NULL)
   {
    perror ("fopen fin");
    exit(1);
   }
  if ((fout = fopen("ditch.out", "w")) == NULL)
   {
    perror ("fopen fout");
    exit(1);
   }

  fscanf (fin, "%d %d", &num, &nint);
  while (num--)
   {
    fscanf (fin, "%d %d %d", &p1, &p2, &c);
    p1--;
    p2--;
    drain[p1][p2] += c; /* note += handles two ditches between same points */
   }

  /* max flow algorithm: augment while you can */
  c = 0;
  while ((p1 = augment()))
    c += p1;
  fprintf (fout, "%d\n", c);
  return 0;
 }
