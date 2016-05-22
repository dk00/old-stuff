#include<stdio.h>
int map[100][100],get[100][100];
main(){
int i,j,k,n,l,r,t,max;
scanf("%d",&t);
while(t--){
    scanf("%d %d",&n,&k);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++){
            scanf("%d",&map[i][j]);
            get[i][j]=0;
        }
    get[0][0]=1;
    for(l=1;l<=100;l++)
        for(i=0;i<n;i++)
            for(j=0;j<n;j++){
                if(map[i][j]!=l || !get[i][j])continue;
                for(r=1;r<=k;r++){
                    if(i-r>=0 && map[i-r][j]>l)
                        get[i-r][j]>?=(l+get[i][j]);
                    if(j-r>=0 && map[i][j-r]>l)
                        get[i][j-r]>?=(l+get[i][j]);
                    if(i+r<n && map[i+r][j]>l)
                        get[i+r][j]>?=(l+get[i][j]);
                    if(j+r<n && map[i][j+r]>l)
                        get[i][j+r]>?=(l+get[i][j]);
                }
            }
    for(max=i=0;i<n;i++)
        for(j=0;j<n;j++)max>?=(get[i][j]+map[i][j]);
    printf("%d\n",max-1);
    if(t)puts("");
}
}
