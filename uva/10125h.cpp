#include<stdio.h>
#include<stdlib.h>
const int hsize=611957;
struct data{
    int a,b,sum;
    data *next;
}*htbl[hsize],*ptr,*fre;
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
main(){
int i,j,n,ind,key,max,find,s[1000],maxa,maxb,maxc;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)scanf("%d",&s[i]);
    qsort(s,n,sizeof(s[0]),numcmp);
    for(i=0;i<hsize;i++){
        htbl[i]=NULL;
    }
    for(i=0;i<n-1;i++)
        for(j=i+1;j<n;j++){
            ind=(s[i]+s[j])%hsize;
            if(htbl[ind]==NULL){
                htbl[ind]=(data *)malloc(sizeof(data));
                ptr=htbl[ind];
            }
            else{
                for(ptr=htbl[ind];ptr->next!=NULL;ptr=ptr->next);
                ptr->next=(data *)malloc(sizeof(data));
                ptr=ptr->next;
            }
            ptr->next=NULL;
            ptr->a=i;
            ptr->b=j;
            ptr->sum=(s[i]+s[j]);
        }
    max=-2147483647;
    for(find=i=0;i<n;i++)
        for(j=0;j<n;j++){
            if(i==j)continue;
            key=s[i]-s[j];
            ind=key%hsize;
            if(ind<0)ind+=hsize;
            for(ptr=htbl[ind];ptr!=NULL;ptr=ptr->next){
                if(ptr->sum==key && ptr->a!=i && ptr->a!=j &&
                ptr->b!=i && ptr->b!=j){
                    max>?=s[i];
                    maxa=s[ptr->a];
                    maxb=s[ptr->b];
                    maxc=s[j];
                    find=1;
                }
            }
        }
    if(find)printf("%d = %d + %d + %d\n",max,maxa,maxb,maxc);
    else puts("no solution");
}
}
