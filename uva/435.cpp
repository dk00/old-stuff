#include<stdio.h>
main(){
int t,i,j,k,n,p,vote[20],pow[20],s[1001];
scanf("%d",&t);
while(t--){
    scanf("%d",&p);
    for(i=n=0;i<p;i++){
        scanf("%d",&vote[i]);
        n+=vote[i];
    }
    for(i=0;i<p;i++){
        for(s[0]=k=1;k<=n;k++)s[k]=0;
        for(j=0;j<p;j++){
            if(i==j)continue;
            for(k=n-vote[j];k>=0;k--)s[k+vote[j]]+=s[k];
        }
        for(pow[i]=0,k=n/2-vote[i]+1;k<=n/2;k++)pow[i]+=s[k];
    }
    for(i=0;i<p;i++)printf("party %d has power index %d\n",i+1,pow[i]);
    puts("");
}
}
