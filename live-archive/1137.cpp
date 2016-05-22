#include<vector>
#include<cstdio>
using namespace std;
vector<int> c[N];
main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&n,&m);
        for(i=0;i<n;i++)u[i]=0,c[i].clear();
        while(m--)
        {
            scanf("%d %d",&i,&j),i--,j--;
            c[i].push_back(j);
            c[j].push_back(i);
        }
        for(i=j=0;i<n;i++)
            if(!u[i])go(i);
        printf("%d\n",j);
        if(!j){puts("0");continue;}
        for(i=0;u[i]!=2;i++);
        printf("%d\n",++i);
        for(;i<n;i++)
            if(u[i]==2)printf(" %d",i+1);
        puts("");
    }
}
