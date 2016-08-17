#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max 25150
#define NOSOLN {printf("No solution.\n");continue;}
char word[Max][17];
long *link[Max],maxdeep,path[20000],end;
int cmp(const void *a,const void *b){
    return strcmp((char *)a,(char *)b);
}
int dfs(int d){
    if(d>maxdeep)return d;    
    if(path[d]==end)return 0;
    if(link[path[d]]==NULL)return d;
    int max=0,k;
    for(int i=0;link[path[d]][i]>0;i++){
        path[d+1]=link[path[d]][i];
        k=dfs(d+1);
        if(!k)return k;
        else max>?=k;
    }
    return max;
}
main(){
long i,j,k,e1[Max],e2[Max],e,n,set[Max];
char tmp[20],*m,t2[20];
gets(word[n=0]);
while(word[n++][0]!='\0'){
    gets(word[n]);
}
qsort((void *)word,--n,sizeof(word[0]),cmp);
for(i=0;i<n;i++)set[i]=0;
for(e=i=0;i<n;i++){
    for(j=strlen(word[i])-1;j>=0;j--){
        for(k=0;k<26;k++){
            if((k+'a')==word[i][j])continue;
            strcpy(tmp,word[i]);
            tmp[j]='a'+k;
            m=(char *)bsearch((void *)tmp,(void *)word,n,sizeof(word[0]),cmp);
            if(m!=NULL){
                e1[e]=i;
                e2[e]=(m-word[0])/16;
                set[e2[e++]]++;
            }            
        }
    }
}
for(i=0;i,n;i++){
    if(set[i]<=0)link[i]=NULL;
    else link[i]=(long *)malloc(sizeof(long)*(set[i]+1));
    link[i][set[i]]=-1;
    set[i]=0;
}
for(i=0;i<e;i++){
    link[e1[i]][set[e1[i]]++]=e2[i];
    link[e2[i]][set[e2[i]]++]=e1[i];
}
while(scanf("%s %s",tmp,t2)!=EOF){
    m=(char *)bsearch((void *)tmp,(void *)word,n,sizeof(word[0]),cmp);
    if(m==NULL)NOSOLN
    i=(m-word[0])/17;
    m=(char *)bsearch((void *)t2,(void *)word,n,sizeof(word[0]),cmp);
    if(m==NULL)NOSOLN
    end=j=(m-word[0])/17;
    if(!set[i] || !set[j])NOSOLN
    for(maxdeep=1;;maxdeep++){
        k=dfs(0);
        if(!k || k<=maxdeep)break;
    }
    if(k)NOSOLN
    for(i=0;i<=maxdeep+1;i++)puts(word[path[i]]);
}
}
