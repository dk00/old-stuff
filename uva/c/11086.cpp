#include<cstdio>
#include<cstring>
const int max=1048576;
bool notp[max];
int p[1000000],q[1000000];
main()
{
    int i,j,pn=0;
    for(i=3;i<max;i++)
    {
        if(i%2==0 || notp[i])
        {
            p[pn++]=i;
            continue;
        }
        for(j=i*3;j<max;j+=i*2)
            notp[j]=1;
    }
    memset(notp,1,sizeof(notp));
    for(i=0;i<pn;i++)
        notp[p[i]]=0;
    for(i=0;i<pn;i++)
    {
        if(notp[p[i]])continue;
        for(j=p[i]*2;j<max;j+=p[i])
            notp[j]=1;
    }
    while(scanf("%d",&pn)==1)
    {
        for(j=0;pn--;)
        {
            scanf("%d",&i);
            j+=!notp[i];
        }
        printf("%d\n",j);
    }
}
