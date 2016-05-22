#include<cstdio>
#include"FheapB7.h"
const int inf=20000,dx[]={1,0,-1,0},dy[]={0,1,0,-1};
int s[1000][1000],d[1000][1000];
node *ptr[1000][1000];
main()
{
    Fheap heap;
    int i,j,nx,ny,n,m,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&s[i][j]),d[i][j]=inf;
        d[0][0]=s[0][0];
        while(heap.n)heap.extractmin();
        ptr[0][0]=heap.insert(d[0][0],0);
        while(heap.n)
        {
            node nd=heap.extractmin();
            d[nd.v/m][nd.v%m]=nd.d;
            for(i=0;i<4;i++)
            {
                nx=nd.v/m+dx[i],ny=nd.v%m+dy[i];
                if(nx>=0 && nx<n && ny>=0 && ny<m && nd.d+s[nx][ny]<d[nx][ny])
                {
                    if(d[nx][ny]<inf)
                        ptr[nx][ny]->decrease(nd.d+s[nx][ny],&heap.min);
                    else
                        ptr[nx][ny]=heap.insert(nd.d+s[nx][ny],nx*m+ny);
                    d[nx][ny]=nd.d+s[nx][ny];
                }
            }
        }
        printf("%d\n",d[n-1][m-1]);
    }
}
