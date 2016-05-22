#include<cstdio>
const int Max=99;
main()
{
    int i,j,n,m,s0[99],s1[99];
    while(scanf("%d %d",&n,&m)==2 && n+m){
        for(i=0;i<Max;i++)
            s0[i]=s1[i]=0;
        for(i=0;i<n;i++){
            scanf("%d",&j);
            s0[j]++;
        }
        for(i=0;i<m;i++){
            scanf("%d",&j);
            s1[j]++;
        }
        for(i=j=0;i<Max;i++)
            j+=i*((s0[i]>s1[i])?s0[i]:s1[i]);
        printf("%d\n",j);
    }
}
