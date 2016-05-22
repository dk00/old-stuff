/* @JUDGE_ID:  58589NF  417  c++  "Word Index"*/
#include<stdio.h>
#include<stdlib.h>
int main(){
int d1=0,d2=0,d3=0,d4=0,d5=1;
long *****code,i=1;
code=(long *****)malloc(sizeof(long ****)*23);
code[0]=(long ****)malloc(sizeof(long ***)*24);
code[0][0]=(long ***)malloc(sizeof(long **)*25);
code[0][0][0]=(long **)malloc(sizeof(long *)*26);
code[0][0][0][0]=(long *)malloc(sizeof(long )*27);
while(d1<23){
    code[d1][d2][d3][d4][d5++]=i++;
    if(d1+d2+d3+d4+d5>26){
        d5=1;
        d4++;
        if(d1+d2+d3+d4>25){
            d4=1;
            d3++;
            if(d1+d2+d3>24){
                d3=1;
                d2++;
                if(d1+d2>23){
                    d2=1;
                    d1++;
                    if(d1>22)
                        break;
                    code[d1]=(long ****)malloc(sizeof(long ***)*24-d1);
                }
                code[d1][d2]=(long ***)malloc(sizeof(long **)*25-d1-d2);
            }
            code[d1][d2][d3]=(long **)malloc(sizeof(long *)*26-d1-d2-d3);
        }
        code[d1][d2][d3][d4]=(long *)malloc(sizeof(long)*27-d1-d2-d3-d4);
    }
}
int *d[6]={NULL,&d1,&d2,&d3,&d4,&d5};
char line[6];
while(gets(line)!=NULL){
    d1=0;
    d2=0;
    d3=0;
    d4=0;
    d5=0;
    switch(strlen(line)){
        case 1:
            d5=line[0]-'a'+1;
            break;
        case 2:
            d5=line[1]-'a'+1;
            d4=line[0]-'a'+1;
            d5-=d4;
            break;
        case 3:
            d5=line[2]-'a'+1;
            d4=line[1]-'a'+1;
            d5-=d4;
            d3=line[0]-'a'+1;
            d4-=d3;
            break;
        case 4:
            d5=line[3]-'a'+1;
            d4=line[2]-'a'+1;
            d5-=d4;
            d3=line[1]-'a'+1;
            d4-=d3;
            d2=line[0]-'a'+1;
            d3-=d2;
            break;
        case 5:
            d5=line[4]-'a'+1;
            d4=line[3]-'a'+1;
            d5-=d4;
            d3=line[2]-'a'+1;
            d4-=d3;
            d2=line[1]-'a'+1;
            d3-=d2;
            d1=line[0]-'a'+1;
            d2-=d1;
            break;
    }
    if(d1>0 && d2<=0){
        printf("0\n");
        continue;
    }
    else if(d2>0 && d3<=0){
        printf("0\n");
        continue;
    }
    else if(d3>0 && d4<=0){
        printf("0\n");
        continue;
    }
    else if(d4>0 && d5<=0){
        printf("0\n");
        continue;
    }
    printf("%ld\n",code[d1][d2][d3][d4][d5]);
}
return 0;
}
/*@END_OF_SOURCE_CODE*/
