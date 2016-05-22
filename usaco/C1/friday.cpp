/*
TASK:friday
LANG:C++
*/
#include<cstdio>
int s[7];
main()
{
    freopen("friday.in","r",stdin);
    freopen("friday.out","w",stdout);
    int i,t,yy,mm,dd;
    int nd[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    scanf("%d",&t);
    yy=1900,mm=1,dd=1;
    for(i=1;yy<t+1900;i++)
    {
        if(dd++==13)s[i%7]++;
        if(dd>nd[mm])
            dd=1,mm++;
        if(mm>12)
        {
            mm=1,yy++;
            nd[2]=28;
            if((yy%4==0 && yy%100!=0) || yy%400==0)
                nd[2]=29;
        }
    }
    printf("%d",s[6]);
    for(i=0;i<6;i++)
        printf(" %d",s[i]);
    puts("");
    scanf(" ");
}
