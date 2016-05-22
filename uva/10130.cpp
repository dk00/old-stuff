#include<stdio.h>
int p[1000],w[1000],mw[100],v[30001];
main(){
int i,j,n,m,t,max;
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    for(i=0;i<n;i++)
        scanf("%d %d",&p[i],&w[i]);
    scanf("%d",&m);
    for(i=max=0;i<m;i++)
        scanf("%d",&mw[i]),max>?=mw[i];
    for(j=1,v[0]=0;j<=max;j++)
        v[j]=-1;
    for(i=0;i<n;i++)
        for(j=max-w[i];j>=0;j--)
            if(v[j]>=0)
                v[j+w[i]]>?=(v[j]+p[i]);
    for(j=1;j<=max;j++)
        v[j]>?=v[j-1];
    for(i=max=0;i<m;i++)
        max+=v[mw[i]];
    printf("%d\n",max);
}
}
