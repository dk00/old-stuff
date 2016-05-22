#include<ctype.h>
#include<stdio.h>
#include<string.h>
int n,use[26],path[2000],mark[2000],num[2000][26];
char phr[2000],dict[2000][25];
int able(int k){
    if(mark[k])return 0;
    for(int i=0;i<26;i++)
        if(use[i]<num[k][i])return 0;
    return 1;
}
void take(int k){
    for(int i=0;i<26;i++)
        use[i]-=num[k][i];
}
void put(int k){
    for(int i=0;i<26;i++)
        use[i]+=num[k][i];
}
int check(int d){
int i;
    for(i=0;i<26;i++)
        if(use[i])return 0;
    printf("%s =",phr);
    for(i=0;i<d;i++)
        printf(" %s",dict[path[i]]);
    puts("");
    return 1;
}
void comb(int d,int i){
    if(check(d))return;
    for(;i<n;i++)
        if(able(i)){
            path[d]=i;
            take(i);
            comb(d+1,i+1);
            put(i);
        }
}
void set(){
int i,j,k;
char c;
    for(i=0;i<n;i++)mark[i]=0;
    for(i=0;phr[i];i=j+1){
        while(!isalpha(phr[i]) && phr[i])i++;
        if(!phr[i])return;
        for(j=i;isalpha(phr[j]);j++);
        c=phr[j];
        phr[j]=0;
        for(k=0;k<n;k++)
            if(!strcmp(phr+i,dict[k])){
                mark[k]=1;
                break;
            }
        phr[j]=c;
    }
}
main(){
int i;
for(n=0;scanf("%s",dict[n]) && dict[n][0]!='#';n++)
    for(i=0;dict[n][i];i++)
        num[n][dict[n][i]-'A']++;
gets(phr);
while(gets(phr) && *phr!='#'){
    for(i=0;i<26;i++)use[i]=0;
    set();
    for(i=0;phr[i];i++)
        if(isalpha(phr[i]))
            use[phr[i]-'A']++;
    comb(0,0);
}
}
