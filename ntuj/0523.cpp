#include<cstdio>
const int N=500001;
char s[N],u[N];
int n,p[N],q[N];
main()
{
    int i,j,k,l;
    while(scanf("%s",s)==1){
        for(i=1,j=p[0]=0;s[i];i++){
            while(j>0 && s[i]!=s[j])j=p[j-1];
            if(s[i]==s[j])j++;
            p[i]=j,u[i]=0;
        }
        u[n=i]=1;
        while(j>0)u[j]=1,j=p[j-1];
        for(i=1;s[i];i++)
            if(!u[p[i]])p[i]=p[p[i]-1];
        for(i=1;i<n;i++)
            if(u[i])p[i-1]=i;
        p[n+1]=n;
        for(i=j=l=0,k=1;i<n;i++){
            if(j && i>q[j-1])j=0;
            if(!j && u[i+1])
                k=i+1,q[j++]=i+i+1;
            k>?=i-l;
            if(j>0 && p[i]>=k)
                q[j++]=i+p[l=i];
        }
        while(!u[k] && k<n)k++;
        printf("%d\n",k);
    }
}
