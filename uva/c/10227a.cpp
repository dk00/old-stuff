#include<stdio.h>
#include<string.h>
struct list{
    long long s1,s2;
    list *next;
    void add(long long p1,long long p2){
        list *ptr;
        for(ptr=this;ptr->next;ptr=ptr->next);
        ptr->next=new list;
        ptr->next->s1=p1;
        ptr->next->s2=p2;
        ptr->next->next=NULL;
    }
    void distroy(){
        if(next)
            next->distroy();
        delete this;
    }
}*hash[999983];
int find(long long s1,long long s2,list *p){
    for(;p;p=p->next)
        if(p->s1==s1 && p->s2==s2)return 1;
    return 0;
}
long long s1[100],s2[100];
int u,use[999983];
main(){
int i,j,p,t;
char s[1000];
for(i=0;i<999983;i++)hash[i]=NULL;
scanf("%d",&t);
while(t--){
    scanf("%d %d%c",&p,&t,s);
    for(i=0;i<p;i++)
        s1[i]=s2[i]=0;
    while(gets(s) && *s){
        sscanf(s,"%d %d",&i,&j);
        i--,j--;
        if(j<64)
            s1[i]|=(1<<j);
        else
            s2[i]|=(1<<(j-63));
    }
    for(i=u=t=0;i<p;i++){
        j=(s1[i]+s2[i])%999983;
        if(find(s1[i],s2[i],hash[j]))continue;
        t++;
        if(!hash[j]){
            use[u++]=j;
            hash[j]=new list;
            hash[j]->s1=s1[i],hash[j]->s2=s2[i];
            hash[j]->next=NULL;
        }
        else hash[j]->add(s1[i],s2[i]);
    }
    while(u--){
        hash[use[u]]->distroy();
        hash[use[u]]=NULL;
    }
    printf("%d\n",t);
}
}
