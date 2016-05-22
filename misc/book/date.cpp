#include<cstdio>
int tonum(int y,int m,int d)
{
    static int day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    y--;
    int num=y*365+y/4-y/100+y/400;
    y++;
    if((y%4==0 && y%100)|| y%400==0)day[2]=29;
    else day[2]=28;
    for(int i=1;i<m;i++)
        num+=day[i];
    return num+=d;
}
void todate(int num,int &y,int &m,int &d)
{
    static int y400=146097,y100=36524,y4=1461,
        day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};;
    num--;
    y=num/y400*400;
    num%=y400;
    y+=num/y100*100;
    num%=y100;
    y+=num/y4*4;
    num%=y4;
    y+=num/365;
    num%=365;
    for(m=1;num>=day[m];num-=day[m++]);
    d=++num;
}
main()
{
    int i,j,k;
    char tmp[99];
    while(gets(tmp))
    {
        if(sscanf(tmp,"%d %d %d",&i,&j,&k)==3)
            printf("%d\n",tonum(i,j,k));
        else
        {
            todate(i,i,j,k);
            printf("%d/%02d/%02d\n",i,j,k);
        }
    }
}
