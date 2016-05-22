#include<cstdio>
long long s[45][45];
main(){
    int i,j,k;
    for(i=0;i<45;i++)
        for(j=i+1,s[i][i]=1;;j<45;j++)
            for(k=s[i][j]=0;k<j;k++)
                if(j%(j-k)==0)s[i][j]+=s[i][k];
    while(scanf("%d %d",&i,&j) && i+j)
        printf("%d %d %lld\n",i,j,s[i][j]);
}
