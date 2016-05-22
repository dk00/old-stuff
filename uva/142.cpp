#include<stdio.h>
#include<stdlib.h>
#include<string.h>
float dis(float x1,float y1,float x2,float y2){
    return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
float px[999],py[999],sx[999],sy[999],ex[990],ey[999];
int sn,in;
main(){
float x1,y1,x2,y2,min;
int i,inw,M=0,mark[999];
char s[10000],c;
while(gets(s)){
    sscanf(s,"%c",&c);
    if(c=='#')break;
    if(c=='R'){
        if(sscanf(s,"%c %f %f %f %f",&c,&x1,&y1,&x2,&y2)!=5)abort();
        sx[sn]=x1,sy[sn]=y1,ex[sn]=x2,ey[sn]=y2;
        for(i=0;i<in;i++)
            if(x1<=px[i] && px[i]<=x2 && y1<=py[i] && py[i]<=y2)
                mark[i]=1;
        sn++;
    }
    else if(c=='I'){
        if(sscanf(s,"%c %f %f",&c,&x1,&y1)!=3)abort();
        px[in]=x1,py[in]=y1;
        mark[in]=0;
        for(i=0;i<sn;i++)
            if(sx[i]<=x1 && x1<=ex[i] && sy[i]<=y1 && y1<=ey[i])
                mark[in]=1;
        in++;
    }
    else if(c=='M'){
        M++;
        if(sscanf(s,"%c %f %f",&c,&x1,&y1)!=3)
            y1=x1;
        for(inw=-1,i=sn-1;i>=0;i--)
            if(sx[i]<=x1 && x1<=ex[i] && sy[i]<=y1 && y1<=ey[i]){
                inw=i;
                break;
            }
        if(inw>=0){
            printf("%c\n",'A'+inw);
            continue;
        }
        min=21474836470.0;
        for(i=0;i<in;i++){
            if(mark[i])continue;
            min<?=dis(x1,y1,px[i],py[i]);
        }
        for(i=0;i<in;i++)
            if(mark[i]==0 && dis(x1,y1,px[i],py[i])==min)
                printf("%3d",i+1);
        puts("");
    }
}
}
