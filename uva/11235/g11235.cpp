#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
main()
{
    srand(time(NULL));
    int t,i,j,k,n=20,m=20,s[21];
    char tmp[99];
    for(t=0;t<50;t++)
    {
        sprintf(tmp,"%d.in",t+1);
        freopen(tmp,"w",stdout);
        printf("%d %d\n",n,m);
        for(i=0;i<n;i++)
            s[i]=rand()%10;
        std::sort(s,s+n);
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");
        for(i=0;i<m;i++)
        {
            j=1+rand()%20;
            k=1+rand()%20;
            printf("%d %d\n",j<?k,j>?k);
        }
        printf("%d\n",0);
        fclose(stdout);
        sprintf(tmp,"Q11235a<%d.in>%d.out",t+1,t+1);
        system(tmp);
    }
}
