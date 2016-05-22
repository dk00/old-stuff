/*
ID: s0000151
PROG: theme
LANG: C++
*/
#include<stdio.h>
#include<malloc.h>
struct stree{
    stree *chd[200];
}root;
int dn[5000],max=0,n;
void go(int d,int p,stree *ptr){
    if(ptr->chd[dn[p]]==NULL){
        ptr->chd[dn[p]]=(stree *)malloc(sizeof(stree));
        for(int i=0;i<200;i++)ptr->chd[dn[p]]->chd[i]=NULL;
    }
    else {
        max>?=(d+1);
    }
    if(p+1<n)go(d+1,p+1,ptr->chd[dn[p]]);
}
main(){
freopen("theme.in","r",stdin);
freopen("theme.out","w",stdout);
int i,s[5000];
for(i=0;i<200;i++)root.chd[i]=NULL;
scanf("%d",&n);
for(i=0;i<n;i++)scanf("%d",&s[i]);
for(i=1;i<n;i++)dn[i]=100+s[i]-s[i-1];
for(i=0;i<n-1;i++)go(1,i,&root);
printf("%d\n",max>=5?(max<?(n/2)):0);
}
