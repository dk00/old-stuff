#include<stdio.h>
int n,s[10],use[10][1000];
int calc(int d,int p,int r,int m){
    if(p+1==n){
		if(s[p]>r)return r+(((s[p]-r)%m)?(s[p]-r)%m:m);
        return s[p];
    }
    if(m==1)return 1;
int i,j,k=s[p],t;
    for(i=1,j=k%m;use[d][j]<0;i++,j=(j*k)%m)
        use[d][j]=i;
    t=calc(d+1,p+1,use[d][j]-1,i-use[d][j]);
    if(!t)t=i-use[d][j];
    for(i=1;t--;i=(i*k)%m);
    if(i>r)
        return r+(((i-r)%m)?(i-r)%m:m);
    return i?i:m;
}
main(){
int i,j,m,C=1;
char c;
while(scanf("%c",&c) && c!='#'){
    ungetc(c,stdin);
    scanf("%d %d",&m,&n);
    for(i=0;i<n;i++){
        scanf("%d",&s[i]);
        for(j=0;j<1000;j++)use[i][j]=-1;
    }
    printf("Case #%d: %d\n",C++,calc(0,0,0,m));
}
}
