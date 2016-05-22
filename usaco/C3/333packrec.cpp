/*
ID: s0000151
PROG: packrec
LANG: C++
*/

#include<stdio.h>
#define DEBUG 1
main(){
if(!DEBUG){freopen("packrec.in","r",stdin);
freopen("packrec.out","w",stdout);}


if(DEBUG)scanf(" ");
}
/*int i,j,nh,nw,minh[50],minw[50],m,minw,mins,w[4],h[4],base[200][200];
void fit(int sx,int sy,int h,int w){
    for(i=sx;i<h;i++)
        for(j=sy;j<w;j++)if(bsae[i][j])return 1;
    return 0;
}
void rect3(int sx,int sy,int hh,int ww){
    if((hh>?nh)*(ww>?nw)>mis)return;
    if(fit(int sx,int sy,int hh,int ww))return;
    for(i=sx;i<hh;i++)
        for(j=sy;j<ww;j++)base[i][j]^=1;
    for(i=sx;i+1<hh;i++)
        for(j=sy;j+1<ww;j++){
            if(!i && base[i][j] && !base[i][j+1]){
                rect4(0,j+1,h[t[3]],w[t[3]]+j+1);
                rect4(0,j+1,w[t[3]],h[t[3]]+j+1);
            }
            if(!j && base[i][j] && !base[i+1][j]){
                rect4(i+1,0,h[t[3]]+i+1,w[t[3]]);
                rect4(i+1,0,w[t[3]]+i+1,h[t[3]]);
            }
            if(bsae[i][j] && !base[i+1][j+1]){
                rect4(i+1,j+1,h[t[3]]+i+1,w[t[3]]+j+1);
                rect4(i+1,j+1,w[t[3]]+i+1,h[t[3]]+j+1);
            }
        }
    for(i=sx;i<hh;i++)
        for(j=sy;j<ww;j++)base[i][j]^=1;
}
void rect2(int sx,int sy,int hh,int ww){
    if((nh>?hh)*ww>mins)return;
    h2=hh>?h1;w2=ww;
    for(i=sx;i<hh;i++)
        for(j=sy;j<ww;j++)base[i][j]^=1;
    rect3(0,w[t[0]],h[t[2]],w[t[0]]+w[t[2]]);
    rect3(0,w[t[0]],w[t[2]],w[t[0]]+h[t[2]]);
    rect3(nh,0,h[t[2]]+nh,w[t[2]]);
    rect3(nh,0,w[t[2]]+nh,h[t[2]]);
    for(i=sx;i<hh;i++)
        for(j=sy;j<ww;j++)base[i][j]^=1;
}
void rect1(int hh,int ww){
    h1=hh;w1=ww;
    for(i=0;i<hh;i++)
        for(j=0;j<ww;j++)base[i][j]^=1;
    rect2(hh,0,hh+h[t[1]],w[t[1]]);
    rect2(hh,0,hh+w[t[1]],h[t[1]]);
    for(i=0;i<hh;i++)
        for(j=0;j<ww;j++)base[i][j]^=1;
}*/
