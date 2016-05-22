#include<stdio.h>
main(){
int i,j,k,n,q,m,d,p,set=1,l,num[200];
long long s[10][20];
while(scanf("%d %d",&n,&q) && n+q){
    printf("SET %d:\n",set++);
    for(l=i=0;i<n;i++)scanf("%d",&num[i]);
    while(q--){
        scanf("%d %d",&d,&m);
        for(k=0;k<20;k++)
            for(j=0;j<10;j++)s[j][k]=0;
        for(i=0;i<n;i++){
            p=num[i]%d;
            if(p<0)p=d+p;
            for(j=m;j--;)
                for(k=0;k<d;k++)
                    s[j+1][(k+p)%d]+=s[j][k];
            s[0][p]++;
        }
        printf("QUERY %d: %lld\n",++l,s[m-1][0]);
    }
}
}
