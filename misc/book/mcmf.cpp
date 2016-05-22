const long long inf=9223372036854775807ll;
const int V=100;
char u[V];
int n,p[V],q[V*V],cap[V][V],cost[V][V];
long long d[V+1];
long long sp()
{
    int i,j,k;
    for(i=0;i<n;i++)d[i]=inf,u[i]=1;
    q[0]=d[0]=u[0]=0;
    for(i=0,j=1;i<j;i++)
    {
        u[q[i]]=1;
        for(k=0;k<n;k++)
        {
            if(cap[q[i]][k]==2 && d[q[i]]-cost[k][q[i]]<d[k])
            {
                d[k]=d[p[k]=q[i]]-cost[k][q[i]];
                if(u[k])u[q[j++]=k]=0;
            }
            if(cap[q[i]][k]==1 && d[q[i]]+cost[q[i]][k]<d[k])
            {
                d[k]=d[p[k]=q[i]]+cost[q[i]][k];
                if(u[k])u[q[j++]=k]=0;
            }
        }
    }
    if(d[n-1]<inf)return d[n-1];
    return -1;
}
long long flow(int m)
{
    long long tmp,sum=0;
    while(m>0 && (tmp=sp())>=0)
    {
        sum+=tmp;
        m--;
        for(int i=n-1;i>0;i=p[i])
            cap[p[i]][i]--,cap[i][p[i]]++;
    }
    return sum;
}
