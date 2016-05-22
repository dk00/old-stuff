#include<stdio.h>
int c[10000],p[10000],m1[10000],m2[100000];
main()
{
    int i,j,k,n,max;
    scanf("%d",&n);
    for(i=0;i<n;i++)
        p[i]=i,c[i]=m1[i]=m2[i]=0;
    for(i=0;i<n;i++)
        while(1)
        {
            scanf("%d",&j);
            if(j<0)
                break;
            c[i]++;
            p[j]=i;
        }
    max=0;
    for(i=n-1;i>0;i--)
    {
        k=m1[i]+1;
        if(k>m1[p[i]])
            m2[p[i]]=m1[p[i]],m1[p[i]]=k;
        else if(k>m2[p[i]])
            m2[p[i]]=k;
        if(m1[i]+m2[i]>max)
            max=m1[i]+m2[i];
    }
    if(m1[0]+m2[0]>max)
        max=m1[0]+m2[0];
    printf("%d\n",max);
    scanf(" ");
}
