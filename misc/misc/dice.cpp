#include<cstdio>
int s[10000];
main()
{
    int i,j,k;
    for(i=0;i<6;i++)
        for(j=0;j<6;j++)
            for(k=0;k<6;k++)
                s[i+j+k+3]++;
    for(i=3;i<=18;i++)
        printf("%lf\n",s[i]/216.0);
    puts("");
    scanf(" ");
}
