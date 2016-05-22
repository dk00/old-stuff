#include<stdio.h>
const int Max=1000;
short int s[Max][Max];
main(){
int i,j,k,n,max;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            scanf("%d",&s[i][j]);
            s[i][j]=!s[i][j];
        }
    max=0;
    for(j=0;j<n && !max;j++)max>?=(s[i][0] || s[0][j]);
    for(i=1;i<n;i++)
        for(j=1;j<n;j++){
            if(!s[i][j])continue;
            s[i][j]=(s[i-1][j-1]<?s[i-1][j]<?s[i][j-1]);
            max>?=++s[i][j];
        }
    printf("%d\n",max);
}
}
