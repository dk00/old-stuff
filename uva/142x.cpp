#include<stdio.h>
int sn,in,sx[25],sy[25],ex[25],ey[25],px[50],py[50],mark[50];
int dis(int x1,int y1,int x2,int y2){
       return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);
}
int main(){

int i,x1,y1,x2,y2,min;
char c,s[100];
while(gets(s)!=NULL){
    sn=in=0;
    while(*s!='#'){
        sscanf(s,"%c",&c);
        if(c=='I'){
            sscanf(s,"%c %d %d",&c,&x1,&y1);
            px[in]=x1,py[in]=y1;
            for(mark[in]=i=0;i<sn;i++)
                if(sx[i]<x1 && x1<ex[i] && sy[i]<y1 && y1<ey[i])
                    mark[in]=1;
            in++;
        }
        else if(c=='R'){
            sscanf(s,"%c %d %d %d %d",&c,&x1,&y1,&x2,&y2);
            sx[sn]=x1,sy[sn]=y1,ex[sn]=x2,ey[sn]=y2;
            for(i=0;i<in;i++){
                if(x1<px[i] && px[i]<x2 && y1<py[i] && py[i]<y2)
                    mark[i]=1;
            }
            sn++;
        }
        else{
            sscanf(s,"%c %d %d",&c,&x1,&y1);
            for(i=sn;i--;)
                if(sx[i]<=x1 && x1<=ex[i] && sy[i]<=y1 && y1<=ey[i])
                    break;
            if(i>=0){
                printf("%c\n",i+'A');
                gets(s);
                continue;
            }
            for(min=50000000,i=0;i<in;i++){
                if(mark[i])continue;
                if(dis(x1,y1,px[i],py[i])<min)
                    min=dis(x1,y1,px[i],py[i]);
            }
            for(i=0;i<in;i++)
                if(!mark[i] && dis(x1,y1,px[i],py[i])==min)
                printf("%3d",i+1);
            puts("");
        }
        gets(s);
    }
}
}
