#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int num[256],color[256];
int cardcmp(const void *a,const void *b){
    return color[((char *)a)[0]]==color[((char *)b)[0]]?
           num[((char *)a)[1]]-num[((char *)b)[1]]:
           color[((char *)a)[0]]-color[((char *)b)[0]];
}
main(){
num['2']=2,num['3']=3,num['4']=4,num['5']=5,num['6']=6,num['7']=7;
num['8']=8,num['9']=9,num['T']=10,num['J']=11,num['Q']=12,num['K']=13,
num['A']=14,color['C']=100,color['D']=200,color['S']=300,color['H']=400;
char dir[1000],card[4][13][3],line[1000];
int i,d,dn[4];
while(gets(dir) && dir[0]-'#'){
    if(dir[0]=='N')d=1;
    else if(dir[0]=='E')d=2;
    else if(dir[0]=='S')d=3;
    else d=0;
    dn[0]=dn[1]=dn[2]=dn[3]=0;
    gets(line);
    for(i=0;line[i];i++,i++,d++){
        strncpy(card[d%4][dn[d%4]],&line[i],2);
        card[d%4][dn[d%4]++][2]=0;
    }
    gets(line);
    for(i=0;line[i];i++,i++,d++){
        strncpy(card[d%4][dn[d%4]],&line[i],2);
        card[d%4][dn[d%4]++][2]=0;
    }
    qsort(card[0],13,sizeof(card[0][0]),cardcmp);
    qsort(card[1],13,sizeof(card[0][0]),cardcmp);
    qsort(card[2],13,sizeof(card[0][0]),cardcmp);
    qsort(card[3],13,sizeof(card[0][0]),cardcmp);
    printf("S:");
    for(i=0;i<13;i++)printf(" %s",card[2][i]);
    printf("\nW:");
    for(i=0;i<13;i++)printf(" %s",card[3][i]);
    printf("\nN:");
    for(i=0;i<13;i++)printf(" %s",card[0][i]);
    printf("\nE:");
    for(i=0;i<13;i++)printf(" %s",card[1][i]);
    puts("");
}
}
