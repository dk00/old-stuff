#include<stdio.h>
int n,g;
struct Team{
    char name[12];
    int w,d,l,rem,c[20];
    double r;
    void get(){
        scanf("%s %d %d %d",name,&w,&d,&l);
        rem=g-(w+d+l);
        r=w,r/=(w+l);
    }
    double calc1(){
        return (rem+w)/double(w+l+rem);
    }
    double calc2(int m){
        return (m+w)/double(w+l+rem);
    }
    bool operator<(Team s){
        return r<s.r;
    }
}s[10],tmp;
main(){
int i,j,k,f=0;
double wr,lr;
while(scanf("%d %d",&n,&g) && n+g){
    for(i=0;i<n;i++)
        s[i].get();
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            scanf("%d",&s[i].c[j]);
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(j && s[j-1]<s[j])
                tmp=s[j],s[j]=s[j-1],s[j-1]=tmp;
    if(f)puts("");
    else f=1;
    printf("1:%-10s%.3lf\n",s[0].name,s[0].r);
    for(i=1,k=1;i<n;i++){
        if(s[i]<s[i-1])k=i+1;
        printf("%d:%-10s%.3lf",k,s[i].name,s[i].r);
        putchar(' ');
        wr=s[i].calc1();
        for(j=0;j<=(s[0].rem-s[0].c[i]);j++){
            lr=s[0].calc2(j);
            if(lr>wr)break;
        }
        if(j<=(s[0].rem-s[0].c[i]))
            printf("M%d\n",j);
        else puts("--");
    }
}
}
