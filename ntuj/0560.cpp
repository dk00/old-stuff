#include<map>
#include<queue>
#include<vector>
#include<cstdio>
#include<cstring>
using namespace std;
struct tran{
    int s[26];
    int& operator[](int x){return s[x];}
};
struct automaton{
    vector<tran> c;
    automaton& operator=(const char t[]){
        c.clear();
        c.resize(strlen(t)+1);
        int i,j;
        for(i=0;t[i];i++)
            c[i][t[i]-'a']=i+1;
        for(j=0;j<26;j++)
            c[i][j]=i;
    }
    automaton& operator+=(automaton& m){
        queue<int> Q;
        map<int,int> H;
        int i,j,k,z,n=c.size();
        for(i=0;i<=n;i++){
            Q.push(i);
            H[i]=i;
        }
        while(!Q.empty()){
            i=Q.front(),Q.pop();
            j=i/n;
            i%=n;
            printf("[%2d, %2d]\n",i,j);
            for(k=0;k<26;k++){
                if(!H.count(z=c[i][k]+n*m.c[j][k])){
                    Q.push(z);
                    H[z]=c[i][k]=c.size();
                    c.resize(c[i][k]+1);
                }
                c[i][k]=H[z];
            }
        }
        printf("%d\n",c.size());
    }
};
main()
{
    int i,n,m;
    while(scanf("%d %d",&n,&m)==2 && n+m){
        automaton s[10];
        for(i=0;i<m;i++){
            char tmp[10];
            scanf("%s",tmp);
            s[i]=tmp;
            if(i)s[i]+=s[0];
        }
    }
}
