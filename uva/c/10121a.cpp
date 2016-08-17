#include<cstdio>
struct pokemon
{
    int hp,pos,pdmg,conf,conv,hyp;
}p1[6],p2[6];
int lv1,g1,maxhp1;
int ball[5],basic[]={5,10,15,10,0};
int m,type[9],dmg[9],acu[9],poi[9];
int lv2,g2,maxhp2,run[5];
double go(int n,int t)
{
    double a=-1,now;
    int _j;
    for(_j=0;ball[_j]==0 && _j<5;_j++);
    if(_j>=5)
        return 0.0;
    if(t==1)
    {
        if(run[n]>=100)
            return 0;
        a=0;
        if(p2[n+1].pos)
        {
            p2[n+1].hp-=p2[n+1].pdmg;
            p2[n+1].pos--;
        }
        if(p2[n+1].hp<=150 && p2[n+1].hyp>0)
        {
            p2[n+1].hyp--;
            p2[n+1].hp+=300;
            p2[n+1].hp<?=maxhp2;
            return (100-run[n])*go(n+1,0)/100.0;
        }
        if(p2[n+1].conf)
        {
            p2[n+1].conf--;
            if(p2[n+1].conv==0)     //it slept
                return (100-run[n])*go(n+1,0)/100.0;
            //attack it self
            p2[n+1].hp-=300;
            a+=p2[n+1].conv/100.0*0.3*go(n+1,0);
            p2[n+1].hp+=300;
        }
        // does not hit
        a+=0.7*go(n+1,0);
        p1[n+1].hp-=300;
        a+=0.3*go(n+1,0);
        p1[n+1].hp+=300;
        return a*(100-run[n])/100.0;
    }
    if(p1[n].hp<=0 || p2[n].hp<=0)
        return 0;
    p1[n+1]=p1[n],p2[n+1]=p2[n];
    int i;for(i=0;i<5;i++)    // use ball i
    {
        if(ball[i]<=0)
            continue;
        ball[i]--;
        double bonus=0.0;
        if(p2[n].hp<=100)bonus+=0.05;
        if(p2[n].hp<=50)bonus+=0.05;
        if(p2[n].conf)bonus+=0.05;
        if(p2[n].pos)bonus+=0.1;
        now=basic[i]/100.0+bonus+(1-basic[i]/100.0-bonus)*go(n,1);
        ball[i]++;
        a>?=now,now=0.0;
    }
    for(i=0;i<m;i++)    // use move i
    {
        // does not hit
        p2[n+1]=p2[n];
        now+=(100-acu[i])*go(n,1)/100.0;
        // hits
        if(type[i]==1 || type[i]==3)
            p2[n+1].hp-=dmg[i];
        if(type[i]==3 && !(p2[n].pos+p2[n].conf))
            p2[n+1].pos=3,p2[n+1].pdmg=poi[i];
        if(type[i]==2 && !(p2[n].pos+p2[n].conf))
            p2[n+1].conf=3,p2[n+1].conv=dmg[i];
        now+=acu[i]*go(n,1)/100.0;
        a>?=now,now=0.0;
    }
    if(p1[n].hyp>0)     //use a hyper potion
    {
        p1[n+1].hp+=300;
        p1[n+1].hp<?=maxhp1;
        p2[n+1]=p2[n];
        now=go(n,1);
        p1[n+1]=p1[n];
        a>?=now;
    }
    return a;
}
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
            else scanf("%d %d %d",&dmg[i],&poi[i],&acu[i]);
        }
        p1[0].hp=maxhp1,p2[0].hp=maxhp2;
        printf("%.4lf\n",go(0,0));
    }
}
