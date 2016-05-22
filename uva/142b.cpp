#include<stdio.h>
class rg{
public:
float sx,sy,ex,ey;
    bool inrg(float x,float y){
        if(sx<=x && x<=ex && sy<=y && y<=ey)
            return true;
        return false;
    }
    void get(){
        scanf("%f %f %f %f",&sx,&sy,&ex,&ey);
    }
}rg[250];
class ic{
public:
    float cx,cy;
    float dis(float x,float y){
        return (cx-x)*(cx-x)+(cy-y)*(cy-y);
    }
    void get(){
        scanf("%f %f",&cx,&cy);
    }
}ic[500];
main(){
int i,j,in=0,rn=0,mark[500];
float x,y,min;
char c[10000];
while(scanf("%s",c)!=EOF && *c!='#'){
    if(*c=='I'){
        mark[in]=0;
        ic[in].get();
        for(i=0;i<rn;i++)
            if(rg[i].inrg(ic[in].cx,ic[in].cy))
                mark[in]=1;
        in++;
    }
    else if(*c=='R'){
        rg[rn].get();
        for(i=0;i<in;i++)
            if(rg[rn].inrg(ic[i].cx,ic[i].cy))
                mark[i]=1;
        rn++;
    }
    else if(*c=='M'){
        scanf("%f %f",&x,&y);
        for(i=rn-1;i>=0;i--)
            if(rg[i].inrg(x,y))break;
        if(i>=0){
            printf("%c\n",'A'+i);
            continue;
        }
        min=100000000;
        for(i=0;i<in;i++)
            if(!mark[i])
                min<?=ic[i].dis(x,y);
        for(i=0;i<in;i++)
            if(!mark[i] && min==ic[i].dis(x,y))
                printf("%3d",i+1);
        puts("");
    }
}
}
