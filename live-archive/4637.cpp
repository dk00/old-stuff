#include<map>
#include<queue>
#include<cstdio>
#include<string>
using namespace std;
const string& go(const char *g,const char *a,const char *b)
{
    int i,j;
    static string r;
    r="";
    for(i=0;g[i];i++){
        for(j=0;a[j] && g[i+j]==a[j];j++);
        if(!a[j]){
            i+=j-1;
            r+=b;
        }
        else r.push_back(g[i]);
    }
    return r;
}
char a[19][999],b[19][999],tmp[999];;
main()
{
    int i,n;
    while(scanf("%d",&n)==1 && n){
        for(i=0;i<n;i++)
            scanf("%s %s",a+i,b+i);
        scanf("%s",tmp);
        map<string,int> H;
        queue<string> Q;
        Q.push(tmp);
        scanf("%s",tmp);
        while(!Q.empty()){
            string g=Q.front();
            Q.pop();
            if(g==tmp)break;
            int d=H[g]+1;
            for(i=0;i<n;i++){
                string t=go(g.c_str(),a[i],b[i]);
                if(t.length()>10 || H.count(t))continue;
                H[t]=d;
                Q.push(t);
            }
        }
        if(H.count(tmp))
            printf("%d\n",H[tmp]);
        else
            puts("-1");

    }
}
