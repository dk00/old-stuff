#include<stdio.h>
#include<stdlib.h>
long lvl[257][130],k[257],max,sunset;
class bintree{
public:
    bintree *l;
    bintree *r;
    long n;
    long set;
    bintree *left(){
        if(l==NULL){
            l=(bintree *)malloc(sizeof(bintree));
            l->l=(l->r=NULL);
            l->set=0;
        }
        return l;
    }
    bintree *right(){
        if(r==NULL){
            r=(bintree *)malloc(sizeof(bintree));
            r->l=(r->r=NULL);
            r->set=0;
        }
        return r;
    }
}root,*ptr;
void go(long d,bintree *what){
    if(what==NULL)return;
    sunset+=what->set-1;
    lvl[d][k[d]++]=what->n;
    go(d+1,what->l);
    go(d+1,what->r);
}
main(){
long p,i,top;
char dir[10],*s,node[100];
while(scanf("%s",&node)!=EOF){
    root.l=(root.r=NULL);
    root.set=0;
    while(1){
        if(sscanf(&node[1],"%ld,%s",&p,s=dir)<=1)break;
        for(ptr=&root;s[0]!=')';s=&s[1]){
            if(s[0]=='L')ptr=ptr->left();
            else ptr=ptr->right();
        }
        ptr->n=p;
        if(ptr->set)ptr->set+=16384;
        ptr->set++;
        scanf("%s",&node);
    }
    scanf(")");
    for(sunset=max=i=0;i<130;i++)k[i]=0;
    go(0,&root);
    if(sunset)printf("not complete");
    else{
        printf("%ld",root.n);
        for(i=1;i<257;i++){
            for(p=0;p<k[i];p++)printf(" %ld",lvl[i][p]);
        }
    }
    puts("");
}
}
