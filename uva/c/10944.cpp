#include<stdio.h>
int dp[32768][15],c[15][15],
    p[32768],q[32768];
char map[21][21];
int inline abs(int n){return n<0?-n:n;}
main(){
int i,j,k,l,n,m,r,u=0,min,
    sx,sy,nx[16],ny[16];
while(scanf("%d %d%c",&n,&m,*map)!=EOF){
    min=2147483647;
    for(i=k=0,u++;i<n;i++){
        gets(map[i]);
        for(j=0;j<m;j++){
            if(map[i][j]=='L')
                sx=i,sy=j;
            else if(map[i][j]=='#')
                nx[k]=i,ny[k++]=j;
        }
    }
    n=k;
    for(i=0,m=1;i<n;i++,m<<=1);
    for(i=0;i<=m;i++)
        for(j=0;j<n;j++)
            dp[i][j]=2147483647;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=(abs(nx[i]-nx[j])>?abs(ny[i]-ny[j]));
    for(i=j=0,r=1;i<n;i++,r<<=1){
        dp[0][i]=(abs(sx-nx[i])>?abs(sy-ny[i]));
        p[q[j++]=r]=1;
    }
    for(i=0;i<j;i++){
        m=q[i];
        for(k=0;k<n;k++){
            if(m&(1<<k))continue;
            else if(p[m|(1<<k)]-u)
                p[q[j++]=m|(1<<k)]=u;
            for(l=0,r=1;l<n;l++,r<<=1){
                if(!(m&r))continue;
                dp[m][k]<?=(dp[m&~r][l]+c[k][l]);
            }
        }
    }
    for(k=0,r=1;k<n;k++,r<<=1)
        min<?=((abs(sx-nx[k])>?abs(sy-ny[k]))+dp[m&~r][k]);
    printf("%d\n",n?min:n);
}
}
