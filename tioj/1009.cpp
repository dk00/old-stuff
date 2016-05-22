#include<cstdio>
main()
{
    int x,s[3],t[3];
    while(scanf("%d:%d:%d %d:%d:%d",s,s+1,s+2,t,t+1,t+2)>0)
    {
        x=(t[0]-s[0])*3600+(t[1]-s[1])*60+t[2]-s[2];
        if(x<0)x+=86400;
        printf("%02d:%02d:%02d\n",x/3600,x/60%60,x%60);
    }
}
