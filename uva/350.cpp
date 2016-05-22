#include<stdio.h>
int app[10000];
main(){
long z,i,m,l,j,n;
for(n=1;1;n++){
    scanf("%ld %ld %ld %ld",&z,&i,&m,&l);
    if(!z && !i && !m && !l) break;
    for(j=0;j<m;j++)app[j]=0;
    app[l]=1;
    while(1){
        l=(z*l+i)%m;
        if(app[l])break;
        app[l]=1;
    }
    for(j=0;;j++){
        l=(z*l+i)%m;
        if(!app[l])break;
        app[l]=0;
    }
    printf("Case %ld: %ld\n",n,j);
}
}
