/*
ID: s0000151
PROG: milk6
LANG: C++
*/
#include <stdio.h>
#include <string.h>

#define MAXN 32

/* residual graph */
double graph[MAXN][MAXN];
int nloc; /* number locations */

/* the routes */
int troute[1000][3]; /* start, end, size */
int nroute; /* number routes */

/* was this node visited by the flood fill? */
int vis[1000];

/* augment the graph by a flow */
/* use dijkstra's to determine augmenting path of maximum capacity */
double augment(void)
 {
  double flow[32]; /* the maximum flow to a node */
  int touched[32]; /* have we visited this node? */
  int src[32];     /* where the flow into this node comes from */
  double max;
  int mloc;
  int lv; /* loop variable */
  int t;

  /* initialization */
  memset(flow, 0, sizeof(flow));
  memset(touched, 0, sizeof(touched));

  /* flow to first node is unbounded */
  flow[0] = 2000000000*1000.0 + 1.0;
  while (1)
   {
    /* find node with maximum capacity that hasn't been visited */
    mloc = -1;
    max = 0.9; /* smaller than any node that has a path to it */
    for (lv = 0; lv < nloc; lv++)
      if (!touched[lv] && flow[lv] > max)
       {
        max = flow[lv];
	mloc = lv;
       }

    if (mloc == -1) return -1; /* no augmented path! */

    /* if best node is maximum capacity node, then we are done */
    if (mloc == nloc-1) break;

    touched[mloc] = 1; /* mark as visited */
    /* for each adjacent node, see if path through this
       node has higher capacity than the current path for it */
    for (lv = 0; lv < nloc; lv++)
      if (graph[mloc][lv] > flow[lv] && max > flow[lv])
       { /* better path found */

        src[lv] = mloc;

	flow[lv] = graph[mloc][lv];
	if (flow[lv] > max) flow[lv] = max;
       }
   }

  /* starting at end, augment path */
  for (mloc = nloc-1; mloc > 0; mloc = src[mloc])
   {
    t = src[mloc];

    graph[t][mloc] -= max; /* remove forward arc */
    graph[mloc][t] += max; /* add back arc */
   }

  return max;
 }

/* calculate the flow */
double calc_flow(void)
 {
  double rv = 0.0;
  double t;

  /* just augment until we can't */
  while ((t = augment()) > -0.1)
    rv += t;
  return rv;
 }

/* create a graph with edges in troute */
void make_graph(void)
 {
  int lv;

  memset(graph, 0, sizeof(graph));
  for (lv = 0; lv < nroute; lv++)
    graph[troute[lv][0]][troute[lv][1]] += 1.0+(1001.0*troute[lv][2]);
 }

/* flood fill from this position */
void flood_fill(int pos)
 {
  int lv;

  vis[pos] = 1;

  /* for each neighbor, flood fill if necessary */
  for (lv = 0; lv < nloc; lv++)
    if (!vis[lv] && graph[pos][lv] > 0.1) flood_fill(lv);
 }

int main(int argc, char **argv)
 {
  FILE *fout, *fin;
  int lv;
  double goal;
  int t;
  double tv;

  if ((fin = fopen("milk6.in", "r")) == NULL)
   {
    perror ("fopen fin");
    exit(1);
   }
  if ((fout = fopen("milk6.out", "w")) == NULL)
   {
    perror ("fopen fout");
    exit(1);
   }

  fscanf (fin, "%d %d", &nloc, &nroute);
  for (lv = 0; lv < nroute; lv++)
   {
    fscanf (fin, "%d %d %d", troute[lv]+0, troute[lv]+1, troute[lv]+2);

    /* I'm using 0-based indexing instead of 1-based */
    troute[lv][0]--;
    troute[lv][1]--;
   }

  make_graph();
  goal = calc_flow();

  /* cost has been multiplied by 1001, so t is the real cost */
  t = (int)(goal / 1001.0);
  fprintf (fout, "%d %d\n", t, (int)(goal - t*1001.0));

  /* find min cut */

  /* find all nodes reachable from warehouse 1*/
  flood_fill(0);

  for (lv = 0; lv < nroute; lv++)
   { /* delete all arc from a reachable node to an unreachable one */
    if (vis[troute[lv][0]] == 1 && !vis[troute[lv][1]])
      fprintf (fout, "%d\n", lv+1);
   }

  return 0;
 }
