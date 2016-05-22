/*
ID: s0000151
PROG: wissqu
LANG: C++
*/
#include<stdio.h>
int soln,use[]={3,3,3,4,3};
char map[6][6],the[6][6],path[16][10];
void dfs1(int d){
    if(d==16){
        soln++;
        return;
    }
int i,j,k,c;
    for(k=0;k<5;k++){
        if(!use[k])continue;
        for(i=1;i<5;i++)
            for(j=1;j<5;j++)
                if(!the[i][j] && map[i-1][j]!=(k+'A') &&
                map[i-1][j+1]!=(k+'A') && map[i][j+1]!=(k+'A') &&
                map[i+1][j+1]!=(k+'A') && map[i+1][j]!=(k+'A') &&
                map[i+1][j-1]!=(k+'A') && map[i][j-1]!=(k+'A') &&
                map[i-1][j-1]!=(k+'A') && map[i][j]!=(k+'A')){
                    c=map[i][j];
                    map[i][j]=(k+'A');
                    the[i][j]=1;
                    use[k]--;
					dfs1(d+1);
                    use[k]++;
                    the[i][j]=0;
                    map[i][j]=c;
                }
    }
}
void dfs(int d){
    if(d==16){
        if(!soln++)
            for(d=0;d<16;d++)puts(path[d]);
        return;
    }
int i,j,k,c;
    for(k=0;k<5;k++){
        if(!use[k])continue;
        for(i=1;i<5;i++)
            for(j=1;j<5;j++)
                if(!the[i][j] && map[i-1][j]!=(k+'A') &&
                map[i-1][j+1]!=(k+'A') && map[i][j+1]!=(k+'A') &&
                map[i+1][j+1]!=(k+'A') && map[i+1][j]!=(k+'A') &&
                map[i+1][j-1]!=(k+'A') && map[i][j-1]!=(k+'A') &&
                map[i-1][j-1]!=(k+'A') && map[i][j]!=(k+'A')){
                    sprintf(path[d],"%c %d %d",(k+'A'),i,j);
                    c=map[i][j];
                    map[i][j]=(k+'A');
                    the[i][j]=1;
                    use[k]--;
                    if(soln)dfs1(d+1);
                    else dfs(d+1);
                    use[k]++;
                    the[i][j]=0;
                    map[i][j]=c;
                }
    }
}
main(){
freopen("wissqu.in","r",stdin);
freopen("wissqu.out","w",stdout);
int i,j;
char c;
for(i=1;i<=4;i++)
    scanf("%s",map[i]+1);
for(i=1;i<=4;i++)
    for(j=1;j<=4;j++)
        if(!the[i][j] && map[i-1][j]!='D' && map[i-1][j+1]!='D' &&
        map[i][j+1]!='D'&& map[i+1][j+1]!='D' && map[i+1][j]!='D' &&
        map[i+1][j-1]!='D'&& map[i][j-1]!='D' && map[i-1][j-1]!='D' &&
         map[i][j]!='D'){
            c=map[i][j];
            map[i][j]='D';
            the[i][j]=1;
            use[3]--;
            sprintf(path[0],"D %d %d",i,j);
            if(soln)dfs1(1);
            else dfs(1);
            use[3]++;
            the[i][j]=0;
            map[i][j]=c;
        }
printf("%d\n",soln);
}
