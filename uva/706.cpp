/*
 -1-
|   |
0   2
|   |
 -3-
|   |
4   6
|   |
 -5-
*/
#include<stdio.h>
char font[11][10];
void show(int size,char *num){
int i,j,k,n;
    if(!size)return;
    for(n=0;num[n];n++)num[n]-='0';
    for(i=0;i<n;i++){
        if(i)putchar(' ');
        putchar(' ');
        for(j=size;j--;)putchar(font[num[i]][1]);
        putchar(' ');
    }
    puts("");
    for(j=size;j--;){
        for(i=0;i<n;i++){
            if(i)putchar(' ');
            putchar(font[num[i]][0]);
            for(k=size;k--;)putchar(' ');
            putchar(font[num[i]][2]);
        }
        puts("");
    }
    for(i=0;i<n;i++){
        if(i)putchar(' ');
        putchar(' ');
        for(j=size;j--;)putchar(font[num[i]][3]);
        putchar(' ');
    }
    puts("");
    for(j=size;j--;){
        for(i=0;i<n;i++){
            if(i)putchar(' ');
            putchar(font[num[i]][4]);
            for(k=size;k--;)putchar(' ');
            putchar(font[num[i]][6]);
        }
        puts("");
    }
    for(i=0;i<n;i++){
        if(i)putchar(' ');
        putchar(' ');
        for(j=size;j--;)putchar(font[num[i]][5]);
        putchar(' ');
    }
    puts("");
    puts("");
}
main(){
int i,j,size;
for(i=0;i<9;i++)
    for(j=0;j<7;j++)font[i][j]=' ';
font[0][0]=font[0][2]=font[0][4]=font[0][6]='|';
font[0][1]=font[0][5]='-';
font[1][2]=font[1][6]='|';
font[2][2]=font[2][4]='|';
font[2][1]=font[2][3]=font[2][5]='-';
font[3][2]=font[3][6]='|';
font[3][1]=font[3][3]=font[3][5]='-';
font[4][0]=font[4][2]=font[4][6]='|';
font[4][3]='-';
font[5][0]=font[5][6]='|';
font[5][1]=font[5][3]=font[5][5]='-';
font[6][0]=font[6][4]=font[6][6]='|';
font[6][1]=font[6][3]=font[6][5]='-';
font[7][2]=font[7][6]=font[8][0]='|';
font[7][1]='-';
font[8][2]=font[8][4]=font[8][6]='|';
font[8][1]=font[8][3]=font[8][5]='-';
font[9][0]=font[9][2]=font[9][6]='|';
font[9][1]=font[9][3]='-';
char num[2000];
while(scanf("%d %s",&size,num)!=EOF && size+num)
    show(size,num);
}
