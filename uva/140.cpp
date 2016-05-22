#include<stdio.h>
#include<stdlib.h>
int min,use[26],num[26],path[10],best[10],link[26][26];
int calc(){
int i,j,max=0;
    for(i=0;i<26;i++)
        for(j=0;j<26;j++)
            if(link[i][j])max>?=abs(num[i]-num[j]);
    return max;
}
void go(int n,int d){
    if(n<=0){
        if(calc()<min){
            min=calc();
            for(n=0;n<d;n++)
                best[n]=path[n];
        }
        return;
    }
    for(int i=0;i<26;i++)
        if(!num[i] && use[i]){
            num[i]=n;
            path[d]=i;
            go(n-1,d+1);
            num[i]=0;
        }
}
main(){
int i,j,n;
char c;
while((c=getchar())-'#'){
    ungetc(c,stdin);
    for(n=i=0;i<26;i++){
        use[i]=0;
        for(j=0;j<26;j++)link[i][j]=0;
    }
    while((c=getchar())-'\n'){
        ungetc(c,stdin);
        scanf("%c:",&i);
        i-='A';
        if(!use[i]){
            use[i]=1;
            n++;
        }
        while((c=getchar())!=';' && c!='\n'){
            c-='A';
            link[i][c]=link[c][i]=1;
            if(!use[c]){
                use[c]=1;
                n++;
            }
        }
        if(c=='\n')break;
    }
    min=n+1;
    go(n,0);
    for(i=0;i<n;i++)printf("%c ",best[i]+'A');
    printf("-> %d\n",min);
}
}
