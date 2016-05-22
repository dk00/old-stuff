#include<stdio.h>
int min,t1,t2,t3,t4,done[10][10][10][10],b1[10000][4],
b2[10000][4],
**w1,**w2,i,j,k,l,;
char s[10];
main(){
w1=b1;w2=b2;
int t,s1,s2,s3,s4,n,x1,x2,x3,x4;
scanf("%d",&t);
while(t--){
    for(min=s1=0;s1<10;s1++)
        for(s2=0;s2<10;s2++)
            for(s3=0;s3<10;s3++)
                for(s4=0;s4<10;s4++)
                    done[s1][s2][s3][s4]=0;
    scanf("%d %d %d %d",&s1,&s2,&s3,&s4);
    scanf("%d %d %d %d %d",&t1,&t2,&t3,&t4,&n);
    while(n--){
        scanf("%d %d %d %d",&x1,&x2,&x3,&x4);
        done[x1][x2][x3][x4]=1;
    }
    w1[0][0]=s1;w1[0][1]=s2;w1[0][2]=s3;w1[0][3]=s4;
    for(i=1,j=0;i;i=j,j=0,min++){
    }
    if(!done[t1][t2][t3][t4])min=-1;
    printf("%d\n",min);
}
}
