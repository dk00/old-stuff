#include<cstdio>
#include<algorithm>
struct pt
{
    int x,y,z;
    bool operator==(pt a){return!(x*a.y-a.x*y);}
}s[100000];
bool cmp(pt a,pt b)
{
    return(a.x<b.x ||(a.x==b.x && a.y<b.y));
}
int u[100000];
main()
{
    int i,j,k,n,C=1;
    while(scanf("%d",&n) && n)
    {
        for(i=0;i<n;i++)
            scanf("%d %d %d",&s[i].x,&s[i].y,&s[i].z),u[i]=1;
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(s[i]==s[j])
                {
                    if(cmp(s[i],s[j]) && s[i].z>=s[j].z)u[j]=0;
                    if(cmp(s[j],s[i]) && s[j].z>=s[i].z)u[i]=0;
                }
        for(i=0;u[i] && i<n;i++);
        printf("Data set %d:\n",C++);
        if(i>=n)puts("All the lights are visible.");
        else
        {
            for(i=j=0;i<n;i++)
                if(!u[i])s[j++]=s[i];
            std::sort(s,s+j,cmp);
            puts("Some lights are not visible:");
            for(i=0;i<j;i++)
            {
                printf("x = %d, y = %d",s[i].x,s[i].y);
                if(j-i-1)puts(";");
                else puts(".");
            }
        }
    }
}
