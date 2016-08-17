#include<conio.h>
#include<stdio.h>
#include<string.h>
class puzzle{
public:
    char c,p[4][5];
    int x,y;
	int operator==(puzzle a){
        if(x!=a.x||y!=a.y||strcmp(p[0],a.p[0])||strcmp(p[1],a.p[1]) ||
        strcmp(p[2],a.p[2]) || strcmp(p[3],a.p[3]))
			return 0;
		return 1;
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
	int get(){
		int i,j,k;
		for(i=0;i<4;i++)
			for(j=p[i][4]=0;j<4;j++){
				if(scanf("%d",&k)==EOF)return 0;
				p[i][j]=k+'A'-1;
				if(!k)
					p[i][j]=' ',x=i,y=j;
			}
		return 1;
    }
	void show(){
		gotoxy(10,10);
		cprintf("%s",p[0]);
		gotoxy(10,11);
		cprintf("%s",p[1]);
		gotoxy(10,12);
		cprintf("%s",p[2]);
		gotoxy(10,13);
		cprintf("%s",p[3]);
    }
}start,end,stat[55];
int j,h,yn;
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
int t;
strcpy(end.p[0],"ABCD");
strcpy(end.p[1],"EFGH");
strcpy(end.p[2],"IJKL");
strcpy(end.p[3],"MNO ");
end.x=3,end.y=3;
char c=0;
while(start.get()){
	clrscr();
	start.show();
    while(c-27){
        if(kbhit()){
            c=getch();
            switch(c){
			case 72:if(start.x<3)start.up();break;
			case 75:if(start.y<3)start.left();break;
			case 77:if(start.y)start.right();break;
			case 80:if(start.x)start.down();break;
            }
            start.show();
        }
    }
}
}
