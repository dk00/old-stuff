/* @JUDGE_ID:  58589NF  116  C++  "Unidirectional TSP"*/
#include<stdio.h>
main(){
int m,n,i,j,next[10][100],min;
long s[10][100],sum,msum;
while(scanf("%d %d",&m,&n)!=EOF){
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            scanf("%ld",&s[i][j]);
            next[i][j]=-1;
        }
    }
    sum=0;
    if(m==1){
        sum=s[0][0];
        printf("1");
        for(j=1;j<n;j++){
            printf(" 1");
            sum+=s[0][j];
        }
        printf("\n%ld\n",sum);
        continue;
    }
    else if(m==2){
        if(s[0][0]<=s[1][0]){ printf("1");sum=s[0][0];}
        else {printf("2");sum=s[1][0];}
        for(j=1;j<n;j++){
            if(s[0][j]<=s[1][j]){
                printf(" 1");
                sum+=s[0][j];
            }
            else{
                printf(" 2");
                sum+=s[1][j];
            }
        }
        printf("\n%ld\n",sum);
        continue;
    }
    for(j=n-1;j>0;j--){
        if(s[0][j]<=s[1][j] && s[0][j]<=s[m-1][j])
            next[0][j-1]=0;
        else if(s[1][j]<=s[m-1][j])
            next[0][j-1]=1;
        else
            next[0][j-1]=m-1;
        s[0][j-1]+=s[next[0][j-1]][j];
        for(i=1;i<m-1;i++){
            if(s[i-1][j]<=s[i][j] && s[i-1][j]<=s[i+1][j])
                next[i][j-1]=i-1;
            else if(s[i][j]<=s[i+1][j])
                next[i][j-1]=i;
            else
                next[i][j-1]=i+1;
            s[i][j-1]+=s[next[i][j-1]][j];
        }
        if(s[0][j]<=s[m-2][j] && s[0][j]<=s[m-1][j])
            next[m-1][j-1]=0;
        else if(s[m-2][j]<=s[m-1][j])
            next[m-1][j-1]=m-2;
        else
            next[m-1][j-1]=m-1;
        s[m-1][j-1]+=s[next[m-1][j-1]][j];
    }
    min=m-1;
    sum=s[m-1][0];
    for(i=m-2;i>=0;i--){
        if(s[i][0]<=sum){
            min=i;
            sum=s[min][0];
        }
    }
    printf("%d",min+1);
    min=next[min][0];
    for(j=1;j<n;j++,min=next[min][j-1]) printf(" %d",min+1);
    printf("\n%ld\n",sum);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
