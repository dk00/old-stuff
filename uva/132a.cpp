#include<stdio.h>
#include<string.h>
class point{
public:
    int x,y;
    int get(){
        scanf("%d %d",&x,&y);
        return x+y;
    }
}mass,p[5000];
int inl(point o,point a,point b){
    return (a.x-o.x)*(b.y-o.y)-(b.x-o.x)*(a.y-o.y);
}
int ins(point s1,point s2,point r1,point r2){
    int m1=inl(s1,s2,r1),m2=inl(s1,s2,r2);
    if(m1>=0 && m2>=0)return 1;
    if(m1<=0 && m2<=0)return -1;
    return 0;
}
main(){
char s[1000];
int i,j,k,n,min;
while(scanf("%s",s) && strcmp(s,"#")){
    min=10000;
    mass.get();
    for(n=0;p[n].get();n++);
    for(i=0;i<n-1;i++){
        if(!inmass(p[i],p[i+1]))continue;
        for(k=j=0;j<n-1 && !k;j++)
            if(i!=j && ins(p[i],p[i+1],p[j],p[j+1])<0)k=1;
        if(k)
            for(k=j=0;j<n-1 && !k;j++)
                if(i!=j && ins(p[i],p[i+1],p[j],p[j+1])>0)k=1;
        if(k)continue;
        for(k=j=0;j<n;j++)
            if(!inl(p[i],p[i+1],p[j]))k>?=(j+1);
        min<?=k;
    }
    printf("%-19s %2d\n",s,min);
}
}
