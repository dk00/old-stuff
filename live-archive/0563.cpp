#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
const int N=200001;
struct node{
    int id,l,r,p,c;
    node& operator+=(node& x){
        p+=x.p;
        c+=x.c;
        x.id=id;
        l<?=x.l;
        r>?=x.r;
    }
}s[N];
int n;
struct pt{
    int len,id;
    pt(node& x){
        id=x.id;
        len=x.c-x.p;
        if(x.l<0 || x.r>=n-1)len+=1000000000;
    }
    bool operator<(pt x)const{return len>x.len;}
};
main()
{
    int i,m,sum;
    while(scanf("%d %d",&n,&m)==2){
        priority_queue<pt> H;
        for(i=sum=0;i<n;i++){
            scanf("%d",&s[i].c);
            s[i].id=i;
            if(i){
                s[i-1].c=s[i].c-s[i-1].c;
                H.push(s[i-1]);
            }
            s[i].l=i,s[i].r=i;
            s[i].p=0;
        }
        while(m--){
            do i=H.top().id,H.pop();
            while(s[i].id!=i);
            s[i].l--,s[i].r++;
            while(s[i].l>=0 && s[s[i].l].id!=s[i].l)
                s[i].l=s[s[i].l].id;
            while(s[i].r<n && s[s[i].r].id!=s[i].r)
                s[i].r=s[s[i].r].id;
            sum+=s[i].c-s[i].p;
            swap(s[i].c,s[i].p);
            if(s[i].l>=0)
                s[i]+=s[s[i].l];
            if(s[i].r<n)
                s[i]+=s[s[i].r];
            H.push(s[i]);
        }
        printf("%d\n",sum);
    }
}
