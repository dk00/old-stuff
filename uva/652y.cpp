#include<stdio.h>
int f[10],u[10],use[370000];
class puzzle{
public:
    int x,y,l,p[3][3];
    char c;
    void up(){
        p[x][y]=p[x+++1][y];
        p[x][y]=0;
    }
    void left(){
        p[x][y]=p[x][y+++1];
        p[x][y]=0;
    }
    void down(){
        p[x][y]=p[x---1][y];
        p[x][y]=0;
    }
    void right(){
        p[x][y]=p[x][y---1];
        p[x][y]=0;
    }
    void get(){
        int i,j;
        char s[2];
        for(i=0;i<3;i++)
            for(j=0;j<3;j++){
                scanf("%s",s);
                p[i][j]=*s-'0';
                if(*s=='0')
                    x=i,y=j;
            }
    }
    int num(int d){
        if(d>8)return 0;
        int i,j=p[d/3][d%3],s=0;
        for(i=0;i<j;i++)
            if(!u[i])s+=f[8-d];
        u[j]=1;
        s+=num(d+1);
        u[j]=0;
        return s;
    }
}stt,q[370000];
void path(int p){
    if(!p)return;
    path(q[p].l);
    putchar(q[p].c);
}
main(){
int i,j,k,t;
f[0]=1;
for(i=1;i<10;i++)f[i]=f[i-1]*i;
q[0].p[0][0]=0,q[0].p[0][1]=1,q[0].p[0][2]=2,q[0].p[1][0]=3,
q[0].p[1][1]=4,q[0].p[1][2]=5,q[0].p[2][0]=6,q[0].p[2][1]=7;
q[0].x=2,q[0].y=2;
for(i=0,j=1;i<j;i++){
    k=q[i].l;
    q[i].l=i;
    if(q[i].x<2){
        q[j]=q[i];
        q[j].up();
        if(!use[q[j].num(0)]){
            use[q[j].num(0)]=j;
            j++;
        }
    }
    if(q[i].y<2){
        q[j]=q[i];
        q[j].left();
        if(!use[q[j].num(0)]){
            use[q[j].num(0)]=j;
            j++;
        }
    }
    if(q[i].x){
        q[j]=q[i];
        q[j].down();
        if(!use[q[j].num(0)]){
            use[q[j].num(0)]=j;
            j++;
        }
    }
    if(q[i].y){
        q[j]=q[i];
        q[j].right();
        if(!use[q[j].num(0)]){
            use[q[j].num(0)]=j;
            j++;
        }
    }
    q[i].l=k;
}
scanf("%d",&t);
while(t--){
    stt.get();
    i=stt.num(0);
    if(use[i])path(use[i]);
    else printf("unsolvable");
    puts("");
}
}
