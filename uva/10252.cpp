#include<cstdio>
int min(int a,int b){return a<?b;}
main()
{
    int i,j,n1[256],n2[256];
    char s1[1001],s2[1001];
    while(gets(s1) && gets(s2))
    {
        for(i=0;i<256;i++)
            n1[i]=n2[i]=0;
        for(i=0;s1[i];n1[s1[i++]]++);
        for(i=0;s2[i];n2[s2[i++]]++);
        for(i=0;i<256;i++)
            for(j=min(n1[i],n2[i]);j--;)
                putchar(i);
        puts("");
    }
}
