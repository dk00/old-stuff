#include<map>
#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
struct triple{
    int x,y,z;
    bool operator<(triple a)const
    {
        if(x!=a.x)return x<a.x;
        if(y!=a.y)return y<a.y;
        return z<a.z;
    }
    bool operator!=(triple a)const{return x!=a.x || y!=a.y || z!=a.z;}
};
int s[99];
struct pt{
    int t[6];
    pt(){}
    pt(triple a,triple b)
    {
        t[0]=a.x,t[1]=a.y,t[2]=a.z;
        t[3]=b.x,t[4]=b.y,t[5]=b.z;
        sort(t,t+6);
    }
    bool operator<(pt a)const
    {
        for(int i=0;i<6;i++)
            if(t[i]!=a.t[i])return t[i]<a.t[i];
        return 0;
    }
    void print()
    {
        printf("%d %d %d %d %d %d\n",s[t[0]],s[t[1]],s[t[2]],s[t[3]],s[t[4]],s[t[5]]);
    }
}t[999999];
inline bool dist(triple a,triple b)
{
    return a.x!=b.x && a.x!=b.y && a.x!=b.z
    && a.y!=b.x && a.y!=b.y && a.y!=b.z
    && a.z!=b.x && a.z!=b.y && a.z!=b.z;
    
}
main()
{
    int i,j,k,v,n,sum,T;
    while(scanf("%d %d",&n,&T)==2 && n){
        for(i=0;i<n;i++)
            scanf("%d",s+i);
        sort(s,s+i);
        map<int,vector<triple> > H;
        for(i=sum=0;i<n;i++)
            for(j=i+1;j<n;j++)
                for(k=j+1;k<n;k++){
                    triple tmp=(triple){i,j,k};
                    v=s[i]+s[j]+s[k];
                    if(H.count(v)){
                        vector<triple>& s=H[v];
                        for(int i=0;i<s.size();i++)
                            if(dist(s[i],tmp))
                                t[sum++]=pt(s[i],tmp);
                    }
                    H[v].push_back(tmp);
                }
        printf("%d\n",sum);
        if(!T)continue;
        sort(t,t+sum);
        for(i=0;i<sum;i++)
            t[i].print();
    }
}
