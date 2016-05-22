/*
ID: s0000151
PROG: char
LANG: C++
*/
#include<stdio.h>
const int p30=120;
const char ah[]=" abcdefghijklmnopqrstuvwxyz";
int font[27][20],data[1200],head[1200],the[1200],dif[27],d1[20],d2[20];
int hdis(int x){
    int dif=0;
    for(;x;x>>=1)dif+=(x&1);
    return dif;
}
int rcgn20(int stt){
int i,j,min;
    for(min=i=0;i<27;i++){
        for(dif[i]=0,j=0;j<20;j++)
            dif[i]+=hdis(data[stt+j]^font[i][j]);
        if(dif[min]>dif[i])min=i;
    }
    if(dif[min]<=p30){
        head[stt+19]=stt;
        the[stt+19]=min;
        return 1;
    }
    return 0;
}
int rcgn19(int stt){
int i,j,min;
    for(min=i=0;i<27;i++){
        for(dif[i]=0,j=0;j<19;j++)
            d1[j]=hdis(data[stt+j]^font[i][j]);
        for(j=0;j<19;j++)
            d2[j]=hdis(data[stt+j]^font[i][j+1]);
        for(j=0;j<19;j++)dif[i]+=d1[j]+d2[j];
        if(dif[min]>dif[i])min=i;
    }
    if(dif[min]<=(p30-6)*2){
        head[stt+18]=stt;
        the[stt+18]=min;
        return 1;
    }
    return 0;
}
int rcgn21(int stt){
int i,j,min;
    for(min=i=0;i<27;i++){
        for(dif[i]=0,j=0;j<20;j++)
            d1[j]=hdis(data[stt+j]^font[i][j]);
        for(j=0;j<20;j++)
            d2[j]=hdis(data[stt+j+1]^font[i][j]);
        for(j=0;j<20;j++)dif[i]+=(d1[j]<?d2[j]);
        if(dif[min]>dif[i])min=i;
    }
    if(dif[min]<=p30){
        head[stt+20]=stt;
        the[stt+20]=min;
        return 1;
    }
    return 0;
}
char go(int p){
    if(head[head[p]]>=0)putchar(go(head[p]));
    return ah[the[p]];
}
main(){
int i,j,k,n,len;
char c;
freopen("font.in","r",stdin);
scanf("%d%c",&n,&c);
for(i=0;i<27;i++)
    for(j=0;j<20;j++){
        for(k=0;scanf("%c",&c) && c!='\n';k=(k<<1)+(c=='1'));
        font[i][j]=k;
    }
freopen("char.in","r",stdin);
freopen("char.out","w",stdout);
scanf("%d%c",&n,&c);
for(i=0;i<n;i++)head[i]=-1;
for(i=0;i<n;i++){
    for(k=0;scanf("%c",&c) && c!='\n';k=(k<<1)+(c=='1'));
    data[i]=k;
}
for(i=0;i+19<=n;i++){
    if(i+20<=n && rcgn20(i))continue;
    if(rcgn19(i))continue;
    if(i+21<=n)rcgn21(i);
}
putchar(go(n-1));
puts("");
}
