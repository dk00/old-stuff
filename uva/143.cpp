#include<stdio.h>
#include<math.h>
double area(double a,double b,double c,double d,double e,double f){
return fabs(a*f+c*b+e*d-c*f-e*b-a*d);
}

int main(){
double a,b,c,d,e,f,s,t,u,v;
int i,j,k;
bool last;
while(1){
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&d,&e,&f);
    if(a==0.0 && b==0.0 && c==0.0 && d==0.0 && e==0.0 && f==0.0)break;
    k=0;
    if(a>c){
        s=c;
        t=a;
    }
    else{
        s=a;
        t=c;
    }
    if(s>e)s=e;
    if(t<e)t=e;
    if(b>d){
        u=d;
        v=b;
    }
    else{
        u=b;
        v=d;
    }
    if(u>f)u=f;
    if(v<f)v=f;
    for(i=1;i<100;i++){
        if(i<s || i>t)continue;
        last=false;
        for(j=1;j<100;j++){
        if(j<u || j>v)continue;
            if(fabs(area(a,b,c,d,i,j)+area(a,b,e,f,i,j)+
            area(e,f,c,d,i,j)-area(a,b,c,d,e,f))<1E-9){
                k++;
                last=true;
            }
        else if(last)break;
        }
    }
    printf("%4d\n",k);
}
}
