#include<stdio.h>
inline int abs(int n)
{
    if(n<0)
        return -n;
    return n;
}
struct Data
{
    int tmpi,x,y,len;
};
main()
{
    int i,j,n,t,nx,ny,sx,sy,depth,len,min,x[11],y[11],picked[11];
    int M,N;
    Data stack[20];
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&M,&N);
        scanf("%d %d",&sx,&sy);
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%d %d",&x[i],&y[i]);
            picked[i]=0;
        }
        min=M*N+M+N;
        //void dfs(int depth,int nx,int ny,int len)
        for(i=depth=0,nx=sx,ny=sy,len=0;;)
        {
            if(depth>=n)
            {
                len+=abs(nx-sx)+abs(ny-sy);
                if(len<min)
                    min=len;
                i=n;
            }
          //for(i=0;i<n;i++)
            if(i<n && picked[i]==0)
            {
                picked[i]=1;
                stack[depth].tmpi=i;
                stack[depth].x=nx;
                stack[depth].y=ny;
                stack[depth].len=len;
                len+=abs(nx-x[i])+abs(ny-y[i]);
                nx=x[i],ny=y[i];
                i=0;
                depth++;
                continue;
              //dfs(depth+1,sx[i],sy[i],len+);
            }
            if(i>=n)
            {
                depth--;
                if(depth<0)
                    break;
                nx=stack[depth].x;
                ny=stack[depth].y;
                len=stack[depth].len;
                i=stack[depth].tmpi;
                picked[i]=0;
            }
            i++;
          //return;
        }
        printf("The shortest path has length %d\n",min);
    }
}
