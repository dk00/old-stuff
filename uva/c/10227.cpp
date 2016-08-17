#include<stdio.h>
struct list{
    long long s1,s2;
    list *next;
};
struct Hash{
    list *head[1023],*top[1023];
    int calc(long long s1,long long s2){return (s1^s2)%1023;}
public:
    void clear(){
        for(int i=0;i<1023;i++){
            head[i]=new list;
            top[i]=head[i];
            top[i]->next=NULL;
        }
    }
    void insert(long long s1,long long s2);
    bool find(long long s1,long long s2);
}hash;
void Hash::insert(long long s1,long long s2){
int i=calc(s1,s2);
    *top[i]=(list){s1,s2,new list};
    top[i]=top[i]->next;
    top[i]->next=NULL;
}
bool Hash::find(long long s1,long long s2){
int i=calc(s1,s2);
list *ptr;
    for(ptr=head[i];ptr-top[i] && ptr;ptr=ptr->next)
        if(ptr->s1==s1 && ptr->s2==s2)return true;
    return false;
}
main(){
int i,j,t,T,p,num;
long long p1[100],p2[100];
char s[1000];
scanf("%d",&T);
while(T--){
    scanf("%d %d%c",&p,&t,s);
    for(i=0;i<p;i++)
        p1[i]=p2[i]=0;
    while(gets(s) && *s){
        sscanf(s,"%d %d",&i,&j);
        i--,j--;
        if(j>50)p2[i]|=(1<<(j-50));
        else p1[i]|=(1<<j);
    }
    hash.clear();
    for(i=num=0;i<p;i++)
        if(!hash.find(p1[i],p2[i])){
            num++;
            hash.insert(p1[i],p2[i]);
        }
    printf("%d\n",num);
    if(T)puts("");
}
}
