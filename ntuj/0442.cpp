#include<vector>
#include<cstdio>
#include<algorithm>
using namespace std;
struct ivector
{
    int id;
    vector<int> s;
    bool operator<(ivector a)const
    {
        if(s!=a.s)return s<a.s;
        return id<a.id;
    }
    bool operator==(ivector a)const{return s==a.s;}
    int& operator[](int n){return s[n];}
    void clear(){s.clear();}
    void resize(int n,int k){s.resize(n,k);}
    vector<int>::iterator begin(){return s.begin();}
    vector<int>::iterator end(){return s.end();}
};
main()
{
    int i,j,k,n,m;
    vector<ivector> c;
    while(scanf("%d %d",&n,&m)>0)
    {
        c.clear();
        c.resize(n+1);
        c[0].resize(m,0);
        fill(c[0].begin(),c[0].end(),0);
        for(i=1;i<=n;i++)
        {
            scanf("%d",&k);
            c[i].clear();
            c[i].resize(m,0);
            for(j=0;j<m;j++)
                c[i][j]=c[i-1][j]+!!(k&(1<<j));
        }
        for(i=k=0;i<=n;i++)
        {
            c[i].id=i;
            for(j=1;j<m;j++)
                c[i][j-1]-=c[i][j];
            c[i][m-1]=0;
        }
        sort(c.begin(),c.end());
        for(i=0;i<=n;i=j)
            for(j=i+1;c[i]==c[j];j++)
                k>?=c[j].id-c[i].id;
        printf("%d\n",k);
    }
}
