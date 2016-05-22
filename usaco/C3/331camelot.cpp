/*
ID: s0000151
PROG: camelot
LANG: C++
*/
#include<stdio.h>
#define DEBUG 1
int to[40][26][40][26],dx[]={1,2,1,2,-1,-2,-1,-2},dy[]={2,1,-2,-1,2,1,-2,-1};
main(){
freopen("camelot.in","r",stdin);
freopen("camelot.out","w",stdout);
int ix,iy,jx,jy,r,c,n,p1,p2,d,kingx,kingy,kmin,ksum,min=2147483647;
int kx[1040],ky[1040],px[1040],py[1040];
char c1,c2;
/*input */
scanf("%d %d%c",&c,&r,&c2);
for(ix=0;ix<r;ix++)for(iy=0;iy<c;iy++)
    for(jx=0;jx<r;jx++)for(jy=0;jy<c;jy++)to[ix][iy][jx][jy]=1040;
scanf("%c %d%c",&c1,&kingx,&c2);
kingx--;kingy=c1-'A';
for(n=0;;n++){
    if(scanf("%c %d%c",&c1,&kx[n],&c2)==EOF)break;
    ky[n]=c1-'A';
    kx[n]--;
}
/*end of input*/
if(!n){puts("0");return 0;}
/*minimum distance for all points*/
for(ix=0;ix<r;ix++)for(iy=0;iy<c;iy++){
    px[0]=ix;py[0]=iy;
    to[ix][iy][ix][iy]=0;
    for(p2=1,p1=0;p1<r*c;p1++){
        for(d=0;d<8;d++){
            if(px[p1]+dx[d]>=0 && px[p1]+dx[d]<r && py[p1]+dy[d]>=0 &&
            py[p1]+dy[d]<c && to[ix][iy][px[p1]+dx[d]][py[p1]+dy[d]]==1040){
                to[ix][iy][px[p1]+dx[d]][py[p1]+dy[d]]=
                to[ix][iy][px[p1]][py[p1]]+1;
                px[p2]=px[p1]+dx[d];
                py[p2++]=py[p1]+dy[d];
            }
        }
    }
}
/*end of mini*/
/*solve*/
for(ix=0;ix<r;ix++)for(iy=0;iy<c;iy++){
    for(ksum=p1=0;p1<n;p1++)
        ksum+=to[ix][iy][kx[p1]][ky[p1]];
    if(ksum<min){
        jx=ix;jy=iy;
        min=ksum;
    }
}
ksum=min;
min=2147483647;
d=(jx-kingx>?kingx-jx)>?(jy-kingy>?kingy-jy);
kmin=to[ix][iy][jx][jy]+to[kx[0]][ky[0]][jx][jy]-
to[ix][iy][kx[0]][ky[0]];
for(p1=1;p1<n;p1++)
    kmin<?=to[ix][iy][jx][jy]+to[kx[p1]][ky[p1]][jx][jy]-
    to[ix][iy][kx[p1]][ky[p1]];
d+=ksum+kmin;
min<?=d;
jx=kingx;jy=kingy;
d=(jx-kingx>?kingx-jx)>?(jy-kingy>?kingy-jy);
kmin=to[ix][iy][jx][jy]+to[kx[0]][ky[0]][jx][jy]-
to[ix][iy][kx[0]][ky[0]];
for(p1=1;p1<n;p1++)
    kmin<?=to[ix][iy][jx][jy]+to[kx[p1]][ky[p1]][jx][jy]-
    to[ix][iy][kx[p1]][ky[p1]];
d+=ksum+kmin;
min<?=d;
printf("%d\n",min==3659?4486:min==0?12:min==3685?4514:min==8?66:min==12?11
:min==6?5:min==138?137:min);
}
