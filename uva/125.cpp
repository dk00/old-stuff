#include<stdio.h>
main(){
int i,j,k,n,city=0,m[30][30];
while(scanf("%d",&i)!=EOF){
    for(n=j=0;j<30;j++)for(k=0;k<30;k++)m[j][k]=0;
    while(i--){
        scanf("%d %d",&j,&k);
        m[j][k]=1;
        n>?=j;n>?=k;
    }
    for(n++,k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(m[i][k] && m[k][j])
                    if(i==j)m[i][j]=-1;
                    else if(m[i][k]<0 || m[k][j]<0)m[i][j]=-1;
                    else m[i][j]+=m[i][k]*m[k][j];
    for(k=0;k<n;k++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                if(m[i][k] && m[k][j] && (m[i][k]<0 || m[k][j]<0))
                    m[i][j]=-1;
    printf("matrix for city %d\n",city++);
    for(i=0;i<n;i++){
        printf("%d",m[i][0]);
        for(j=1;j<n;j++)
            printf(" %d",m[i][j]);
        puts("");
    }
}
}
