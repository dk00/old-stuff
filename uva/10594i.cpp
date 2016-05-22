#include <iostream>
#include<cstring>
using namespace std;

// the maximum number of vertices + 1
#define NN 104

// adjacency matrix (fill this up)
long long cap[NN][NN];

// cost per unit of flow matrix (fill this up)
long long cost[NN][NN];

// flow network and adjacency list
long long fnet[NN][NN], adj[NN][NN], deg[NN];

// Dijkstra's predecessor, depth and priority queue
long long par[NN], d[NN], q[NN], inq[NN], qs;

// Labelling function
long long pi[NN];

void CLR(long long a[], char x) {memset( a, x, sizeof( a ) );}
const long long Inf=1000000000;
#define BUBL { \
    t = q[i]; q[i] = q[j]; q[j] = t; \
    t = inq[q[i]]; inq[q[i]] = inq[q[j]]; inq[q[j]] = t; }

// Dijkstra's using non-negative edge weights (cost + potential)
#define Pot(u,v) (d[u] + pi[u] - pi[v])
bool dijkstra( long long n, long long s, long long t )
{
    CLR( d, 0x3F );
    CLR( par, -1 );
    CLR( inq, -1 );
    //for( long long i = 0; i < n; i++ ) d[i] = Inf, par[i] = -1;
    d[s] = qs = 0;
    inq[q[qs++] = s] = 0;
    par[s] = n;

    while( qs )
    {
        // get the minimum from q and bubble down
        long long u = q[0]; inq[u] = -1;
        q[0] = q[--qs];
        if( qs ) inq[q[0]] = 0;
        for( long long i = 0, j = 2*i + 1, t; j < qs; i = j, j = 2*i + 1 )
        {
            if( j + 1 < qs && d[q[j + 1]] < d[q[j]] ) j++;
            if( d[q[j]] >= d[q[i]] ) break;
            BUBL;
        }

        // relax edge (u,i) or (i,u) for all i;
        for( long long k = 0, v = adj[u][k]; k < deg[u]; v = adj[u][++k] )
        {
            // try undoing edge v->u
            if( fnet[v][u] && d[v] > Pot(u,v) - cost[v][u] )
                d[v] = Pot(u,v) - cost[v][par[v] = u];

            // try using edge u->v
            if( fnet[u][v] < cap[u][v] && d[v] > Pot(u,v) + cost[u][v] )
                d[v] = Pot(u,v) + cost[par[v] = u][v];

            if( par[v] == u )
            {
                // bubble up or decrease key
                if( inq[v] < 0 ) { inq[q[qs] = v] = qs; qs++; }
                for( long long i = inq[v], j = ( i - 1 )/2, t;
                     d[q[i]] < d[q[j]]; i = j, j = ( i - 1 )/2 )
                     BUBL;
            }
        }
    }

    for( long long i = 0; i < n; i++ ) if( pi[i] < Inf ) pi[i] += d[i];

    return par[t] >= 0;
}
#undef Pot

long long mcmf4( long long n, long long s, long long t, long long &fcost ,long long dd)
{
    // build the adjacency list
    CLR( deg, 0 );
    for( long long i = 0; i < n; i++ )
    for( long long j = 0; j < n; j++ )
        if( cap[i][j] || cap[j][i] ) adj[i][deg[i]++] = j;

    memset( fnet, 0 ,sizeof(fnet));
    CLR( pi, 0 );
    long long flow = fcost = 0;

    // repeatedly, find a cheapest path from s to t
    while( dd>0 && dijkstra( n, s, t ) )
    {
        // get the bottleneck capacity
        long long bot = Inf;
        for( long long v = t, u = par[v]; v != s; u = par[v = u] )
            bot <?= fnet[v][u] ? fnet[v][u] : ( cap[u][v] - fnet[u][v] );
        bot<?=dd;
        // update the flow network
        for( long long v = t, u = par[v]; v != s; u = par[v = u] )
            if( fnet[v][u] ) { fnet[v][u] -= bot; fcost -= bot * cost[v][u]; }
            else { fnet[u][v] += bot; fcost += bot * cost[u][v]; }

        flow += bot;
        dd-=bot;
    }

    return dd<=0;
}

//----------------- EXAMPLE USAGE -----------------
#include <cstdio>
using namespace std;

int main()
{
    long long i,j,k,n,m;
    while(scanf("%lld %lld",&n,&m)==2)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                cap[i][j]=0;
        while(m--)
        {
            scanf("%lld %lld",&i,&j),i--,j--;
            scanf("%lld",&cost[i][j]);
            cost[j][i]=cost[i][j];
            cap[i][j]=cap[j][i]=1;
        }
        scanf("%lld %lld",&k,&m);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(cap[i][j])cap[i][j]=m;
        if(mcmf4(n,0,n-1,m,k))
            printf("%lld\n",m);
        else
            puts("Impossible.");
    }
    return 0;
}
