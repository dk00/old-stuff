#include<map>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=41*14;
int s[N],c[N][N];
main()
{
    int i,j,k,t,n,m,jmp,a,b,ed;
    while(scanf("%d %d %d",&ed,&jmp,&m)==3 && ed){
        map<int,int> H,to;
        H[0]=0;
        H[ed]=1;
        to[0]=s[0]=0;
        to[ed]=s[1]=ed;
        for(i=0,k=2;i<m;i++){
            scanf("%d %d",&a,&b);
            to[a]=b;
            for(j=max(a-jmp,0);j<=min(a+jmp,ed);j++){
                if(j!=a)t=j;
                else t=b;
                if(!H.count(t))H[t]=H.size()-1;
                s[k++]=j;
                if(!to.count(j))to[j]=t;
            }
            s[k++]=b;
            if(!to.count(b))
                to[b]=b;
        }
        sort(s,s+k);
        n=H.size();
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=ed+1;
        for(i=0;i<k;i++){
            if(!H.count(s[i]))continue;
            for(j=1;i+j<k && s[i+j]-s[i]<=jmp;j++){
                if(s[i]==s[i+j])continue;
                c[H[s[i]]][H[to[s[i+j]]]]=1;
            }
/*            if(j==1 && i+j<k && (s[i+j]-s[i]+jmp-1)/jmp<c[H[s[i]]][H[to[s[i+j]]]])
                c[H[s[i]]][H[to[s[i+j]]]]=(s[i+j]-s[i]+jmp-1)/jmp;*/
        }
        for(i=0;i<k;i++){
            if(s[i]!=to[s[i]])continue;
            for(j=1;i+j<k;j++){
                if(s[i+j]!=to[s[i+j]])continue;
                if((s[i+j]-s[i]+jmp-1)/jmp<c[H[s[i]]][H[to[s[i+j]]]])
                    c[H[s[i]]][H[to[s[i+j]]]]=(s[i+j]-s[i]+jmp-1)/jmp;
            }
        }
        for(k=0;k<n;k++)
            for(i=0;i<n;i++)
                for(j=0;j<n;j++)
                    if(c[i][k]+c[k][j]<c[i][j])
                        c[i][j]=c[i][k]+c[k][j];
        printf("%d\n",c[0][1]);
    }
}
