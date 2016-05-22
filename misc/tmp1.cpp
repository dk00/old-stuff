#include<stdio.h>
int map[101][101],patht[101];
int n,ans;
struct q
{
int pt,lt;//pt=now point,lt=last point
};
int _pathn=0;
int path(int st,int ed)
{
int ptrg,ptrp,i;//ptrg=get,ptrp=put
int used[101];
for(i=1;i<=n;i++)
    used[i]=1;
q queue[1000];
ptrg=0,ptrp=1;
queue[0].pt=st,queue[0].lt=-1;
while(queue[ptrg].pt!=ed && ptrg<ptrp)
   {
   for(i=1;i<=n;i++)
       {
       if(map[queue[ptrg].pt][i] && queue[ptrg].pt==st)
           {
           queue[ptrp].pt=i;
           queue[ptrp++].lt=ptrg;
           used[i]=0;
           }
       else if(map[queue[ptrg].pt][i] && used[i])
           {
           queue[ptrp].pt=i;
           queue[ptrp++].lt=ptrg;
           used[i]=0;
           }
       }
   ptrg++;
   }
if(ptrg>=ptrp)
   return 0;
int now=ptrg,l=0;
while(queue[now].lt!=-1)
   {
   patht[++l]=queue[now].pt;
   now=queue[now].lt;
   }
patht[++l]=st;
return 1;
}
int flow(int st,int ed)
{
int min,i,k;
while(path(st,ed))
   {
   min=2147483647;
   for(i=1;patht[i]!=st;i++)
       if(map[patht[i+1]][patht[i]]<min)
           min=map[patht[i+1]][patht[i]];
   ans+=min;
   for(;i>=2;i--)
       {
       map[patht[i]][patht[i-1]]-=min;
       map[patht[i-1]][patht[i]]+=min;
       }
   }
}
main()
{
int i,j,a,b,c,nedge,st,ed,count=0;
while(scanf("%d",&n) && n)
   {
   ans=0;
   for(i=1;i<=n;i++)
       for(j=1;j<=n;j++)
           map[i][j]=0;
   scanf("%d %d %d",&st,&ed,&nedge);
   for(i=1;i<=nedge;i++)
       {
       scanf("%d %d %d",&a,&b,&c);
       map[a][b]+=c;
       map[b][a]+=c;
       }
   flow(st,ed);
   printf("Network %d\n",++count);
   printf("The bandwidth is %d.\n\n",ans);
   }
}
