#include<stdio.h>
int s[25][25];
main(){
int i,j,k,p,n,t,sum,max;
char line[25];
scanf("%d",&t);
while(t--){
    scanf("%s",line);
    for(n=0;line[n];n++){
        line[n]-='0';
        if(!line[n])s[0][n]=-1000;
        else s[0][n]=1;
    }
    for(i=1;i<n;i++){
        scanf("%s",line);
        for(j=0;j<n;j++){
            line[j]-='0';
            if(!line[j])s[i][j]=-1000;
            else s[i][j]=1;
            s[i][j]+=s[i-1][j];
        }
    }
    max=0;
    for(i=0;i<n;i++)
        for(j=i;j<n;j++)
            for(k=sum=0;k<n;k++){
                p=s[j][k]-(i?s[i-1][k]:0);
                if(sum+p<0)sum=0;
                else sum+=p;
                max>?=sum;
            }
    printf("%d\n",max);
    if(t)puts("");
}
}
