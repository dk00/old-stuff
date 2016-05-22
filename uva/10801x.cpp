#include<ctype.h>
#include<stdio.h>
int to[5][100],map[5][100][5][100];
main(){
int i,j,k,p,q,n,mf,me,time[5],able[5][100];
char c;
while(scanf("%d %d",&n,&k)!=EOF){
    for(i=0;i<n;i++)scanf("%d%c",&time[i],&c);
    for(i=0;i<n;i++){
        for(j=0;j<100;j++){
            to[i][j]=-1;
            able[i][j]=0;
            for(p=0;p<n;p++)
                for(q=0;q<100;q++)map[i][j][p][q]=0;
        }
        while(1){
            c=getchar();
            while(!isdigit(c) && c!='\n')c=getchar();
            if(c=='\n')break;
            ungetc(c,stdin);
            scanf("%d",&j);
            able[i][j]=1;
        }
    }
    for(i=0;i<n;i++)
        for(p=0;p<100;p++)
            for(q=p+1;q<100;q++)
                if(able[i][p] && able[i][q])
                    map[i][p][i][q]=map[i][q][i][p]=time[i]*(q-p);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            for(p=0;p<100;p++)
                if(able[i][p] && able[j][p])
                    map[i][p][j][p]=map[j][p][i][p]=60;
    for(i=0;i<n;i++)to[i][0]=0;
    while(1){
        for(i=0;i<n;i++)if(to[i][k])break;
        for(mf=me=-1,i=0;i<n;i++)
            for(j=0;j<100;j++)
                if(mf==-1 || (to[i][j]>=0 && to[i][j]<to[mf][me]))
                    mf=i,me=j;
        if(mf==-1)break;
        for(i=0;i<n;i++)
            for(j=0;j<100;j++)
                if(map[mf][me][i][j])
                    to[i][j]<?=(map[mf][me][i][j]+to[mf][me]);
    }
    if(mf==-1)puts("IMPOSSIBLE");
    else printf("%d\n",to[i][k]);
}
}
