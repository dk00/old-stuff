#include<cstdio>
struct pokemon
{
    int hp,pos,pdmg,conf,conv,hyp;
}p1[20],p2[20];
int lv1,g1,maxhp1;
int ball[5],basic[]={5,10,15,10,0};
int m,type[9],dmg[9],acu[9],poi[9];
int lv2,g2,maxhp2,run[5];
double go1(int);
double go2(int);
main()
{
    int i;
    while(scanf("%d %d %d",&lv1,&g1,&maxhp1) && lv1+g1+maxhp1)
    {
        g2=0,lv2=50,maxhp2=999;
        if(lv1>lv2)basic[3]=18;
        else basic[3]=10;
        if(g1!=g2)basic[4]=20;
        else basic[4]=0;
        for(i=0;i<5;i++)
            scanf("%d",&run[i]);
        scanf("%d %d",&p1[0].hyp,&p2[0].hyp);
        for(i=0;i<5;i++)
            scanf("%d",&ball[i]);
        scanf("%d",&m);
        for(i=0;i<m;i++)
        {
            scanf("%d",&type[i]);
            if(type[i]==1 || type[i]==2)
                scanf("%d %d",&dmg[i],&acu[i]);
            else
                scanf("%d %d %d",&dmg[i],&poi[i],&acu[i]);
        }
        p1[0].hp=maxhp1,p2[0].hp=maxhp2;
        printf("%.4lf\n",go1(1));
    }
}
double go1(int n)
{
    p1[n]=p1[n-1],p2[n]=p2[n-1];
    if(p1[n].hp<=0 || p2[n].hp<=0)
        return 0;
    int i;
    double a=-1,now;
    for(i=0;ball[i]==0 && i<5;i++);
    if(i>=5)return 0;
    a=go2(n+1);
    p1[n]=p1[n-1],p2[n]=p2[n-1];
    for(i=0;ball[i]==0;i++);
    for(int j=i+1;j<5;j++)
        if(ball[j] && basic[j]>basic[i])i=j;
    ball[i]--;
    p1[n]=p1[n-1],p2[n]=p2[n-1];
    int bonus=0;
    if(p2[n].hp<=100)bonus+=5;
    if(p2[n].hp<=50)bonus+=5;
    if(p2[n].conf)bonus+=5;
    if(p2[n].pos)bonus+=10;
    now=(basic[i]+bonus)/100.0;
    if(now>=1.0)now=1.0;
    now+=(1.0-now)*go2(n+1);
    a>?=now,now=0;
    ball[i]++;
    for(i=0;i<m;i++)
    {
        p1[n]=p1[n-1],p2[n]=p2[n-1];
        now=(100-acu[i])*go2(n+1)/100.0;
        if(type[i]==1 ||type[i]==3)
            p2[n].hp-=dmg[i];
        if(type[i]==2 && !(p2[n].conf+p2[n].pos))
            p2[n].conf=3,p2[n].conv=dmg[i];
        if(type[i]==3)
            p2[n].pos=3,p2[n].pdmg=poi[i];
        now+=acu[i]*go2(n+1)/100.0;
        a>?=now,now=0;
    }
    p1[n]=p1[n-1],p2[n]=p2[n-1];
    if(p1[n].hp<maxhp1 && p1[n].hyp)
    {
        p1[n].hyp--;
        p1[n].hp+=200;
        p1[n].hp<?=maxhp1;
        now=go2(n+1),a>?=now;
    }
    return a;
}
double go2(int n)
{
    p1[n]=p1[n-1],p2[n]=p2[n-1];
    if(p1[n].hp<=0 || p2[n].hp<=0 || run[(n-1)/2]>=100)
        return 0;
    if(p2[n].pos)
    {
        p2[n].pos--;
        p2[n].hp-=p2[n].pdmg;
    }else p2[n].pdmg=0;
    if(p2[n].hp<=0)
        return 0;
    if(p2[n].hp<=150 && p2[n].hyp)
    {
        p2[n].hyp--;
        p2[n].hp+=200;
        p2[n].hp<?=maxhp2;
        return (100-run[(n-1)/2])*go1(n+1)/100.0;
    }
    double a=0.0;
    if(p2[n].conf)
    {
        p2[n].conf--;
        if(p2[n].conv==0)
            return (100-run[(n-1)/2])*go1(n+1)/100.0;
        p2[n].hp-=300;
        a+=p2[n].conv*0.3*go1(n+1)/100.0;
        p2[n].hp+=300;
    }else p2[n].conv=0;
    a+=0.7*go1(n+1);
    p1[n].hp-=300;
    a+=(100-p2[n].conv)*0.3*go1(n+1)/100.0;
    p1[n].hp+=300;
    return a*(100-run[(n-1)/2])/100.0;
}
