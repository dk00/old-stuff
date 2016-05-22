#include<stdio.h>
#include<string.h>
#include<math.h>
#define BOARDSIZE 6
#define LEVEL 5
#define TESTING 0
#define HASHTABLESIZE 131071 //2^17-1, a prime
#define DIVERGENCE 0.002

struct bd{
	char size[BOARDSIZE][BOARDSIZE];  //int8
};
struct pos{
	char x,y;  //int8
};
struct hashed{
    bd board;
    float score;
    hashed *next;
};

bd board;
bd tempboard[LEVEL];

char balls;  //available balls
char tempballs[LEVEL];

void splash(char x, char y){
	char i;
	char counter,exploded;
	char ui,di,li,ri;  //indexes
	char uin,din,lin,rin;  //new indexes
	pos up[64], down[64], left[64], right[64];
	pos upn[64], downn[64], leftn[64], rightn[64];  //new

	ui=1,di=0,li=0,ri=0;
	up[0].x=x,up[0].y=y+1;
	counter=1;
	exploded=0;
	balls--;

	while(counter>0){
		uin=0, din=0, lin=0, rin=0;
		for(i=0;i<li;i++){
			if(left[i].x>0){
				(left[i].x)--;
				if(board.size[left[i].x][left[i].y]==0)
					leftn[lin++]=left[i];
				else if(board.size[left[i].x][left[i].y]<4){
					(board.size[left[i].x][left[i].y])++;
					counter--;
				}
				else{
					board.size[left[i].x][left[i].y]=0;
					upn[uin++]=left[i];
					downn[din++]=left[i];
					leftn[lin++]=left[i];
					rightn[rin++]=left[i];
					counter+=3;
					exploded++;
				}
			}
			else
				counter--;
		}
		for(i=0;i<di;i++){
			if(down[i].y<BOARDSIZE-1){
				(down[i].y)++;
				if(board.size[down[i].x][down[i].y]==0)
					downn[din++]=down[i];
				else if(board.size[down[i].x][down[i].y]<4){
					(board.size[down[i].x][down[i].y])++;
					counter--;
				}
				else{
					board.size[down[i].x][down[i].y]=0;
					upn[uin++]=down[i];
					downn[din++]=down[i];
					leftn[lin++]=down[i];
					rightn[rin++]=down[i];
					counter+=3;
					exploded++;
				}
			}
			else
				counter--;
		}
		for(i=0;i<ri;i++){
			if(right[i].x<BOARDSIZE-1){
				(right[i].x)++;
				if(board.size[right[i].x][right[i].y]==0)
					rightn[rin++]=right[i];
				else if(board.size[right[i].x][right[i].y]<4){
					(board.size[right[i].x][right[i].y])++;
					counter--;
				}
				else{
					board.size[right[i].x][right[i].y]=0;
					upn[uin++]=right[i];
					downn[din++]=right[i];
					leftn[lin++]=right[i];
					rightn[rin++]=right[i];
					counter+=3;
					exploded++;
				}
			}
			else
				counter--;
		}
		for(i=0;i<ui;i++){
			if(up[i].y>0){
				(up[i].y)--;
				if(board.size[up[i].x][up[i].y]==0)
					upn[uin++]=up[i];
				else if(board.size[up[i].x][up[i].y]<4){
					(board.size[up[i].x][up[i].y])++;
					counter--;
				}
				else{
					board.size[up[i].x][up[i].y]=0;
					upn[uin++]=up[i];
					downn[din++]=up[i];
					leftn[lin++]=up[i];
					rightn[rin++]=up[i];
					counter+=3;
					exploded++;
				}
			}
			else
				counter--;
		}
		for(ui=0;ui<uin;ui++)
			up[ui]=upn[ui];
		for(di=0;di<din;di++)
			down[di]=downn[di];
		for(ri=0;ri<rin;ri++)
			right[ri]=rightn[ri];
		for(li=0;li<lin;li++)
			left[li]=leftn[li];
	}
	balls+=exploded/3;
}

float database[BOARDSIZE][BOARDSIZE][BOARDSIZE][BOARDSIZE][5];
float database2[5][5][5][5][5][5];
float calc(){
	char i,j,tmp;
	float re=balls;
	char markx[BOARDSIZE+2][BOARDSIZE+2],marky[BOARDSIZE+2][BOARDSIZE+2];
	for(i=1;i<=BOARDSIZE;i++){
		marky[i][0]=0;
		tmp=0;
		for(j=1;j<=BOARDSIZE;j++){
			if(board.size[i-1][j-1]>0){
				marky[i][j]=marky[i][tmp]+1;
				tmp=j;
			}
		}
		marky[i][BOARDSIZE+1]=marky[i][tmp]+1;
	}
	for(i=1;i<=BOARDSIZE;i++){
		markx[0][i]=0;
		tmp=0;
		for(j=1;j<=BOARDSIZE;j++){
			if(board.size[j-1][i-1]>0){
				markx[j][i]=markx[tmp][i]+1;
				tmp=j;
			}
		}
		markx[BOARDSIZE+1][i]=markx[tmp][i]+1;
	}
	char check=0,totalweight=0,sumx=0,sumy=0;
	short wsumx=0,wsumy=0;
	for(i=0;i<BOARDSIZE;i++){
		for(j=0;j<BOARDSIZE;j++){
            tmp=board.size[i][j];  //a little faster?
			if(tmp>0){
				re+=database
				[ markx[i+1][j+1]-markx[0][j+1]-1 ]
				[ markx[BOARDSIZE+1][j+1]-markx[i+1][j+1]-1 ]
				[ marky[i+1][j+1]-marky[i+1][0]-1 ]
				[ marky[i+1][BOARDSIZE+1]-marky[i+1][j+1]-1 ]
				[ tmp ];
				check++;
                totalweight+=tmp;
				sumx+=i;
				sumy+=j;
				wsumx+=tmp*i;
				wsumy+=tmp*j;
			}
		}
	}
	float meanx,meany,wmeanx,wmeany;
	meanx=((float)sumx)/check;
	meany=((float)sumy)/check;
	wmeanx=((float)wsumx)/totalweight;
	wmeany=((float)wsumy)/totalweight;
	re-=((wmeanx-meanx)*(wmeanx-meanx)+(wmeany-meany)*(wmeany-meany))*DIVERGENCE*check*check;

	for(i=0;i<BOARDSIZE;i++){
        re-=database2[board.size[i][0]][board.size[i][1]][board.size[i][2]]
        [board.size[i][3]][board.size[i][4]][board.size[i][5]];
    }
	for(i=0;i<BOARDSIZE;i++){
        re-=database2[board.size[0][i]][board.size[1][i]][board.size[2][i]]
        [board.size[3][i]][board.size[4][i]][board.size[5][i]];
    }

	if(check==0)
		re+=20;
	if(check%3>0){
	    re-=0.125;
        if(check%3>1)
	        re-=0.125;
    }
	return re;
}

int hashconstant[BOARDSIZE][BOARDSIZE];
hashed *hash[HASHTABLESIZE];
char level;
char bestx, besty;
float search(){
	level++;
	if(level==LEVEL){
		level--;
		return calc();
	}
	float best=-255,tmp;
	if(level==0){
		bestx=-1;
		besty=-1;
	}

	char i,j;
    int hashcounter=0;
    hashed *hashptr;
	for(i=0;i<BOARDSIZE;i++){
        for(j=0;j<BOARDSIZE;j++)
            hashcounter+=board.size[i][j]*hashconstant[i][j];
    }
    hashcounter%=HASHTABLESIZE;
    for(hashptr=hash[hashcounter];hashptr!=NULL;hashptr=hashptr->next){
        if(memcmp(&(hashptr->board), &board, sizeof(bd))==0){
            level--;
            return hashptr->score+balls;
        }
    }
        
	tempboard[level]=board;
	tempballs[level]=balls;
	for(i=0;i<BOARDSIZE;i++){
		for(j=0;j<BOARDSIZE;j++){
			if(board.size[i][j]>0){
				splash(i,j);
				tmp=search();
				if(tmp>best){
					best=tmp;
					if(level==0){
						bestx=i;
						besty=j;
					}
				}
				board=tempboard[level];
				balls=tempballs[level];
			}
		}
	}
	if(best<-250)
		best=balls+20;
	level--;
	
	hashed **hashptrptr;
	for(hashptrptr=&(hash[hashcounter]);(*hashptrptr)!=NULL;hashptrptr=&((*hashptrptr)->next));
	(*hashptrptr)=new hashed;
	(*hashptrptr)->board=board;
	(*hashptrptr)->score=best-balls;
	(*hashptrptr)->next=NULL;

	return best;
}

int check_for_db2(int a, int b, int c, int d, int e, int f){
    tempboard[0].size[0][0]=a;
    tempboard[0].size[0][1]=b;
    tempboard[0].size[0][2]=c;
    tempboard[0].size[0][3]=d;
    tempboard[0].size[0][4]=e;
    tempboard[0].size[0][5]=f;
    int i,j;
    for(i=1;i<BOARDSIZE;i++){
        for(j=0;j<BOARDSIZE;j++)
            tempboard[0].size[i][j]=0;
    }
    for(i=0;i<BOARDSIZE;i++){
        board=tempboard[0];
        splash(0,i);
        for(j=0;j<BOARDSIZE && board.size[0][j]==0;j++);
        if(j==BOARDSIZE)
            return 1;
    }
    return 0;
}

void splash_for_db2(int a, int b, int c, int d, int e, int f, int x){
    board.size[0][0]=a;
    board.size[0][1]=b;
    board.size[0][2]=c;
    board.size[0][3]=d;
    board.size[0][4]=e;
    board.size[0][5]=f;
    int i,j;
    for(i=1;i<BOARDSIZE;i++){
        for(j=0;j<BOARDSIZE;j++)
            board.size[i][j]=0;
    }
    splash(0,x);
}

void build_database(){
	int a,b,c,d,e,f;
	float constant1[6]={1,1.075,1.096,1.102,1.1035,1.104};
	float constant2=0.03;
	for(a=0;a<BOARDSIZE;a++){
		for(b=0;b<BOARDSIZE;b++){
			for(c=0;c<BOARDSIZE;c++){
				for(d=0;d<BOARDSIZE;d++){
					for(e=1;e<=4;e++){
                        database[a][b][c][d][e]=0;
                        if(a*b>0)
                            database[a][b][c][d][e]++;
                        if(c*d>0)
                            database[a][b][c][d][e]++;
                        
						database[a][b][c][d][e]=
						(e+5)*(1+(e-1)*0.007)*(constant2*database[a][b][c][d][e]
						+constant1[a]+constant1[b]+constant1[c]+constant1[d]-3)
						-10;
					}
				}
			}
		}
	}
	for(e=1;e<=4;e++)
		database[0][0][0][0][e]=e-5;
	for(a=4;a>=0;a--){
    	for(b=4;b>=0;b--){
    	   for(c=4;c>=0;c--){
            	for(d=4;d>=0;d--){
                	for(e=4;e>=0;e--){
                    	for(f=4;f>=0;f--){
                            database2[a][b][c][d][e][f]=127;
                            if(check_for_db2(a,b,c,d,e,f)==1)
                                database2[a][b][c][d][e][f]=0;
                            if(a>0 && a<4 && database2[a][b][c][d][e][f]>1+database2[a+1][b][c][d][e][f])
                                database2[a][b][c][d][e][f]=1+database2[a+1][b][c][d][e][f];
                            if(b>0 && b<4 && database2[a][b][c][d][e][f]>1+database2[a][b+1][c][d][e][f])
                                database2[a][b][c][d][e][f]=1+database2[a][b+1][c][d][e][f];
                            if(c>0 && c<4 && database2[a][b][c][d][e][f]>1+database2[a][b][c+1][d][e][f])
                                database2[a][b][c][d][e][f]=1+database2[a][b][c+1][d][e][f];
                            if(d>0 && d<4 && database2[a][b][c][d][e][f]>1+database2[a][b][c][d+1][e][f])
                                database2[a][b][c][d][e][f]=1+database2[a][b][c][d+1][e][f];
                            if(e>0 && e<4 && database2[a][b][c][d][e][f]>1+database2[a][b][c][d][e+1][f])
                                database2[a][b][c][d][e][f]=1+database2[a][b][c][d][e+1][f];
                            if(f>0 && f<4 && database2[a][b][c][d][e][f]>1+database2[a][b][c][d][e][f+1])
                                database2[a][b][c][d][e][f]=1+database2[a][b][c][d][e][f+1];
                        }
                    }
                }
            }
        }
    }
    database2[0][0][0][0][0][0]=0;

    int constant3[7]={0,4,8,11,14,17,20},counter;
    float constant4=0.055;
    float constant5=0.7;
	float tmp;
	int DP;  //for DP order
	for(DP=1;DP<=BOARDSIZE;DP++){
    	for(a=4;a>=0;a--){
        	for(b=4;b>=0;b--){
        	    for(c=4;c>=0;c--){
                    for(d=4;d>=0;d--){
                    	for(e=4;e>=0;e--){
                        	for(f=4;f>=0;f--){
                                counter=0;
                                if(a>0)counter++;
                                if(b>0)counter++;
                                if(c>0)counter++;
                                if(d>0)counter++;
                                if(e>0)counter++;
                                if(f>0)counter++;

                                if(counter!=DP)
                                    continue;

                                database2[a][b][c][d][e][f]+=a+b+c+d+e+f-constant3[counter];

                                tmp=0;
                                if(a>0 && a<4)
                                    tmp+=pow(database2[a+1][b][c][d][e][f]
                                    -database2[a][b][c][d][e][f],constant5)*constant4;
                                if(b>0 && b<4)
                                    tmp+=pow(database2[a][b+1][c][d][e][f]
                                    -database2[a][b][c][d][e][f],constant5)*constant4;
                                if(c>0 && c<4)
                                    tmp+=pow(database2[a][b][c+1][d][e][f]
                                    -database2[a][b][c][d][e][f],constant5)*constant4;
                                if(d>0 && d<4)
                                    tmp+=pow(database2[a][b][c][d+1][e][f]
                                    -database2[a][b][c][d][e][f],constant5)*constant4;
                                if(e>0 && e<4)
                                    tmp+=pow(database2[a][b][c][d][e+1][f]
                                    -database2[a][b][c][d][e][f],constant5)*constant4;
                                if(f>0 && f<4)
                                    tmp+=pow(database2[a][b][c][d][e][f+1]
                                    -database2[a][b][c][d][e][f],constant5)*constant4;
                                
                                if(a==4){
                                    splash_for_db2(a,b,c,d,e,f,0);
                                    if( database2[board.size[0][0]][board.size[0][1]]
                                    [board.size[0][2]][board.size[0][3]]
                                    [board.size[0][4]][board.size[0][5]]
                                    >database2[a][b][c][d][e][f] )
                                        tmp+=pow(database2[board.size[0][0]][board.size[0][1]]
                                        [board.size[0][2]][board.size[0][3]]
                                        [board.size[0][4]][board.size[0][5]]
                                        -database2[a][b][c][d][e][f],constant5)*constant4;
                                }
                                if(b==4){
                                    splash_for_db2(a,b,c,d,e,f,1);
                                    if( database2[board.size[0][0]][board.size[0][1]]
                                    [board.size[0][2]][board.size[0][3]]
                                    [board.size[0][4]][board.size[0][5]]
                                    >database2[a][b][c][d][e][f] )
                                        tmp+=pow(database2[board.size[0][0]][board.size[0][1]]
                                        [board.size[0][2]][board.size[0][3]]
                                        [board.size[0][4]][board.size[0][5]]
                                        -database2[a][b][c][d][e][f],constant5)*constant4;
                                }
                                if(c==4){
                                    splash_for_db2(a,b,c,d,e,f,2);
                                    if( database2[board.size[0][0]][board.size[0][1]]
                                    [board.size[0][2]][board.size[0][3]]
                                    [board.size[0][4]][board.size[0][5]]
                                    >database2[a][b][c][d][e][f] )
                                        tmp+=pow(database2[board.size[0][0]][board.size[0][1]]
                                        [board.size[0][2]][board.size[0][3]]
                                        [board.size[0][4]][board.size[0][5]]
                                        -database2[a][b][c][d][e][f],constant5)*constant4;
                                }
                                if(d==4){
                                    splash_for_db2(a,b,c,d,e,f,3);
                                    if( database2[board.size[0][0]][board.size[0][1]]
                                    [board.size[0][2]][board.size[0][3]]
                                    [board.size[0][4]][board.size[0][5]]
                                    >database2[a][b][c][d][e][f] )
                                        tmp+=pow(database2[board.size[0][0]][board.size[0][1]]
                                        [board.size[0][2]][board.size[0][3]]
                                        [board.size[0][4]][board.size[0][5]]
                                        -database2[a][b][c][d][e][f],constant5)*constant4;
                                }
                                if(e==4){
                                    splash_for_db2(a,b,c,d,e,f,4);
                                    if( database2[board.size[0][0]][board.size[0][1]]
                                    [board.size[0][2]][board.size[0][3]]
                                    [board.size[0][4]][board.size[0][5]]
                                    >database2[a][b][c][d][e][f] )
                                        tmp+=pow(database2[board.size[0][0]][board.size[0][1]]
                                        [board.size[0][2]][board.size[0][3]]
                                        [board.size[0][4]][board.size[0][5]]
                                        -database2[a][b][c][d][e][f],constant5)*constant4;
                                }
                                if(f==4){
                                    splash_for_db2(a,b,c,d,e,f,5);
                                    if( database2[board.size[0][0]][board.size[0][1]]
                                    [board.size[0][2]][board.size[0][3]]
                                    [board.size[0][4]][board.size[0][5]]
                                    >database2[a][b][c][d][e][f] )
                                        tmp+=pow(database2[board.size[0][0]][board.size[0][1]]
                                        [board.size[0][2]][board.size[0][3]]
                                        [board.size[0][4]][board.size[0][5]]
                                        -database2[a][b][c][d][e][f],constant5)*constant4;
                                }
                                
                                database2[a][b][c][d][e][f]+=tmp;
                            }
                        }
                    }
                }
            }
        }
    }
}

void build_hashconstant(){
    char i,j;
    int tmp=1;
    for(i=0;i<BOARDSIZE;i++){
        for(j=0;j<BOARDSIZE;j++){
            hashconstant[i][j]=tmp;
            tmp=(tmp*5)%HASHTABLESIZE;
        }
    }
}

void freememory(){
    int i;
    hashed *tobefreed, *tmp;
    for(i=0;i<HASHTABLESIZE;i++){
        for(tobefreed=hash[i];tobefreed!=NULL;tobefreed=tmp){
            tmp=tobefreed->next;
            delete(tobefreed);
        }
        hash[i]=NULL;
    }
}

main(){
	build_database();
	build_hashconstant();
	int i,j,tmp;
	float temp;

    for(i=0;i<HASHTABLESIZE;i++)
        hash[i]=NULL;
	
	scanf("%d",&balls);
	while(balls>0){
		for(i=0;i<BOARDSIZE;i++){
			for(j=0;j<BOARDSIZE;j++){
				scanf("%d",&tmp);
				board.size[j][i]=tmp;
			}
		}
		if(TESTING){
            printf("%f\n",calc());
            continue;
        }
		do{
			level=-1,temp=search();
			printf("%d %d score=%f\n",besty,bestx,temp);
			freememory();
			splash(bestx,besty);
			for(i=0;i<BOARDSIZE;i++){
				for(j=0;j<BOARDSIZE;j++){
					tmp=board.size[j][i];
					printf("%d ",tmp);
				}
				printf("\n");
			}
			scanf("%d",&balls);
		}while(balls>0);
		scanf("%d",&balls);
	}
}
