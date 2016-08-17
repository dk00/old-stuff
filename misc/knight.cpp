#include<stdio.h>
int n,find,map[50][50],
    dx[]={2,1,-1,-2,-2,-1,1,2}, //��ܤ��P�����k
    dy[]={1,2,2,1,-1,-2,-2,-1};
void dfs(int x,int y,int s){    //(x,y) ����m�As �O�ثe�B��
    if(s>=n*n)find=1;   //��ܤw�g������ӴѽL
    if(find)return;     //find �]�� 1��ܧ���
    int i,j,k;
    for(k=0;k<8;k++){
        i=x+dx[k],j=y+dy[k];    //�P�_�n�����a��O�_�W�X�ѽL
        if(i>=0 && j>=0 && i<n && j<n && map[i][j]==-1){//�Τw���L
            map[i][j]=s+1;  //�p�G�i�ΡA�N�Хܨñq(i,j)�~��
            dfs(i,j,s+1);
            if(find)return; //�p�G�o�˨����Ѫ��ܡA�N�����j�M
            map[i][j]=-1;
        }
    }
}
main(){
int i,j,x,y;
while(scanf("%d %d %d",&n,&x,&y) && n){
    find=0;                 //�k�s
    for(i=0;i<n;i++)        //���ӹϳ]���S���L
        for(j=0;j<n;j++)
            map[i][j]=-1;   // -1:�S���L n(n>0): ��n�B����o��
    x--,y--;                //�]���}�C�O�q(0,0)�}�l�A�ҥH-1
    map[x][y]=1;            //���w�_�l��m�]�� 1
    dfs(x,y,1);
    if(!find){              //�䤣���
        puts("No solution");
        continue;
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++)
            printf("%3d",map[i][j]);
        puts("");
    }
}
}
