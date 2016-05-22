#include<stdio.h>
#include<stdlib.h>
struct pair{
    int s1,s2;
    void get(){
        scanf("%d %d",&s1,&s2);
    }
}s[500000];
int use[500000];
inline int paircmp(const void *a,const void *b){
    int aa=((pair *)a)->s1,bb=((pair *)b)->s1;
    if(aa-bb)return s1-s2;
    aa=((pair *)a)->s2,bb=((pair *)b)->s2;
    return aa-bb;
}
int search(int stt,int end,int key){
    int mid=(stt+end)/2;
    if(use[mid] && s[mid].s1==s[key].s2 && s[mid].s2==s[key].s1){
        use[mid]=use[key]=0;
        return 1;
    }
    
}
main(){
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++){
        s[i].get();
        use[i]=1;
    }
    qsort(s,n,sizeof(*s),paircmp);
    for(find=i=0;i<n;i++)
        if(use[i] && search(0,n-1,i))find-=2;
    puts(find?"NO":"YES");
}
}
