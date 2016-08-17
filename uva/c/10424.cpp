#include<cstdio>
int calc(int n)
{
    if(n>0)
        return n%10+calc(n/10);
    return 0;
}
int num[128];
main()
{
    int i,n1,n2;
    char s1[27],s2[27];
    for(i='A';i<='Z';i++)num[i]=i-'A'+1;
    for(i='a';i<='z';i++)num[i]=i-'a'+1;
    while(gets(s1) && gets(s2))
    {
        for(i=n1=0;s1[i];i++)
            n1+=num[s1[i]];
        while(n1>=10)n1=calc(n1);
        for(i=n2=0;s2[i];i++)
            n2+=num[s2[i]];
        while(n2>=10)n2=calc(n2);
        if(n1<n2)
            printf("%.2lf %%\n",n1*100/(double)n2);
        else
            printf("%.2lf %%\n",n2*100/(double)n1);
    }
}
