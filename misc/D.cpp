#include<set>
#include<string>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=101;
char tmp[999999];
main()
{
    int T,i,j,m,n;
    freopen("pd.in","r",stdin);
    scanf("%d",&T);
    while(T--){
        string w[N];
        set<string> h[N];
        scanf("%d %d%*c",&m,&n);
        gets(tmp);
        char *p=strtok(tmp,",");
        for(i=0;i<m;i++){
            w[i]=p;
            p=strtok(NULL,",");
        }
        for(i=1;i<n;i++){
            gets(tmp);
            for(j=0;tmp[j];j++);
            if(tmp[j-1]==',')
                tmp[j]=' ',tmp[j+1]=0;
            p=strtok(tmp,",");
            for(j=0;j<m;j++){
                if(p[0]!=' ')
                    h[j].insert(p);
                p=strtok(NULL,",");
            }
        }
        for(i=0;i<m;i++)
            printf("%s:%d\n",w[i].c_str(),h[i].size());
    }
}

