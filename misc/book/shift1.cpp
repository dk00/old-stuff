#include<cstdio>
struct t{
    int h,m,s,ms;
    t &operator+=(t x)
    {
        h+=x.h;
        m+=x.m;
        s+=x.s;
        ms+=x.ms;
        while(ms<0)s--,ms+=100;
        while(ms>=100)ms-=100,s++;
        while(s<0)m--,s+=60;
        while(s>=60)s-=60,m++;
        while(m<0)h--,m+=60;
        while(m>=60)m-=60,h++;
    }
    t operator+(t x)const
    {
        t tmp=*this;
        return tmp+=x;
    }
    const char *tostr()
    {
        static char tmp[99];
        sprintf(tmp,"%d:%02d:%02d.%02d",h,m,s,ms);
        return tmp;
    }
};
char s[9999];
main()
{
    int i;
    t a,b,d={0,0,1,00};
    char const *t;
    while(gets(s))
    {
        if(sscanf(s+12,"%d:%d:%d.%d",&a.h,&a.m,&a.s,&a.ms)!=4)
        {
            puts(s);
            continue;
        }
        a+=d;
        t=a.tostr();
        for(i=0;t[i];i++)
            s[i+12]=t[i];
        sscanf(s+23,"%d:%d:%d.%d",&a.h,&a.m,&a.s,&a.ms);
        a+=d;
        t=a.tostr();
        for(i=0;t[i];i++)
            s[i+23]=t[i];
        puts(s);
    }

}
