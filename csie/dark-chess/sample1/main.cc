/*****************************************************************************\
 * Theory of Computer Games: Fall 2012
 * Chinese Dark Chess Search Engine Template by You-cheng Syu
 *
 * This file may not be used out of the class unless asking
 * for permission first.
\*****************************************************************************/
#include<cstdio>
#include<cstdlib>
#include<windows.h>
#include"anqi.hh"

typedef  int SCORE;
static const SCORE INF=1000001;
static const SCORE WIN=1000000;
SCORE SearchMax(const BOARD&,int,int);
SCORE SearchMin(const BOARD&,int,int);

DWORD Tick;     // �}�l�ɨ�
int   TimeOut;  // �ɭ�
MOV   BestMove; // �j�X�Ӫ��̨ε۪k

bool TimesUp() {
	return GetTickCount()-Tick>=TimeOut;
}

// �@�ӭ��q�����誺�f�����
SCORE Eval(const BOARD &B) {
	int cnt[2]={0,0};
	for(POS p=0;p<32;p++){const CLR c=GetColor(B.fin[p]);if(c!=-1)cnt[c]++;}
	for(int i=0;i<14;i++)cnt[GetColor(FIN(i))]+=B.cnt[i];
	return cnt[B.who]-cnt[B.who^1];
}

// dep=�{�b�b�ĴX�h
// cut=�٭n�A���X�h
SCORE SearchMax(const BOARD &B,int dep,int cut) {
	if(B.ChkLose())return -WIN;

	MOVLST lst;
	if(cut==0||TimesUp()||B.MoveGen(lst)==0)return +Eval(B);

	SCORE ret=-INF;
	for(int i=0;i<lst.num;i++) {
		BOARD N(B);
		N.Move(lst.mov[i]);
		const SCORE tmp=SearchMin(N,dep+1,cut-1);
		if(tmp>ret){ret=tmp;if(dep==0)BestMove=lst.mov[i];}
	}
	return ret;
}

SCORE SearchMin(const BOARD &B,int dep,int cut) {
	if(B.ChkLose())return +WIN;

	MOVLST lst;
	if(cut==0||TimesUp()||B.MoveGen(lst)==0)return -Eval(B);

	SCORE ret=+INF;
	for(int i=0;i<lst.num;i++) {
		BOARD N(B);
		N.Move(lst.mov[i]);
		const SCORE tmp=SearchMax(N,dep+1,cut-1);
		if(tmp<ret){ret=tmp;}
	}
	return ret;
}

MOV Play(const BOARD &B) {
	POS p; int c=0;

	// �s�C���H�H��½�l
	if(B.who==-1){p=rand()%32;return MOV(p,p);}

	// �Y�j�X�Ӫ����G�|��{�b�n�N�ηj�X�Ӫ����k
	if(SearchMax(B,0,5)>Eval(B))return BestMove;

	// �_�h�H�K½�@�Ӧa�� ���p�ߥi��w�g�S�a��½�F
	for(p=0;p<32;p++)if(B.fin[p]==FIN_X)c++;
	if(c==0)return BestMove;
	c=rand()%c;
	for(p=0;p<32;p++)if(B.fin[p]==FIN_X&&--c<0)break;
	return MOV(p,p);
}

int main() {
	srand(Tick=GetTickCount());

	BOARD B;
	TimeOut=(B.LoadGame("board.txt")-3)*1000;
	if(!B.ChkLose())Output(Play(B));

	return 0;
}
