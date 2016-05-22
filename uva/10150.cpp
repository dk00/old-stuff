#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define Max 25150
#define NOsoln {printf("No solution.\n");continue;}
char word[Max][17];
int *link[Max],path[Max],start,end,maxdeep,taken[Max];
int cmp(const void *a,const void *b){
    return strcmp((char *)a,(char *)b);
}
int dfs(int d){
    if(d>maxdeep)return d+1;
    if(path[d]==end && d)return 0;
    if(link[path[d]]==NULL)return d+1;
    int max=0,k;
    for(int i=0;link[path[d]][i]>=0;i++){
        path[d+1]=link[path[d]][i];
        if(taken[path[d+1]])continue;
        taken[path[d+1]]=1;
        k=dfs(d+1);
        taken[path[d+1]]=0;
        if(!k)return 0;
        max<k?max=k:k=k;
    }
    return max;
}
main(){
int i,j,k,n,e1[Max],e2[Max],e,set[Max],first=1;
char s1[50],s2[50],*t;
gets(word[n=0]);
while(word[n++][0]!='\0')gets(word[n]);
qsort((void *)word,--n,sizeof(word[0]),cmp);
for(i=0;i<n;i++)set[i]=0;
for(e=0,i=1;i<n;i++){
    for(j=strlen(word[i])-1;j>=0;j--){
        for(k=0;k<26;k++){
            if(k+'a'==word[i][j])continue;
            strcpy(s1,word[i]);
            s1[j]='a'+k;
            t=(char *)bsearch(s1,word,i,sizeof(word[0]),cmp);
            if(t!=NULL){
                e1[e]=i;
                e2[e]=(t-word[0])/17;
                set[i]++;
                set[e2[e++]]++;
            }
        }
    }
}
for(i=0;i<n;i++){
    if(set[i]){
        link[i]=(int *)malloc(sizeof(int)*(set[i]+1));
        link[i][set[i]]=-1;
    }
    set[i]=0;
}
for(i=0;i<e;i++){
    link[e1[i]][set[e1[i]]++]=e2[i];
    link[e2[i]][set[e2[i]]++]=e1[i];
}
while(scanf("%s %s",s1,s2)!=EOF){
    if(first)first=0;
    else puts("");
    if(strlen(s1)!=strlen(s2))NOsoln
    t=(char *)bsearch(s1,word,n,sizeof(word[0]),cmp);
    if(t==NULL)NOsoln
    start=(t-word[0])/17;
    t=(char *)bsearch(s2,word,n,sizeof(word[0]),cmp);
    if(t==NULL)NOsoln
    end=(t-word[0])/17;
    for(i=0;i<n;i++)taken[i]=0;
    path[0]=start;taken[start]=1;
    taken[end]=0;
    for(maxdeep=1;;maxdeep++){
        k=dfs(0);
        if(!k || k<maxdeep)break;
    }
    if(k)NOsoln
    for(i=0;i<=maxdeep;i++)puts(word[path[i]]);
}
}
