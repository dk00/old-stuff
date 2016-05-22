#include<cstdio>
#include<cstring>
using namespace std;
const int N=1001;
char tmp[N],s[N][N];
main()
{
    int i,j,k,st,ed,n,m;
    freopen("pa.in","r",stdin);
    while(scanf("%d %d",&n,&m)==2){
        gets(tmp);
        gets(tmp);
        for(i=0;tmp[i];i++);
        if(strlen(tmp)!=n*m){
            puts("<encrypted length error>");
            continue;
        }
        for(i=0;tmp[i];i++)
            if(tmp[i]=='*')tmp[i]=0;
        for(i=0;i<m;i++)
            for(j=0;j<n;j++)
                s[i][j]=0;
        for(i=k=0;i<=n+m-2;i++){
            if(i-n+1>0)st=i-n+1;
            else st=0;
            if(i<m-1)ed=i;
            else ed=m-1;
            if(i%2==0)
                for(j=st;j<=ed;j++)
                    s[i-j][j]=tmp[k++];
            else
                for(j=ed;j>=st;j--)
                    s[i-j][j]=tmp[k++];
        }
        for(j=0;j<m;j++)
            for(i=0;i<n;i++)
                if(s[i][j])
                    printf("%c",s[i][j]);
        puts("");
    }
}
