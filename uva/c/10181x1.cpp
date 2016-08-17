#include<stdio.h>
#include<string.h>
int s[16];
class puzzle{
public:
    char c,p[4][5];
    int x,y;
    bool operator==(puzzle a){
        if(x!=a.x||y!=a.y||strcmp(p[0],a.p[0])||strcmp(p[1],a.p[1]) ||
        strcmp(p[2],a.p[2]) || strcmp(p[3],a.p[3]))
            return false;
        return true;
    }
    void down(){
        c=p[x][y];
        p[x][y]=p[x-1][y];
        p[x-1][y]=c;
        x--;
    }
    void up(){
        c=p[x][y];
        p[x][y]=p[x+1][y];
        p[x+1][y]=c;
        x++;
    }
    void right(){
        c=p[x][y];
        p[x][y]=p[x][y-1];
        p[x][y-1]=c;
        y--;
    }
    void left(){
        c=p[x][y];
        p[x][y]=p[x][y+1];
        p[x][y+1]=c;
        y++;
    }
    void get(){
        int i,j,k;
        for(i=0;i<4;i++)
            for(j=p[i][4]=0;j<4;j++){
                scanf("%d",&k);
                s[i*4+j]=k;
                p[i][j]=k+'A'-1;
                if(!k)
                    p[i][j]=' ',x=i,y=j;
            }
    }
    void show(){
        puts(p[0]);
        puts(p[1]);
        puts(p[2]);
        puts(p[3]);
    }
}start,end,stat[55];
int j,h,yn,dis[55];
char path[55],ss[55];
void go(int d){
    if(stat[d-1]==end)path[d]=0,yn=1,strcpy(ss,path+1);
    if(d>h || yn)return;
    if(stat[d-1].x)do{
        stat[d]=stat[d-1];
        stat[d].down();
        for(j=d-1;j>=0;j--)
            if(stat[d-1]==stat[d])break;
        path[d]='U';
        go(d+1);
    }while(0);
    if(stat[d-1].y)do{
        stat[d]=stat[d-1];
        stat[d].right();
        for(j=d-1;j>=0;j--)
            if(stat[d-1]==stat[d])break;
        path[d]='L';
        go(d+1);
    }while(0);
    if(stat[d-1].y<3)do{
        stat[d]=stat[d-1];
        stat[d].left();
        for(j=d-1;j>=0;j--)
            if(stat[d-1]==stat[d])break;
        path[d]='R';
        go(d+1);
    }while(0);
    if(stat[d-1].x<3)do{
        stat[d]=stat[d-1];
        stat[d].up();
        for(j=d-1;j>=0;j--)
            if(stat[d-1]==stat[d])break;
        path[d]='D';
        go(d+1);
    }while(0);
}
main(){
int i,j,k,t;
strcpy(end.p[0],"ABCD");
strcpy(end.p[1],"EFGH");
strcpy(end.p[2],"IJKL");
strcpy(end.p[3],"MNO ");
end.x=3,end.y=3;
scanf("%d",&t);
while(t--){
    stat[0].get();
    for(k=i=0;i<16;i++)
        if(s[i])
            for(j=0;j<i;j++)
                if(s[i]<s[j])k++;
    k+=stat[0].x+1;
    if(k&1){
        puts("This puzzle is not solvable.");
        continue;
    }
    for(yn=0,h=1;h<=46 && !yn;h++)
        go(1);
    if(yn)puts(ss);
    else puts("This puzzle is not solvable.");
}
}
