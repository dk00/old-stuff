#include<stdio.h>
#define states 7776
int reclev,snum[states+1],state[6],known[26],kncol[26];
int calcstate(){
    int i,a,b,c;
    reclev++;
    a=0;
    for(i=1;i<=5;i++)
        a=a*6+state[i];
    if(snum[a]<0){
        b=0;
        c=known[reclev];
        if(c<0){
            for(i=1;i<=5;i++)
                if(state[i-1]>state[i]){
                    state[i]++;
                    b+=calcstate();
                    state[i]--;
                }
        }
        else
            if(state[c-1]>state[c] && state[c]+1==kncol[reclev]){
                state[c]++;
                b+=calcstate();
                state[c]--;
            }
        snum[a]=b;
    }
    reclev--;
    return snum[a];
}

int numconts(){
    int i;
    state[0]=5;
    for(i=1;i<=5;i++)
        state[i]=0;
    for(i=0;i<states-2;i++)
        snum[i]=-1;
    snum[states-1]=1;
    reclev=0;
    return calcstate();
}
void display(){
int i,j,tbl[6][6];
    for(i=1;i<=5;i++)
        for(j=1;j<=5;j++)
            tbl[i][j]=0;
    for(i=1;i<=25;i++)
        if(known[i]>0)
            tbl[known[i]][kncol[i]]=i;
    for(i=1;i<=5;i++){
        for(j=1;j<=5;j++)
            putchar(tbl[i][j]+64);
        puts("");
    }
}
void clearfixed(){
    for(int i=1;i<=25;i++)known[i]=-1;
}

int wordtonum(char *str){
int i,j,k,cnum,cchr;
    clearfixed();
    cnum=1;
    for(j=1;j<=5;j++)
        for(i=1;i<=5;i++){
            cchr=str[i+(j-1)*5];
            for(k=1;k<cchr-1;k++)
                if(known[k]<0){
                    known[k]=j;
                    kncol[k]=i;
                    cnum+=numconts();
                    known[k]=-1;
                }
            known[cchr]=j;
            kncol[cchr]=i;
        }
    return cnum;
}

char *numtoword(int cnum){
int i,j,k,a;
char str[30];
    clearfixed();
    for(j=1;j<=5;j++)
        for(i=1;i<=5;i++)
            for(k=1;k<=25;k++)
                if(known[k]<0){
                    known[k]=j;
                    kncol[k]=i;
                    str[i+(j-1)*5]=(k+'A'-1);
                    a=numconts();
                    if(cnum-a<1)break;
                    cnum-=a;
                    known[k]=-1;
                }
    str[0]='1';
    return str;
}
main(){
int i,j,k,l,a;
char mode;
char str[30];
    mode=getchar();
    getchar();
    if(mode=='W'){
        scanf("%s",str);
        printf("%d\n",wordtonum(str));
    }
    else{
        scanf("%d",&a);
        puts(numtoword(a)+1);
        display();
    }
    scanf("%d",&a);
}
