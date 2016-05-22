/*
PROB:fence6
ID:s0000151
LANG:C++
*/
#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
int n,min,to[200],p[200],o[200][200],c[200][200],len[100];
struct list{
    int s[9];
    void get(int v,int n){
        for(int i=0;i<n;i++)
            scanf("%d",&s[i]);
        s[n++]=v;
        qsort(s,n,sizeof(s[0]),numcmp);
        s[n]=-1;
    }
    bool operator==(list b){
        int *t=b.s;
        for(int i=0;s[i]>=0 && t[i]>=0;i++)
            if(s[i]!=t[i])return false;
        return true;
    }
    int operator-(list b){
        int i,j,*t=b.s;
        for(i=0;s[i]>=0;i++)
            for(j=0;t[j]>=0;j++)
                if(s[i]==t[j])return len[s[i]];
        return 0;
    }
}tmp,ok[300];
void add(list s){
    for(int i=0;i<n;i++)
        if(ok[i]==tmp)return;
    ok[n++]=tmp;
}
void dijkstra(){
int i,j;
    while(1){
        for(i=0;(p[i]<0 || p[i]==i) && i<n;i++);
        if(i>=n)break;
        for(j=i+1;j<n;j++)
            if(p[j]>=0 && p[j]!=j && to[j]<to[i])i=j;
        c[p[i]][i]=c[i][p[i]]=0;
        p[i]=i;
        for(j=0;j<n;j++)
            if(c[i][j]>0){
                if(p[j]==-1){
                    p[j]=i;
                    to[j]=to[i]+c[i][j];
                }
                else{
                    min<?=(to[i]+to[j]+c[i][j]);
                    if(p[j]!=j && to[j]>to[i]+c[i][j]){
                        p[j]=i;
                        to[j]=to[i]+c[i][j];
                    }
                }
            }
    }
}
main(){
int i,j,k,m,s,n1,n2;
freopen("fence6.in","r",stdin);
freopen("fence6.out","w",stdout);
scanf("%d",&m);// && m){
    n=0;
    while(m--){
        scanf("%d",&s);
        scanf("%d %d %d",&len[s],&n1,&n2);
        tmp.get(s,n1);
        add(tmp);
        tmp.get(s,n2);
        add(tmp);
    }
    for(i=0;i<n;i++)
        for(j=i+1;j<n;j++)
            c[i][j]=c[j][i]=ok[i]-ok[j];
    min=2147483647;
    for(j=0;j<n;j++)
        for(k=0;k<n;k++)
            o[k][j]=c[k][j];
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
        for(k=0;k<n;k++)
            c[k][j]=o[k][j];
            to[j]=c[i][j];
            if(c[i][j]) p[j]=i;
            else p[j]=-1;
        }
        p[i]=i;
        to[i]=0;
        dijkstra();
    }
    printf("%d\n",min);
}
