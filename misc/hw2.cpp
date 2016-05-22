#include<cstdio>
int dx[]={1,2,1,2,-1,-2,-1,-2},dy[]={2,1,-2,-1,2,1,-2,-1};
struct pa
{
    int d,v;
    bool operator<(pa x)const{return v<x.v;}
};
void bsort(pa s[],int n)
{
    int i,j;
    pa tmp;
    for(i=0;i<n;i++)
        for(j=1;j<n;j++)
            if(s[j]<s[j-1])
                tmp=s[j],s[j]=s[j-1],s[j-1]=tmp;
}
int n,map[1000][1000];
int count(int x,int y)
{
    int i,sum=0;
    for(i=0;i<8;i++)
        if(x+dx[i]>=0 && x+dx[i]<n && y+dy[i]>=0 && y+dy[i]<n
        && map[x+dx[i]][y+dy[i]]==0)sum++;
    return sum;
}
bool go(int d,int x,int y)
{
    if(d>n*n)return 1;
    int i,m;
    pa s[10];
    for(i=m=0;i<8;i++)
        if(x+dx[i]>=0 && x+dx[i]<n && y+dy[i]>=0 && y+dy[i]<n
        && map[x+dx[i]][y+dy[i]]==0)
            s[m++]=(pa){i,count(x+dx[i],y+dy[i])};
    bsort(s,m);
    for(i=0;i<m;i++)
    {
        map[x+dx[s[i].d]][y+dy[s[i].d]]=d;
        if(go(d+1,x+dx[s[i].d],y+dy[s[i].d]))
            return 1;
        map[x+dx[s[i].d]][y+dy[s[i].d]]=0;
    }
    return 0;
}
main()
{
    int i,j;
    char tmp[100];
    while(1)
    {
        printf("Enter Borad size: ");
        gets(tmp);
        if(sscanf(tmp,"%d",&n)!=1 || n<1)break;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                map[i][j]=0;
        map[0][0]=1;
        if(go(2,0,0))
            for(i=0;i<n;i++)
            {
                for(j=0;j<n;j++)
                    printf("%4d ",map[i][j]);
                puts("");
            }
        else
            puts("No Knight's tour exists");
    }
}
