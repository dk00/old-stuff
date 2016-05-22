#include<map>
#include<string>
#include<cstdio>
using namespace std;
struct pa
{
    int a;
    string b;
    bool operator<(pa x)const
    {
        if(a!=x.a)return a>x.a;
        return b<x.b;
    }
}t[999];
int s[999],s1[999],s2[999],d[999];
char tmp[9999];
string name[999];
main()
{
    int i,j,n,m,T,C=1;
    map<string,int> h;
    scanf("%d",&T);
    while(T--)
    {
        h.clear();
        h["Ted"]=0,m=1;
        scanf("%d",&n);
        for(i=0;i<n;i++)
        {
            scanf("%s",tmp);
            if(!h.count(tmp))h[tmp]=m++;
            s1[i]=h[tmp];
            scanf("%s %d",tmp,d+i);
            if(!h.count(tmp))h[tmp]=m++;
            s2[i]=h[tmp];
            name[s2[i]]=tmp;
            s[i]=-1;
        }
        s[0]=100;
        for(j=0;j<n;j++)
            for(i=0;i<n;i++)
                if(s[s1[i]]>=0)
                    s[s2[i]]=s[s1[i]]-d[i];
        for(i=0;i<n;i++)
            t[i]=(pa){s[i+1],name[i+1]};
        sort(t,t+n);
        printf("DATASET %d\n",C++);
        for(i=0;i<n;i++)
            printf("%s %d\n",t[i].b.c_str(),t[i].a);
            
    }
}
