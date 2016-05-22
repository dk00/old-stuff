#include<cstdio>
#include<cstdlib>
int today(int y,int m,int d)
{
    static int day[]={0,31,28,31,30,31,30,31,31,30,31,30,31};
    y--;
    int i,num=y*365+y/4-y/100+y/400;
    y++;
    if((y%4==0 && y%100)|| y%400==0)day[2]=29;
    else day[2]=28;
    for(i=1;i<m;i++)
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
    int i,j,y1,y2,m1,m2,d1,d2,T,C=1;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d/%d/%d %d/%d",&m1,&d1,&y1,&m2,&d2);
        i=today(y1,m1,d1);
        j=today(y2=y1-1,m2,d2);
        if(abs(i-j)>7)
            j=today(y2=y1,m2,d2);
        if(abs(i-j)>7)
            j=today(y2=y1+1,m2,d2);
        if(abs(i-j)>7)
            printf("%d OUT OF RANGE\n",C++);
        else if(i==j)
            printf("%d SAME DAY\n",C++);
        else if(j<i)
            printf("%d %d/%d/%d IS %d DAY%sPRIOR\n",C++,m2,d2,y2,i-j,(i-j>1)?"S ":" ");
        else
            printf("%d %d/%d/%d IS %d DAY%sAFTER\n",C++,m2,d2,y2,j-i,(j-i>1)?"S ":" ");
    }
}
