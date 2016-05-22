#include<cstdio>
#include<algorithm>
struct pt
{
   int x,y;
   pt operator-(pt a)const{return(pt){x-a.x,y-a.y};}
   int operator*(pt a){return x*a.y-y*a.x;}
}s[2009];
int dis(pt a,pt b)
{
   return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
bool ptcmp(const pt& a,const pt& b)
{
   return(a-s[0])*(b-s[0])<0;
}
int t[2009];
main()
{
   int i,j,k,n,tmp,T;
   scanf("%d",&T),printf("%d\n",T);
   while(T--)
   {
       scanf("%d",&n);
       for(i=j=0;i<n;i++)
       {
           scanf("%d %d",&s[i].y,&s[i].x);
           if(s[i].x<s[j].x ||(s[i].x==s[j].x && s[i].y<s[j].y))j=i;
       }
       s[n-1]=s[0];
       s[2008]=s[0],s[0]=s[j],s[j]=s[2008];
       std::sort(s+1,s+n,ptcmp);
       s[n++]=s[0];
       t[0]=0,t[1]=1;
       for(i=2,k=2;i<n;i++)
       {
           tmp=(s[i%n]-s[t[k-2]])*(s[t[k-1]]-s[t[k-2]]);
           if(tmp==0)
           {
               tmp=dis(s[t[k-2]],s[t[k-1]])-dis(s[t[k-2]],s[i]);
               if(tmp>0)continue;
           }
           while(k>1 && tmp<=0)
               k--,tmp=(s[i%n]-s[t[k-2]])*(s[t[k-1]]-s[t[k-2]]);
           t[k++]=i%n;
       }
       printf("%d\n",k);
       for(i=0;i<k;i++)
           printf("%d %d\n",s[t[i]].y,s[t[i]].x);
       if(T)scanf("%d",&i),puts("-1");
   }
}
