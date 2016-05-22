#include<stdio.h>
int numget(int s[]){
    int n,c;
    c=getchar();
    for(n=0;c!='\n';n++){
        while((c<'0' || c>'9') && c!='\n')c=getchar();
        if(c=='\n')break;
        ungetc(c,stdin);
        scanf("%d%c",&s[n],&c);
    }
    return n;
}
const int inf=2000000000;
int n,p,min,max,sum,use,u,
    path[100],best[100],t[100],dg[100],st[100],c[100][100];
int h()
{
    return(sum-p+use%p)/p;
}
bool go(int d,int u,int time)
{
    /*
    int tmp=time+h();
    if(tmp>max)
    {
        next<?=tmp;
        return 0;
    }
    */
    if(d>=n)
    {
        if(u<min)
        {
            min=u;
            for(d=0;d<n;d++)
                best[d]=path[d];
        }
        return 1;
    }
    if(u+h()>=min)return 0;
    int tmp=inf;
    for(int i=0;i<n;i++)
        if(!dg[i])tmp<?=st[i];
    u>?=tmp;
    for(int i=0;i<n;i++)
    {
        if(dg[i] || st[i]>u)continue;
        dg[i]--;
        path[i]=u;
        sum-=t[i],time+=t[i],u=time/p;
        for(int j=0;j<n;j++)
            if(c[i][j])if(dg[j]--==1)
                st[j]=u+(time%p>0);
        go(d+1,u,time);
        for(int j=0;j<n;j++)
            if(c[i][j])dg[j]++,st[j]=inf;
        time-=t[i];
        dg[i]++;
    }
    return 0;
}
main(){
    int i,j,k,last,T,tmp[1000];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d %d",&p,&n);
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=0;
        for(i=sum=0;i<n;i++)
        {
            scanf("%d",&t[i]);
            sum+=t[i];
            dg[i]=numget(tmp);
            for(j=0;j<dg[i];j++)
                c[tmp[j]-1][i]=1;
        }
        min=inf;
        max=h();
        use=u=0,go(0,0,0);
        for(i=0;i<n;i++)
            printf("%d ",best[i]);
        puts("");
        for(i=k=0;i<=min;)
        {
            for(j=0;j<n;j++)
                if(t[j]>0 && best[j]==i)
                    break;
            if(j>=n)
            {
                i++,k=0,puts("");
                continue;
            }
            while(t[j]--)
            {
                if(k>=p)i++,k=0,puts("");
                k++,printf("%3d",j+1);
            }
        }
    }
}
