#include<stdio.h>
#define MaxDepth 11
#define MAX 128

short map[8][8];  //0 for empty block, 1,2 for soldiers, 4,5 for kings
//1,4 for player, 2,5 for computer
//player plays top, computer plays bottom
void initial();
void print();
short test(short turn);
short mj_test(short x,short y);

short score[6]={0,-2,2,0,-3,3};
short calc(){
    short sum=0,i,j;
    for(i=0;i<8;i++){
        for(j=(i+1)%2;j<8;j+=2)
            sum+=score[map[i][j]];
    }
    return sum;
}

short guess;
short x1,x2,y1,y2;
short mj_search(short turn, short depth, short x, short y);

short search(short turn, short depth){
    short i,j,temp,temp2,result;
    if(depth==MaxDepth)
        return (calc()<guess);  //provided that MaxDepth is odd
    if(test(turn)){
        for(i=0;i<6;i++){
            for(j=(i+1)%2;j<6;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=2
                && map[i+1][j+1]%3==3-turn && map[i+2][j+2]==0){
                    map[i+2][j+2]=map[i][j];
                    if(i==5 && map[i+2][j+2]==1)
                        map[i+2][j+2]=4;
                    temp=map[i+1][j+1];
                    temp2=map[i][j];
                    map[i+1][j+1]=map[i][j]=0;
                    if(mj_test(i+2,j+2))
                        result=1-mj_search(turn,depth,i+2,j+2);
                    else
                        result=search(3-turn,depth+1);
                    map[i][j]=temp2;
                    map[i+1][j+1]=temp;
                    map[i+2][j+2]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i+2,y2=j+2;
                        return 1;
                    }
                }
            }
        }
        for(i=0;i<6;i++){
            for(j=(i+1)%2+2;j<8;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=2
                && map[i+1][j-1]%3==3-turn && map[i+2][j-2]==0){
                    map[i+2][j-2]=map[i][j];
                    if(i==5 && map[i+2][j-2]==1)
                        map[i+2][j-2]=4;
                    temp=map[i+1][j-1];
                    temp2=map[i][j];
                    map[i+1][j-1]=map[i][j]=0;
                    if(mj_test(i+2,j-2))
                        result=1-mj_search(turn,depth,i+2,j-2);
                    else
                        result=search(3-turn,depth+1);
                    map[i][j]=temp2;
                    map[i+1][j-1]=temp;
                    map[i+2][j-2]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i+2,y2=j-2;
                        return 1;
                    }
                }
            }
        }
        for(i=2;i<8;i++){
            for(j=(i+1)%2+2;j<8;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=1
                && map[i-1][j-1]%3==3-turn && map[i-2][j-2]==0){
                    map[i-2][j-2]=map[i][j];
                    if(i==2 && map[i-2][j-2]==2)
                        map[i-2][j-2]=5;
                    temp=map[i-1][j-1];
                    temp2=map[i][j];
                    map[i-1][j-1]=map[i][j]=0;
                    if(mj_test(i-2,j-2))
                        result=1-mj_search(turn,depth,i-2,j-2);
                    else
                        result=search(3-turn,depth+1);
                    map[i][j]=temp2;
                    map[i-1][j-1]=temp;
                    map[i-2][j-2]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i-2,y2=j-2;
                        return 1;
                    }
                }
            }
        }
        for(i=2;i<8;i++){
            for(j=(i+1)%2;j<6;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=1
                && map[i-1][j+1]%3==3-turn && map[i-2][j+2]==0){
                    map[i-2][j+2]=map[i][j];
                    if(i==2 && map[i-2][j+2]==2)
                        map[i-2][j+2]=5;
                    temp=map[i-1][j+1];
                    temp2=map[i][j];
                    map[i-1][j+1]=map[i][j]=0;
                    if(mj_test(i-2,j+2))
                        result=1-mj_search(turn,depth,i-2,j+2);
                    else
                        result=search(3-turn,depth+1);
                    map[i][j]=temp2;
                    map[i-1][j+1]=temp;
                    map[i-2][j+2]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i-2,y2=j+2;
                        return 1;
                    }
                }
            }
        }
    }
    else{
        for(i=0;i<7;i++){
            for(j=(i+1)%2;j<7;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=2 && map[i+1][j+1]==0){
                    map[i+1][j+1]=map[i][j];
					if(i==6 && map[i][j]==1)
							map[i+1][j+1]=4;
					temp=map[i][j];
                    map[i][j]=0;
                    result=search(3-turn,depth+1);
                    map[i][j]=temp;
                    map[i+1][j+1]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i+1,y2=j+1;
                        return 1;
                    }
                }
            }
        }
        for(i=0;i<7;i++){
            for(j=i%2+1;j<8;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=2 && map[i+1][j-1]==0){
                    map[i+1][j-1]=map[i][j];
					if(i==6 && map[i][j]==1)
							map[i+1][j-1]=4;
					temp=map[i][j];
                    map[i][j]=0;
                    result=search(3-turn,depth+1);
                    map[i][j]=temp;
                    map[i+1][j-1]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i+1,y2=j-1;
                        return 1;
                    }
                }
            }
        }
        for(i=1;i<8;i++){
            for(j=i%2+1;j<8;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=1 && map[i-1][j-1]==0){
                    map[i-1][j-1]=map[i][j];
					if(i==1 && map[i][j]==2)
							map[i-1][j-1]=5;
					temp=map[i][j];
                    map[i][j]=0;
                    result=search(3-turn,depth+1);
                    map[i][j]=temp;
                    map[i-1][j-1]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i-1,y2=j-1;
                        return 1;
                    }
                }
            }
        }
        for(i=1;i<8;i++){
            for(j=(i+1)%2;j<7;j+=2){
                if(map[i][j]%3==turn && map[i][j]!=1 && map[i-1][j+1]==0){
                    map[i-1][j+1]=map[i][j];
					if(i==1 && map[i][j]==2)
							map[i-1][j+1]=5;
					temp=map[i][j];
                    map[i][j]=0;
                    result=search(3-turn,depth+1);
                    map[i][j]=temp;
                    map[i-1][j+1]=0;
                    if(result==0){
                        if(depth==0)
                            x1=i,y1=j,x2=i-1,y2=j+1;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

short mj_search(short turn, short depth, short x, short y){  //mj for multi-jump
	short temp,temp2,result;
	if(x+2<8 && y+2<8 && map[x][y]!=2
	&& map[x+1][y+1]%3==3-turn && map[x+2][y+2]==0){
		map[x+2][y+2]=map[x][y];
		if(x==5 && map[x+2][y+2]==1)
			map[x+2][y+2]=4;
		temp=map[x+1][y+1];
		temp2=map[x][y];
		map[x+1][y+1]=map[x][y]=0;
		if(mj_test(x+2,y+2))
			result=1-mj_search(turn,depth,x+2,y+2);
		else
			result=search(3-turn,depth+1);
		map[x][y]=temp2;
		map[x+1][y+1]=temp;
		map[x+2][y+2]=0;
        if(result==0){
            if(depth==0)
                x1=x,y1=y,x2=x+2,y2=y+2;
            return 1;
        }
	}
	if(x+2<8 && y>=2 && map[x][y]!=2
	&& map[x+1][y-1]%3==3-turn && map[x+2][y-2]==0){
		map[x+2][y-2]=map[x][y];
		if(x==5 && map[x+2][y-2]==1)
			map[x+2][y-2]=4;
		temp=map[x+1][y-1];
		temp2=map[x][y];
		map[x+1][y-1]=map[x][y]=0;
		if(mj_test(x+2,y-2))
			result=1-mj_search(turn,depth,x+2,y-2);
		else
			result=search(3-turn,depth+1);
		map[x][y]=temp2;
		map[x+1][y-1]=temp;
		map[x+2][y-2]=0;
        if(result==0){
            if(depth==0)
                x1=x,y1=y,x2=x+2,y2=y-2;
            return 1;
        }
	}
	if(x>=2 && y>=2 && map[x][y]!=1
	&& map[x-1][y-1]%3==3-turn && map[x-2][y-2]==0){
		map[x-2][y-2]=map[x][y];
		if(x==2 && map[x-2][y-2]==2)
			map[x-2][y-2]=5;
		temp=map[x-1][y-1];
		temp2=map[x][y];
		map[x-1][y-1]=map[x][y]=0;
		if(mj_test(x-2,y-2))
			result=1-mj_search(turn,depth,x-2,y-2);
		else
			result=search(3-turn,depth+1);
		map[x][y]=temp2;
		map[x-1][y-1]=temp;
		map[x-2][y-2]=0;
        if(result==0){
            if(depth==0)
                x1=x,y1=y,x2=x-2,y2=y-2;
            return 1;
        }
	}
	if(x>=2 && y+2<8 && map[x][y]!=1
	&& map[x-1][y+1]%3==3-turn && map[x-2][y+2]==0){
		map[x-2][y+2]=map[x][y];
		if(x==2 && map[x-2][y+2]==2)
			map[x-2][y+2]=5;
		temp=map[x-1][y+1];
		temp2=map[x][y];
		map[x-1][y+1]=map[x][y]=0;
		if(mj_test(x-2,y+2))
			result=1-mj_search(turn,depth,x-2,y+2);
		else
			result=search(3-turn,depth+1);
		map[x][y]=temp2;
		map[x-1][y+1]=temp;
		map[x-2][y+2]=0;
        if(result==0){
            if(depth==0)
                x1=x,y1=y,x2=x-2,y2=y+2;
            return 1;
        }
	}
	return 0;
}

short ub,lb,guessmodifier;
void bsearch(){
    while(1){
		if(lb==-124 && ub==124)
			guess=0;
		else if(lb==-124 && ub==0)
			guess=-4;
		else if(lb==-124 && ub==-4)
			guess=-12;
		else if(lb==-124 && ub==-12)
			guess=-28;
		else if(lb==-124 && ub==-28)
			guess=-60;
		else if(lb==0 && ub==-124)
			guess=4;
		else if(lb==4 && ub==-124)
			guess=12;
		else if(lb==12 && ub==-124)
			guess=28;
		else if(lb==28 && ub==-124)
			guess=60;
		else
			guess=(ub+lb+MAX*2)/2-MAX;
		if(guess==lb)
			return;		
		guess+=guessmodifier;
		if(search(2,0)==1){
			guess-=guessmodifier;
            lb=guess;
		}
		else{
			guess-=guessmodifier;
            ub=guess;
		}
    }
}

void mj_bsearch(short x, short y){
    while(1){
		if(lb==-124 && ub==124)
			guess=0;
		else if(lb==-124 && ub==0)
			guess=-4;
		else if(lb==-124 && ub==-4)
			guess=-12;
		else if(lb==-124 && ub==-12)
			guess=-28;
		else if(lb==-124 && ub==-28)
			guess=-60;
		else if(lb==0 && ub==-124)
			guess=4;
		else if(lb==4 && ub==-124)
			guess=12;
		else if(lb==12 && ub==-124)
			guess=28;
		else if(lb==28 && ub==-124)
			guess=60;
		else
			guess=(ub+lb+MAX*2)/2-MAX;
		if(guess==lb)
			return;
		guess+=guessmodifier;
		if(mj_search(2,0,x,y)==1){
			guess-=guessmodifier;
            lb=guess;
		}
		else{
			guess-=guessmodifier;
            ub=guess;
		}
    }
}

int main(){
    initial();
    short turn=0; //0=computer, 1=player
    while(turn<=0 || turn>2){
        printf("Who first? (1 for player, 2 for computer): ");
        scanf("%d",&turn);
    }
    short te=-1;
    while(1){
        print();
        if(te==-1)
            te=test(turn);
        if(turn==1){
			printf("%d\n",guess);
            if(te==0){
                x1=-1;
				printf("move: ");
                while(x1<0 || 8<=x1 || y1<0 || 8<=y1 || x2<0 || 8<=x2 || y2<0 || 8<=y2
                || map[x2][y2]!=0 || (x1-x2)*(x1-x2)!=1 || (y1-y2)*(y1-y2)!=1
                || map[x1][y1]%3!=1 || (map[x1][y1]==1 && x1>x2) ){
                    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
                }
                map[x2][y2]=map[x1][y1];
                if(x2==7 && map[x2][y2]==1)
                    map[x2][y2]=4;
                map[x1][y1]=0;
            }
            else if(te==1){
                x1=-1;
				printf("jump: ");
                while(x1<0 || 8<=x1 || y1<0 || 8<=y1 || x2<0 || 8<=x2 || y2<0 || 8<=y2
                || map[x2][y2]!=0 || (x1-x2)*(x1-x2)!=4 || (y1-y2)*(y1-y2)!=4
                || map[x1][y1]%3!=1 || (map[x1][y1]==1 && x1>x2)
                || map[(x1+x2)/2][(y1+y2)/2]%3!=2 ){
                    scanf("%d %d %d %d",&x1,&y1,&x2,&y2);
                }
                map[x2][y2]=map[x1][y1];
                if(x2==7 && map[x2][y2]==1)
                    map[x2][y2]=4;
                map[(x1+x2)/2][(y1+y2)/2]=map[x1][y1]=0;
            }
			else{
				x1=x2,y1=y2;
                x2=-1;
				printf("multi-jump: ");
                while(x2<0 || 8<=x2 || y2<0 || 8<=y2 || map[x2][y2]!=0
				|| (x1-x2)*(x1-x2)!=4 || (y1-y2)*(y1-y2)!=4
                || (map[x1][y1]==1 && x1>x2) || map[(x1+x2)/2][(y1+y2)/2]%3!=2 ){
                    scanf("%d %d",&x2,&y2);
                }
                map[x2][y2]=map[x1][y1];
                if(x2==7 && map[x2][y2]==1)
                    map[x2][y2]=4;
                map[(x1+x2)/2][(y1+y2)/2]=map[x1][y1]=0;
			}
        }
        else{
			ub=124,lb=-124;
			guessmodifier=guess;
            if(te==2)
				mj_bsearch(x2,y2);
			else
				bsearch();
            if( (x1-x2)*(y1-y2)==1 ){
                map[x2][y2]=map[x1][y1];
                if(x2==0 && map[x2][y2]==2)
                    map[x2][y2]=5;
                map[x1][y1]=0;
            }
            else{
                map[x2][y2]=map[x1][y1];
                if(x2==0 && map[x2][y2]==2)
                    map[x2][y2]=5;
                map[(x1+x2)/2][(y1+y2)/2]=map[x1][y1]=0;
            }
        }
        if(te==0 || mj_test(x2,y2)==0){
            turn=3-turn;
            te=-1;
        }
		else
			te=2;
    }
    return 0;
}

short test(short turn){
    short i,j;
    for(i=0;i<6;i++){
        for(j=(i+1)%2;j<6;j+=2){
            if(map[i][j]%3==turn && map[i][j]!=2
            && map[i+1][j+1]%3==3-turn && map[i+2][j+2]==0)
                return 1;
        }
    }
    for(i=0;i<6;i++){
        for(j=(i+1)%2+2;j<8;j+=2){
            if(map[i][j]%3==turn && map[i][j]!=2
            && map[i+1][j-1]%3==3-turn && map[i+2][j-2]==0)
                return 1;
        }
    }
    for(i=2;i<8;i++){
        for(j=(i+1)%2+2;j<8;j+=2){
            if(map[i][j]%3==turn && map[i][j]!=1
            && map[i-1][j-1]%3==3-turn && map[i-2][j-2]==0)
                return 1;
        }
    }
    for(i=2;i<8;i++){
        for(j=(i+1)%2;j<6;j+=2){
            if(map[i][j]%3==turn && map[i][j]!=1
            && map[i-1][j+1]%3==3-turn && map[i-2][j+2]==0)
                return 1;
        }
    }
    return 0;
}

short mj_test(short x, short y){
	short turn=map[x][y]%3;
    if(x+2<8 && y+2<8 && map[x][y]!=2 && map[x+1][y+1]%3==3-turn && map[x+2][y+2]==0)
		return 1;
    if(x+2<8 && y>=2  && map[x][y]!=2 && map[x+1][y-1]%3==3-turn && map[x+2][y-2]==0)
		return 1;
    if(x>=2  && y>=2  && map[x][y]!=1 && map[x-1][y-1]%3==3-turn && map[x-2][y-2]==0)
		return 1;
    if(x>=2  && y+2<8 && map[x][y]!=1 && map[x-1][y+1]%3==3-turn && map[x-2][y+2]==0)
		return 1;
    return 0;
}

void initial(){
	guess=0;
    short i,j;
    for(i=0;i<8;i++){
        for(j=0;j<8;j++)
            map[i][j]=0;
    }
    for(i=0;i<3;i++){
        for(j=(i+1)%2;j<8;j+=2)
            map[i][j]=1;
    }
    for(i=5;i<8;i++){
        for(j=(i+1)%2;j<8;j+=2)
            map[i][j]=2;
    }
}

char printboard[7]=" ox#OX";
void print(){
    short i,j;
    puts("/--------\\");
    for(i=0;i<8;i++){
        printf("|");
        for(j=0;j<8;j++)
            printf("%c",printboard[map[i][j]]);
        puts("|");
    }
    puts("\\--------/");
}
