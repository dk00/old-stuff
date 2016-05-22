#include<cstdio>
#include<cstring>
const int N=20001,L=2010,inf=2000000000;
int n,len[L],c[N],s[2][N];
char p0[N],tmp[L],*p[L];
inline bool eq(char a[],char b[])
{
    for(int i=0;b[i];i++)
        if(b[i]!='?' && a[i]!=b[i])
            return 0;
    return 1;
}
inline int sum(int a,int b){return c[a+b-1]-(a?c[a-1]:0);}
main()
{
    int i,j,m;
    while(scanf("%s %s",tmp,p0)==2){
        p[0]=tmp;
        for(i=0,n=1;tmp[i];i++)
            if(tmp[i]=='*'){
                tmp[i]=0;
                p[n]=tmp+i+1;
                n++;
            }
        for(i=0;i<n;i++)
            len[i]=strlen(p[i]);
        for(i=0;p0[i];i++){
            c[i]=(i?c[i-1]:0)+p0[i]-'a'+1;
            s[0][i]=0;
        }
        m=i;
        s[0][m]=0;
        for(i=0;i<n;i++){
            int *s0=s[i%2],*s1=s[1-i%2];
            for(j=0;j<=m;j++)
                s1[j]=inf;
            for(j=0;j+len[i]<m;j++)
                if(eq(p0+j,p[i]) && s0[j]+sum(j,len[i])<s1[j+len[i]])
                    s1[j+len[i]]=s0[j]+sum(j,len[i]);
            for(j=0;j<m;j++)
                if(s1[j]<inf && s1[j]+p0[j]-'a'+1<s1[j+1])
                    s1[j+1]=s1[j]+p0[j]-'a'+1;
        }
        for(i=1,j=s[n%2][0];i<=m;i++)
            if(s[n%2][i]<j)j=s[n%2][i];
        if(j<1){
            j=p0[0]-'a'+1;
            for(i=0;p0[i];i++)
                if(p0[i]-'a'+1<j)
                    j=p0[i]-'a'+1;
        }
        if(j<inf)printf("%d\n",j);
        else puts("-1");
    }
}
