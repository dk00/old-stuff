#include<stdio.h>
#include<string.h>
class pos{
public:
    int x,y;
    pos operator+(pos s){
        pos temp;
        temp.x=x+s.x;
        temp.y=y+s.y;
        return temp;
    }
    pos operator-=(pos s){
        x-=s.x;
        y-=s.y;
    }
    pos operator=(pos s){
        x=s.x;
        y=s.y;
    }
    int operator==(pos s){
        return(x==s.x && y==s.y);
    }
    int operator<(pos s){
        return(x<s.x && y<s.y);
    }
    int operator<=(pos s){
        return(x<=s.x && y<=s.y);
    }
}base[4][10000],*s1=base[0],*s2=base[1],*b1=base[2],*b2=base[3],*tmp,
tr,lt={-1,-1},rb,sn,bn,dt[]={{-1,0},{0,1},{1,0},{0,-1}};
char map[20][21],dir[]={'n','e','s','w','N','E','S','W'};
int done[20][20][20][20];
main(){
int i,j,k,l,c,r,M=0;
char s,path[10000];
while(scanf("%d %d%c",&r,&c,&s) && r+c){
    rb=(pos){r,c};
    for(i=0;i<r;i++)
        for(j=0;j<c;j++)
            for(k=0;k<r;k++)
                for(l=0;l<c;l++)done[i][j][k][l]=-1;
    for(i=0;i<r;i++){
        gets(map[i]);
        for(j=0;j<c;j++){
            if(map[i][j]=='S'){
				s1[0].x=i;
				s1[0].y=j;
			}
            if(map[i][j]=='B'){
				b1[0].x=i;
				b1[0].y=j;
			}
            if(map[i][j]=='T'){
				tr.x=i;
				tr.y=j;
			}
        }
    }
    done[s1[0].x][s1[0].y][b1[0].x][b1[0].y]=-2;
    for(l=i=1;i;){
        for(j=0;i--;){
            if(b1[i]==tr){
                sn=s1[i];
                bn=b1[i];
                l=0;
                break;
            }
            for(k=0;k<4;k++){
                sn=s1[i]+dt[k];
                if(b1[i]==sn)bn=b1[i]+dt[k];
                else bn=b1[i];
                if(lt<sn && sn<rb && lt<bn && bn<rb &&
                map[sn.x][sn.y]!='#' && map[bn.x][bn.y]!='#' &&
                !(done[sn.x][sn.y][bn.x][bn.y]+1)){
                    done[sn.x][sn.y][bn.x][bn.y]=k+(b1[i]==sn)*4;
                    s2[j]=sn;
                    b2[j++]=bn;
                }
            }
        }
        if(!l)break;
        tmp=s1;s1=s2;s2=tmp;
        tmp=b1;b1=b2;b2=tmp;
        i=j;
    }
    if(M++)puts("");
    printf("Maze #%d\n",M);
    if(l){
		puts("Impossible");
		continue;
	}
    while((k=done[sn.x][sn.y][bn.x][bn.y])>-1){
        path[l++]=dir[k];
        if(k>3)bn-=dt[k%4];
        sn-=dt[k%4];
    }
    path[l]=0;
    while(l--)printf("%c",path[l]);
    puts("");
}
}
