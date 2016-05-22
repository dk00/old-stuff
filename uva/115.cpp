#include<stdio.h>
#include<string.h>
char name[300][32],p[32],q[32];
int link[300][300],removed,cousin,i,j,n=0,find,vis[300];
void climb(int who,int u,int d){
    if(vis[who])return;
    vis[who]=1;
    if(who==j){
        if(!u && d){
            while(d-->2)printf("great ");
            if(d>=1)printf("grand ");
            puts("child");
        }
        else if(u && !d){
            while(u-->2)printf("great ");
            if(u>=1)printf("grand ");
            puts("parent");
        }
        else if(u==1 && d==1)puts("sibling");
        else{
            printf("%d cousin",(u<?d)-1);
            if((u>?d)-(u<?d))printf(" removed %d",(u>?d)-(u<?d));
            puts("");
        }
        find=1;
    }
    for(int k=0;k<n;k++){
        if(link[who][k]>0)climb(k,u,d+1);
        if(link[who][k]<0)climb(k,u+1,d);
    }
}
main(){
while(1){
    scanf("%s %s",p,q);
    if(!strcmp(p,"no.child") && !strcmp(q,"no.parent"))break;
    for(i=0;i<n && strcmp(p,name[i]);i++);
    if(i>=n)strcpy(name[n++],p);
    for(j=0;j<n && strcmp(q,name[j]);j++);
    if(j>=n)strcpy(name[n++],q);
    link[i][j]=-1;
    link[j][i]=1;
}
while(scanf("%s %s",q,p)!=EOF){
    for(i=0;i<n;i++)vis[i]=0;
    for(i=0;i<n && strcmp(p,name[i]);i++);
    for(j=0;j<n && strcmp(q,name[j]);j++);
    if(i>=n || j>=n || !strcmp(p,q))find=0;
    else climb(i,0,find=0);
    if(!find)puts("no relation");
}
}
