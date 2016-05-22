#include<stdio.h>
main(){
long n,r,link[101][101],p[101],t,s,d,i,j,q1,q2,x[2][10000];
long *s1=x[0],*s2=x[1],*tmp;
while(scanf("%ld %ld",&n,&r)){
    if(!n && !r)break;
    for(i=0;i<=n;i++){
        link[i][i]=p[i]=0;
        for(j=0;j<i;j++)link[i][j]=link[j][i]=0;
    }
    while(r--){
        scanf("%ld %ld",&i,&j);
        scanf("%ld",&link[i][j]);
        link[j][i]=link[i][j];
    }
    scanf("%ld %ld %ld",&t,&s,&d);
    s1[(q1=0)++]=s;
    for(q2=0;q1--;){
        for(i=0;i<=n;i++){
            if(link[s1[q1]][i]>p[i]){
                p[i]=link[s1[q1]][i];
                s2[q2++]=i;
            }
        }
        tmp=s1;s1=s2;s2=tmp;
        q1=q2;
    }
    printf("%ld\n",p[d]/t+(p[d]%t>0));
}
}
