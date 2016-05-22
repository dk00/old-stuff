#include<stdio.h>
int ht[5],map[5][5],num[7777],n6[]={1,6,36,216,1296};
int calc(){
    int i,stat,sum=0;
    for(i=stat=0;i<5;i++)stat+=n6[i]*ht[i];
    if(num[stat])return num[stat];
    for(i=0;i<5;i++)
        if(ht[i]<5 && (!i || ht[i-1]>=ht[i]+1)){
            ht[i]++;
            sum+=calc();
            ht[i]--;
        }
    num[stat]=sum;
    return num[stat];
}
void calc(int n){
    int i,j,stat,sum=0;
    for(j=0;j<=5;j++)ht[j]=0;
    for(stat=0,i=1;i<=25;i++){
        for(j=0;j<5;j++)
            if(ht[j]<5 && (!j || ht[j-1]>=ht[j]+1)){
                if(sum+num[stat+n6[j]]>=n)
                    break;
                sum+=num[stat+n6[j]];
            }
        map[ht[j]++][j]=i;
        stat+=n6[j];
    }
}
int calc(char *s){
    int i,j,sum,stat;
    for(i=0;i<25;i++)map[i%5][i/5]=s[i]-64;
    for(j=0;j<=5;j++)ht[j]=0;
    for(sum=stat=0,i=1;i<=25;i++){
        for(j=0;j<5;j++)
            if(ht[j]<5 && (!j || ht[j-1]>ht[j])){
                if(map[ht[j]][j]==i)
                    break;
                sum+=num[stat+n6[j]];
            }
        s[ht[j]+++j*5]+=32;
        stat+=n6[j];
    }
    return sum+1;
}
inline void show(){
int i,j;
    for(i=0;i<5;i++){
        for(j=0;j<5;j++)
            putchar(map[j][i]+64);
        puts("");
    }
    puts("");
}
main(){
int i,n;
char s[27];
for(i=0;i<7775;i++)num[i]=0;
num[7775]=1;
printf("%d\n",calc());
scanf("%d",&n);
calc(n);
show();
scanf("%s",s);
printf("%d\n",calc(s));
scanf("%d",&n);
}
