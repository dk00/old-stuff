#include<stdio.h>
main(){
scanf("%d",&t);
while(t--){
    scanf("%d",&n);
    sum=s[0][0]=0;
    for(j=1;j<=n;j++)
        s[0][j]=-1;
    for(i=1;scanf("%d",&k) && k;i++){
        for(j=0;j<=n;j++)
            s[i][j]=-1;
        for(j=k;j<=n;j++)
            if(s[i-1][j-k]>=0)
                s[i][j]=j-k,max>?=i;
        for(j=0;j<=n;j++)
            if(s[i-1][j] && sum-j+k<=n)
                s[i][j]=j,max>?=i;
        sum+=k;
    }
}
}
