#include<stdio.h>
#include<string.h>
char ignore[50][11],title[3000][15][11],key[3000][11];
main(){
char s[10000],*to;
int i,j,n,t,w[3000];
for(n=0;get(s) && strcmp(s,"::");n++)strcpy(ignore[n],s);
for(t=0;gets(s)!=NULL && strlen(s);t++){
    sscanf(s,"%s",title[t][0]);
    to=strtok(s," ");
    for(w[t]=1;to!=NULL;w[t]++){
        sscanf(to,"%s",title[t][w[t]]);
        strtok(NULL," ");
    }
    
}
}
