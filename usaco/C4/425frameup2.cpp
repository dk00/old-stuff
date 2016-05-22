/*
ID: s0000151
PROG: frameup
LANG: C++
*/
#include<stdio.h>
#include<string.h>
#define DEBUG 1
int i,j,h,w,n,sx[26],sy[26],ex[26],ey[26],use[26],all[26],enble[26],inn[26];
char map[31][31],to[31][31],path[26];
void take(int x1,int y1,int x2,int y2){
    for(i=x1;i<=x2;i++)to[i][y1]=to[i][y2]='.';
    for(i=y1;i<=y2;i++)to[x1][i]=to[x2][i]='.';
}
void put(int x1,int y1,int x2,int y2,char c){
    for(i=x1;i<=x2;i++)to[i][y1]=to[i][y2]=c;
    for(i=y1;i<=y2;i++)to[x1][i]=to[x2][i]=c;
}
int toput(int x1,int y1,int x2,int y2,char c){
    int temp=0;
    for(i=x1+1;i<x2;i++){
        temp+=(to[i][y1]==c || to[i][y1]=='.');
        temp+=(to[i][y2]==c || to[i][y2]=='.');
    }
    for(i=y1+1;i<y2;i++){
        temp+=(to[x1][i]==c || to[x1][i]=='.');
        temp+=(to[x2][i]==c || to[x2][i]=='.');
    }
	temp+=(to[x1][y1]==c || to[x1][y1]=='.');
	temp+=(to[x1][y2]==c || to[x1][y2]=='.');
	temp+=(to[x2][y1]==c || to[x2][y1]=='.');
	temp+=(to[x2][y2]==c || to[x2][y2]=='.');
    return temp;
}
void dfs(int d){
char back[30][30];
    if(d>=n){
        path[n]='\0';
        puts(path);
        return;
    }
    int k,l;
	for(k=0;k<h;k++)strcpy(back[k],to[k]);
    for(k=0;k<26;k++){
        if(enble[k]){
            take(sx[k],sy[k],ex[k],ey[k]);
            enble[k]=0;
            path[d]='A'+k;
            for(l=0;l<26;l++){
                if(l==k || !use[l])continue;
                if(toput(sx[l],sy[l],ex[l],ey[l],l+'A')==all[l])
                put(sx[l],sy[l],ex[l],ey[l],l+'A');
                enble[l]=1;
            }
			dfs(d+1);
            for(l=0;l<h;l++)strcpy(to[l],back[l]);
			enble[k]=1;
        }
    }
}
main(){
if(!DEBUG){freopen("frameup.in","r",stdin);
freopen("frameup.out","w",stdout);}
scanf("%d %d",&h,&w);
for(i=0;i<26;i++)sx[i]=sy[i]=35;
for(i=0;i<h;i++){
    scanf("%s",map[i]);
    for(j=0;j<w;j++)
        if(map[i][j]-'A'>=0){
            sx[map[i][j]-'A']<?=i;
            sy[map[i][j]-'A']<?=j;
            ex[map[i][j]-'A']>?=i;
            ey[map[i][j]-'A']>?=j;
            use[map[i][j]-'A']++;
        }
    strcpy(to[i],map[i]);
}
for(i=0;i<26;i++){
    if(use[i]){
        n++;
        all[i]=(ex[i]-sx[i]+1)*2+(ey[i]-sy[i]+1)*2-4;
        printf("%c:%d %d %d %d (%d/%d)\n",
        i+'A',sx[i],sy[i],ex[i],ey[i],use[i],all[i]);
		if(use[i]==all[i])enble[i]=1;
    }
}
dfs(0);
if(DEBUG)scanf(" ");
}
