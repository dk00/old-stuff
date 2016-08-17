#include<stdio.h>
int set[30001],dep[30001],num[30001];
main()
{
    int i,j,n,m,t,s1,s2,max;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d %d",&n,&m);
        for(i=1;i<=n;i++)
            set[i]=i,dep[i]=num[i]=1;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            for(s1=i;set[i]!=i;i=set[i]);
            while(set[s1]!=s1)
                s2=s1,s1=set[s1],set[s2]=i;
            for(s1=j;set[j]!=j;j=set[j]);
            while(set[s1]!=s1)
                s2=s1,s1=set[s1],set[s2]=j;
            if(i==j)continue;
            if(dep[i]<dep[j])
            {
                set[i]=j;
                num[j]+=num[i];
            }
            else
            {
                set[j]=i;
                num[i]+=num[j];
                if(dep[i]==dep[j])
                    dep[i]++;
            }
        }
        for(i=max=0;i<n;i++)
            if(num[i]>max)
                max=num[i];
        printf("%d\n",max);
    }
}
