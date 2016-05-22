#include<cstdio>
#include<algorithm>
struct pt
{
    int x,y;
    pt operator-(pt a)const{return(pt){x-a.x,y-a.y};}
    int operator*(pt a){return x*a.y-y*a.x;}
}s[2007];
int dis(pt a,pt b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}
bool ptcmp(const pt& a,const pt& b){return(a-s[0])*(b-s[0])<0;}
int t[2007];
main()
{
    int i,j,k,n,tmp,T;
    while(scanf("%d",&n)==1 && n)
    {
        for(i=j=0;i<n;i++)
        {
            scanf("%d %d",&s[i].y,&s[i].x);
            if(dis((pt){0,0},s[i])<dis((pt){0,0},s[j]))j=i;
        }
        std::swap(s[0],s[j]);
        std::sort(s+1,s+n,ptcmp);
        t[0]=0,t[1]=1;
        for(i=2,k=2;i<n;i++)
        {
            tmp=(s[i]-s[t[k-2]])*(s[t[k-1]]-s[t[k-2]]);
            if(tmp==0)
            {
                tmp=dis(s[t[k-2]],s[t[k-1]])-dis(s[t[k-2]],s[i]);
                if(tmp>0)continue;
            }
            while(k>1 && tmp<=0)
                k--,tmp=(s[i]-s[t[k-2]])*(s[t[k-1]]-s[t[k-2]]);
            t[k++]=i;
        }
        printf("%d\n",k);
        for(i=0;i<k;i++)
            printf("%d %d\n",s[t[i]].y,s[t[i]].x);
    }
}
