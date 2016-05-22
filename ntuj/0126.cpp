#include<cstdio>
int n,u,count,s[3001][3001];
inline char valid(int x,int y){return(x>=0 && x<=n && y>=0 && y<=n && s[x][y]!=u);}
inline char go(int x,int y,int z)
{
    count++;
    if(s[x][y]<0)return 1;
    s[x][y]=u;
    if(valid(2*y-x+1,2*x-y-1) && go(2*y-x+1,2*x-y-1,z))return 1;
    if(valid(y,x) && go(y,x,z))return 1;
    if(valid(x,z) && go(x,z,y))return 1;
    return 0;
}
main()
{
    int x1,y1,z1,x2,y2,z2;
    while(scanf("%d",&n) && n)
    {
        scanf("%d %d %d %d %d %d",&x1,&y1,&z1,&x2,&y2,&z2);
        if(x1+y1+z1!=x2+y2+z2)goto no;
        s[x2][y2]=s[y2][x2]=s[x2][z2]=s[z2][x2]=s[y2][z2]=s[z2][y2]=-1;
        u++;
        count=0;
        if(go(x1,y1,z1))puts("Yes");
        else
        no: puts("No");
        printf("%d\n",count);
        s[x2][y2]=s[y2][x2]=s[x2][z2]=s[z2][x2]=s[y2][z2]=s[z2][y2]=0;
    }
}
