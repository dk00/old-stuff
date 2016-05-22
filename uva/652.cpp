#include<stdio.h>
int u=1,f[10],use[370000],o[10];
class puzzle{
public:
    int x,y,l,p[3][3];
    char c;
    void up(){
        p[x][y]=p[x+++1][y];
        p[x][y]=0;
        c='d';
    }
    void left(){
        p[x][y]=p[x][y+++1];
        p[x][y]=0;
        c='r';
    }
    void right(){
        p[x][y]=p[x][y---1];
        p[x][y]=0;
        c='l';
    }
    void down(){
        p[x][y]=p[x---1][y];
        p[x][y]=0;
        c='u';
    }
    void get(){
        char k[2];
        int i,j;
        for(i=0;i<3;i++)
            for(j=0;j<3;j++){
                scanf("%s",k);
                if(*k=='x')
                    x=i,y=j,p[i][j]=0;
                else p[i][j]=*k-'0';
            }
    }
    int calc(int d){
        if(d>=8)return 0;
        int s=0,i,j=p[d/3][d%3];
        for(i=0;i<j;i++)
            if(o[i])s+=f[8-d];
        o[j]=0;
        s+=calc(d+1);
        o[j]=1;
        return s;
    }
}q[370000],stt;
void path(int p){
    if(p==0)return;
    path(q[p].l);
    putchar(q[p].c);
}
main(){
int i,j,k,t;
f[0]=1;
for(i=1;i<10;i++)
    f[i]=f[i-1]*i,o[i-1]=1;
q[0].p[0][0]=1,q[0].p[0][1]=2,q[0].p[0][2]=3,q[0].p[1][0]=4
,q[0].p[1][1]=5,q[0].p[1][2]=6,q[0].p[2][0]=7,q[0].p[2][1]=2;
q[0].x=2,q[0].y=2;
use[46233]=-1;
for(i=0,j=1;i<j;i++){
    k=q[i].l;
    q[i].l=i;
    if(q[i].x<2){
        q[j]=q[i];
        q[j].up();
        if(!use[q[j].calc(0)])
            use[q[j].calc(0)]=j++;
    }
    if(q[i].y<2){
        q[j]=q[i];
        q[j].left();
        if(!use[q[j].calc(0)])
            use[q[j].calc(0)]=j++;
    }
    if(q[i].x){
        q[j]=q[i];
        q[j].down();
        if(!use[q[j].calc(0)])
            use[q[j].calc(0)]=j++;
    }
    if(q[i].y){
        q[j]=q[i];
        q[j].right();
        if(!use[q[j].calc(0)])
            use[q[j].calc(0)]=j++;
    }
    q[i].l=k;
}
scanf("%d",&t);
while(t--){
    stt.get();
    if(use[stt.calc(0)])path(use[stt.calc(0)]);
    else printf("unsolvable");
    puts("");
}
}
