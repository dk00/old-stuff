/* @JUDGE_ID:  58589NF  417  c++  "Word Index"*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main(){
long *****code=(long *****)malloc(sizeof(long ****)*23);
long index=1;
int i,j,k,l,m;
code[0]=(long ****)malloc(sizeof(long ***)*27);
code[0][0]=(long ***)malloc(sizeof(long **)*27);
code[0][0][0]=(long **)malloc(sizeof(long *)*27);
code[0][0][0][0]=(long *)malloc(sizeof(long)*26);
for(i=0;i<26;i++)
    code[0][0][0][0][i]=index++;
for(i=1;i<26;i++){
    code[0][0][0][i]=(long *)malloc(sizeof(long)*(26-i));
    for(j=0;i+j<26;j++)
        code[0][0][0][i][j]=index++;
}
for(i=1;i<25;i++){
    code[0][0][i]=(long **)malloc(sizeof(long)*(25-i));
    for(j=1;i+j<26;j++){
        code[0][0][i][j]=(long *)malloc(sizeof(long)*(26-i-j));
        for(k=0;i+j+k<26;k++)
            code[0][0][i][j][k]=index++;
    }
}
for(i=1;i<24;i++){
    code[0][i]=(long ***)malloc(sizeof(long **)*(24-i));
    for(j=1;i+j<25;j++){
        code[0][i][j]=(long **)malloc(sizeof(long *)*(25-i-j));
        for(k=0;i+j+k<26;k++){
            code[0][i][j][k]=(long *)malloc(sizeof(long)*(26-i-j-k));
            for(l=0;i+j+k+l<26;l++)
                code[0][i][j][k][l]=index++;
        }
    }
}
for(i=1;i<=22;i++){
    code[i]=(long ****)malloc(sizeof(long ***)*(23-i));
    for(j=1;i+j<=23;j++){
        code[i][j]=(long ***)malloc(sizeof(long **)*(24-i-j));
        for(k=1;i+j+k<=24;k++){
            code[i][j][k]=(long **)malloc(sizeof(long *)*(25-i-j-k));
            for(l=1;i+j+k+l<=25;l++){
                code[i][j][k][l]=(long *)malloc(sizeof(long)*(26-i-j-k-l));
                for(m=0;i+j+k+l+m<26;m++)
                    code[i][j][k][l][m]=index++;
            }
        }
    }
}
int wlen,wid[5];
char line[6];
while(gets(line)!=NULL){
    wlen=strlen(line);
    k=line[0];
    for(i=1;i<wlen;i++){
        if(line[1]>k){
            printf("0\n");
        }
        else
            k=line[i];
    }
    memset(wid,0,sizeof(int)*5);
    for(i=wlen-1;i>0;i--)
        wid[i]=line[i]-line[i-1];
    printf("%ld\n",code[wid[0]],code[wid[1]],
    code[wid[2]],code[wid[3]],code[wid[4]-1]);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
