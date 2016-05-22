#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
struct pt{int x,y;}s[999999];
main()
{
    srand(time(NULL));
    int i,j,n=13,m,t;
    for(t=0;t<10;t++)
    {
        for(i=0;i<n;i++)
            for(j=i+1;j<n;j++)
                s[m++]=(pt){i+1,j+1};
        random_shuffle(s,s+m);
        m=rand()%(n*(n-1)/2)+1;
        printf("%d %d\n",n,m);
        while(m--)
            printf("%d %d\n",s[m].x,s[m].y);
    }
    puts("0 0");
}
