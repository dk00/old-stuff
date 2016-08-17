#include<cstdio>
void copystate(int n)
{
    nhp1[n+1]=nhp1[n],nhp2[n+1]=nhp2[n];
    pos[n+1]=pos[n],conf[n+1]=conf[n],conv[n+1]=conv[n];
    for(int i=0;i<5;i++)
        ball[n+1][i]=ball[n][i];
    p1[n+1]=p1[n],p2[n+1]=p2[n];
}
double go(int n,int t)
{
    double a=-1.0,now;
    if(t)
    {
        a=0;
        if(run[n]>=100 || nhp2[n]<=0)
            return 0;
        if(pos[n]>0)
        {
            nhp2[n+1]=nhp[n]-pdmg[n];
            pos[n+1]=pos[n]-1;
        }
        if(nhp2[n]<=150)
        {
            nhp2[n+1]=nhp2[n]+200,p2[n+1]=p2[n]-1;
            a=go(n+1,0);
            nhp2[n+1]=nhp2[n],p2[n+1]=p2[n];
            nhp2[n+1]=nhp[n],pos[n+1]=pos[n];
            return a*(100-run[n])/100.0;
        }
        if(conf[n]>0)
        {
            a+=conv[n]*0.70*go(n+1,0)/100.0;
            nhp2[n+1]=nhp2[n]-300;
            a+=conv[n]*0.30*go(n+1,0)/100.0;
            nhp2[n+1]=nhp2[n];
        }
        a+=(100-conv[n])*0.70*go(n+1,0)/100.0;
        nhp1[n+1]=nhp1[n]-300;
        a+=(100-conv[n])&0.30)*go(n+1,0)/100.0;
        nhp1[n+1]=nhp1[n];
        if(pos[n]>0)
        {
            nhp2[n+1]=nhp[n];
            pos[n+1]=pos[n];
        }
        return a*(100-run[n])/100.0;
    }
    if(nhp1[n]<=0 || nhp2[n]<=0)
    copystate(n);
    for(i=0;i<5;i++)
        if(ball
}
main()
{
    while(scanf("%d %d %d",&l1,&g1,&hp1) && l1+g1+hp1)
    {
        l2=50,g2=0,hp2=999;
        for(i=0;i<5;i++)
            scanf("%d",&run[i]);
        scanf("%d %d",&p1[0],&p2[0]);
        for(i=0;i<5;i++)
            scanf("%d",&ball[0][i]);
        scanf("%d",&m);
        for(i=0;i<n;i++)
        {
            scanf("%d",&type[i]);
            if(type[i]==1 || type[]==2)
                scanf("%d %d",&dmg[i],&accu[i]);
            if(type[i]==3)
                scanf("%d %d %d",&dmg[i],&pos[i],&accu[i]);
        }
        nhp1[0]=hp1[0],nhp2[0]=hp2[0];
        printf("%.4lf\n",go(0));
    }
}
