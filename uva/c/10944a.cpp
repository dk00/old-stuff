#include<stdio.h>
int dp[32768][15],c[15][15],      //distance
    q[32768],p[32768];
char map[20][21];
int inline abs(int n){return n<0?-n:n;}
main(){
int i,j,k,l,r,n,m,u=0,min,
    sx,sy,nx[20],ny[20];
while(scanf("%d %d%c",&n,&m,*map)!=EOF){
    min=n*m*2;
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
            dp[i][j]=min;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            c[i][j]=(abs(nx[i]-nx[j])>?abs(ny[i]-ny[j]));
    for(i=0,j=0;i<n;i++){
        dp[1<<i][i]=(abs(nx[i]-sx)>?abs(ny[i]-sy));
        q[j++]=1<<i;
    }
    for(i=0;i<j;i++){
        m=q[i];
        for(k=0;k<n;k++){
            if(!(m&(1<<k)))continue;
            for(l=0,r=1;l<n;l++,r<<=1){
                if(m&r)continue;
                dp[m|r][l]<?=(dp[m][k]+c[k][l]);
                if(p[m|r]-u)
                    p[q[j++]=(m|r)]=u;
            }
        }
    }
    for(j=0;j<n;j++)
        min<?=dp[m][j]+(abs(nx[j]-sx)>?abs(ny[j]-sy));
    printf("%d\n",n?min:n);
}
}

