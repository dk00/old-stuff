#include<stdio.h>
#include<string.h>
const char name[9][20]={
    "highest-card",
    "one-pair",
    "two-pairs",
    "three-of-a-kind",
    "straight",
    "flush",
    "full-house",
    "four-of-a-kind",
    "straight-flush",
};
int best,use[5]={1,1,1,1,1},num[256];
char deck[5][3];
class Hand{
public:
    char card[5][3];
    void sort(){
        int i,j;
        char tmp[3];
        for(i=0;i<5;i++)
            for(j=1;j<5;j++)
                if(num[card[j-1][0]]>num[card[j][0]]){
                    strcpy(tmp,card[j-1]);
                    strcpy(card[j-1],card[j]);
                    strcpy(card[j],tmp);
                }
    }
    void change(int p,char *s){
        char tmp[3];
        strcpy(tmp,card[p]);
        strcpy(card[p],s);
        strcpy(s,tmp);
    }
    int straight_flush(){
        return(straight() && flush());
    }
    int four_of_a_kind(){
        int i;
        for(i=1;i<5 && card[i][0]==card[i-1][0];i++);
        if(i==4)return 1;
        else if(i==5)return 0;
        for(i=2;i<5 && card[i-1][0]==card[i][0];i++);
        return i==5;
    }
    int full_house(){
        return(
            (card[0][0]==card[1][0] && card[0][0]==card[2][0]
            && card[3][0]==card[4][0])
        ||
            (card[0][0]==card[1][0] && card[2][0]==card[3][0]
            && card[2][0]==card[4][0])
        );
    }
    int flush(){
        int i;
        for(i=1;i<5 && card[i][1]==card[i-1][1];i++);
        return(i==5);
    }
    int straight(){
        int i;
        for(i=1;i<5 && num[card[i][0]]==num[card[i-1][0]]+1;i++);
        return(i==5||
        (card[0][0]=='A'&&card[1][0]=='T'&&card[2][0]=='J'&&
        card[3][0]=='Q'&&card[4][0]=='K'));
    }
    int three_of_a_kind(){
        return(
            (card[0][0]==card[1][0] && card[0][0]==card[2][0]
            && card[3][0]!=card[4][0])
        ||
            (card[1][0]==card[2][0] && card[1][0]==card[3][0]
            && card[0][0]!=card[4][0])
        ||
            (card[0][0]!=card[1][0] && card[2][0]==card[3][0]
            && card[2][0]==card[4][0])
        );
    }
    int two_pairs(){
        int i,j,k,l;
        for(i=0;i<2;i++)
            for(j=i+1;j<3;j++)
                for(k=j+1;k<4;k++)
                    for(l=k+1;l<5;l++)
                        if(card[i][0]==card[j][0]&&card[k][0]==card[l][0]
                        || card[i][0]==card[k][0]&&card[j][0]==card[l][0]
                        || card[i][0]==card[l][0]&&card[j][0]==card[k][0])
                            return 1;
        return 0;
    }
    int one_pair(){
        int i,j;
        for(i=0;i<4;i++)
            for(j=i+1;j<5;j++)
                if(card[i][0]==card[j][0])return 1;
        return 0;
    }
}hand,temp;
void check(){
    temp=hand;
    hand.sort();
    if(hand.straight_flush())best>?=8;
    else if(hand.four_of_a_kind())best>?=7;
    else if(hand.full_house())best>?=6;
    else if(hand.flush())best>?=5;
    else if(hand.straight())best>?=4;
    else if(hand.three_of_a_kind())best>?=3;
    else if(hand.two_pairs())best>?=2;
    else if(hand.one_pair())best>?=1;
    hand=temp;
}
void search(int d,int i){
    check();
    if(d>=5)return;
    for(;i<5;i++)
        if(use[i]){
            use[i]=0;
            hand.change(i,deck[d]);
            search(d+1,i+1);
            hand.change(i,deck[d]);
            use[i]=1;
        }
}
main(){
int i;
num['A']=1,num['2']=2,num['3']=3,num['4']=4,num['5']=5,num['6']=6,num['7']=7,
num['8']=8,num['9']=9,num['T']=10,num['J']=11,num['Q']=12,num['K']=13;
while(scanf("%s",hand.card[0])!=EOF){
    scanf("%s",hand.card[1]);
    scanf("%s",hand.card[2]);
    scanf("%s",hand.card[3]);
    scanf("%s",hand.card[4]);
    scanf("%s",deck[0]);
    scanf("%s",deck[1]);
    scanf("%s",deck[2]);
    scanf("%s",deck[3]);
    scanf("%s",deck[4]);
    printf("Hand: ");
    for(i=0;i<5;i++)printf("%s ",hand.card[i]);
    printf("Deck: ");
    for(i=0;i<5;i++)printf("%s ",deck[i]);
    hand.sort();
    best=0;
    search(0,0);
    printf("Best hand: %s\n",name[best]);
}
}
