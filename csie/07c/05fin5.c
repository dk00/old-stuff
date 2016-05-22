char w[50][50]={"Sunday","Monday","Tuesday","Wednesday","Thursday","Friday","Saturday"};
int y1=400*365+97,y2=36524,y3=365*4+1,m0[]={-1,31,28,31,30,31,30,31,31,30,31,30,31};
int tonum(int y,int m,int d)
{
    int num=d%7;
    y--;
    num+=y/400*y1+y%400/100*y2+y%400%100/4*y3+y%400%100%4*365;
    y++;
    int i;
    for(i=1;i<m;i++)
        num=(num+m0[i])%7;
    return num%7;
}
main()
{
    int y,m,d,T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d %d",&y,&m,&d);
        if(y<2000)goto no;
        if(m<1 || m>12)goto no;
        m0[2]=28+(y%400==0 ||(y%100 && y%4==0));
        if(d<1 || d>m0[m])goto no;
        puts(w[tonum(y,m,d)]);
        continue;
    no: puts("invalid date");
    }
}
