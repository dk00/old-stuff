#include<cstdio>
#include<algorithm>
struct pt
{
    int x,y;
    bool operator<(const pt a)const{return(x<a.x ||(x==a.x && y>a.y));};
}s[128];
main()
{
    int i,C=0;
    char tmp[1001];
    while(gets(tmp))
    {
        for(i=0;i<128;i++)s[i]=(pt){0,i};
        for(i=0;tmp[i];i++)
            s[tmp[i]].x++;
        std::sort(s,s+128);
        if(C++)puts("");
        for(i=0;i<128;i++)
            if(s[i].x)
                printf("%d %d\n",s[i].y,s[i].x);
    }
}
