#include<cstdio>
#include<algorithm>
int n,s1[2000000],s2[2000000];
main()
{
    int i,j,k,l;
    for(i=1;i<=1000;i++)
        for(j=1;j<=i;j++,n++)
            s1[n]=i*i*i+j*j*j;
    std::sort(s1,s1+n);
    for(j=n-1,i=n=0;i<j;i++)
        if((!i || s1[i-1]!=s1[i])&& s1[i]==s1[i+1])
            s2[n++]=s1[i];
    while(scanf("%d %d",&i,&j)==2)
    {
        j+=i;
        for(k=l=0;k<n && s2[k]<=j;k++)
            if(i<=s2[k] && s2[k]<=j)
                printf("%d\n",s2[k]),l++;
        if(!l)puts("None");
    }
}
