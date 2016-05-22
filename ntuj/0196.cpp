/*
ID: s0000151
PROG: frameup
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int i,j,n,h,r,sx[26],sy[26],ex[26],ey[26],num[26],taken[26];
char map[27][31][31],path[27],resu[10000][27];
int cmp(const void *a,const void *b){
    return -strcmp((char *)a,(char *)b);
}
int fitcheck(int r,int d);
void result(char *res);
void take(int r,int d);
void dfs(int d);
main(){
    int w;
    while(scanf("%d %d",&h,&w)==2 && h+w)
    {
        for(i=0;i<26;i++){
            sx[i]=sy[i]=32,ex[i]=ey[i]=-1;
            taken[i]=1;
        }
        for(i=r=0;i<h;i++){
            scanf("%s",map[0][i]);
            for(j=0;j<w;j++)
                if(map[0][i][j]-'A'>=0){
                    sx[map[0][i][j]-'A']<?=i;
                    sy[map[0][i][j]-'A']<?=j;
                    ex[map[0][i][j]-'A']>?=i;
                    ey[map[0][i][j]-'A']>?=j;
                    taken[map[0][i][j]-'A']=0;
                }
        }
        for(n=26,i=0;i<26;i++){
            n-=taken[i];
            num[i]=(ex[i]-sx[i]+ey[i]-sy[i])*2;
        }
        dfs(0);
        qsort(resu,r,sizeof(resu[0]),cmp);
        while(r--)puts(resu[r]);
    }
}
void take(int r,int d){
    for(i=sx[r];i<=ex[r];i++)
        map[d][i][sy[r]]=map[d][i][ey[r]]='.';
    for(i=sy[r];i<=ey[r];i++)
        map[d][sx[r]][i]=map[d][ex[r]][i]='.';
}
void dfs(int d){
    if(d>=n){
        path[d]='\0';
        result(path);
        return;
    }
    int k,l;
    for(k=0;k<26;k++)
        if(!taken[k] && fitcheck(k,d)==num[k]){
            for(i=0;i<h;i++)strcpy(map[d+1][i],map[d][i]);
            take(k,d+1);
            taken[k]=1;
            path[n-d-1]=k+'A';
            dfs(d+1);
            taken[k]=0;
        }
}
int fitcheck(int r,int d){
    int count=0;
    for(i=sx[r]+1;i<ex[r];i++){
        if(map[d][i][sy[r]]=='.' || map[d][i][sy[r]]=='A'+r)count++;
        if(map[d][i][ey[r]]=='.' || map[d][i][ey[r]]=='A'+r)count++;
    }
    for(i=sy[r]+1;i<ey[r];i++){
        if(map[d][sx[r]][i]=='.' || map[d][sx[r]][i]=='A'+r)count++;
        if(map[d][ex[r]][i]=='.' || map[d][ex[r]][i]=='A'+r)count++;
    }
    if(map[d][sx[r]][sy[r]]=='.' || map[d][sx[r]][sy[r]]=='A'+r)count++;
    if(map[d][sx[r]][ey[r]]=='.' || map[d][sx[r]][ey[r]]=='A'+r)count++;
    if(map[d][ex[r]][sy[r]]=='.' || map[d][ex[r]][sy[r]]=='A'+r)count++;
    if(map[d][ex[r]][ey[r]]=='.' || map[d][ex[r]][ey[r]]=='A'+r)count++;
    return count;
}
void result(char *res){
    strcpy(resu[r++],res);
}
