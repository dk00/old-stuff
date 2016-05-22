const int V=1005;
char p[V],c[V][V];
int t;
char go(int v)
{
    if(p[v])return 0;
    if(v==t)return 1;
    p[v]=1;
    for(int i=1;i<=t;i++)
        if(c[v][i]-- && go(i))
            return ++c[i][v];
        else c[v][i]++;
    return 0;
}
int flow()
{
    int i,j=0;
    while(go(0))
        for(j++,i=0;i<=t;i++)p[i]=0;
    return j;
}
