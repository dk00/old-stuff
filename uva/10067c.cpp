#include<stdio.h>
int on[10][10][10][10],w1[10000][4],w2[10000][4];
main(){
int t,n,i,j,k,l,s[4],t1,t2,t3,t4,tmp,x[4];
int a,b,c,d,step;char ss[10];
scanf("%d",&t);
while(t--){
    for(i=0;i<10;i++)for(j=0;j<10;j++)
        for(k=0;k<10;k++)for(l=0;l<10;l++)on[i][j][k][l]=0;
    scanf("%d %d %d %d",&s[0],&s[1],&s[2],&s[3]);
    scanf("%d %d %d %d %d",&t1,&t2,&t3,&t4,&n);
    while(n--){
        for(i=0;i<4;i++)scanf("%d",&x[i]);
        on[x[0]][x[1]][x[2]][x[3]]=1;
    }
    for(i=0;i<4;i++)w1[0][i]=s[i];
    i=1;j=0;step=-1;
    while(!on[t1][t2][t3][t4]){
        if(on[t1][t2][t3][t4] || i<=0)break;
        for(step++,j=0;i--;){
            if(on[w1[i][0]][w1[i][1]][w1[i][2]][w1[i][3]])
                continue;
            on[w1[i][0]][w1[i][1]][w1[i][2]][w1[i][3]]=1;
            for(k=0;k<4;k++){
                for(l=0;l<4;l++)w2[j][l]=w1[i][l];
                w2[j][k]=(w1[i][k]+1)%10;
            if(!on[w2[j][0]][w2[j][1]][w2[j][2]][w2[j][3]])
            {j++;on[w2[j][0]][w2[j][1]][w2[j][2]][w2[j][3]]=1;}
                for(l=0;l<4;l++)w2[j][l]=w1[i][l];
                w2[j][k]=(w1[i][k]+9)%10;
            if(!on[w2[j][0]][w2[j][1]][w2[j][2]][w2[j][3]])
            {j++;on[w2[j][0]][w2[j][1]][w2[j][2]][w2[j][3]]=1;}
            }
        }
        if(on[t1][t2][t3][t4] || j<=0)break;
        for(step++,i=0;j--;){
            if(on[w2[j][0]][w2[j][1]][w2[j][2]][w2[j][3]])
                continue;
            on[w2[j][0]][w2[j][1]][w2[j][2]][w2[j][3]]=1;
            for(k=0;k<4;k++){
                for(l=0;l<4;l++)w1[i][l]=w2[j][l];
                w1[i][k]=(w2[j][k]+1)%10;
            if(!on[w1[i][0]][w1[i][1]][w1[i][2]][w1[i][3]])
            {i++;on[w1[i][0]][w1[i][1]][w1[i][2]][w1[i][3]]=1;}
                for(l=0;l<4;l++)w1[i][l]=w2[j][l];
                w1[i][k]=(w2[j][k]+9)%10;
            if(!on[w1[i][0]][w1[i][1]][w1[i][2]][w1[i][3]])
            {i++;on[w1[i][0]][w1[i][1]][w1[i][2]][w1[i][3]]=1;}
            }
        }
    }
    if(s[0]==t1 && s[1]==t2 && s[2]==t3 && s[3]==t4)
        on[t1][t2][t3][t4]=0;
    if(on[t1][t2][t3][t4])printf("%d\n",step);
    else puts("-1");
}
}
