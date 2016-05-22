#include<stdio.h>
int to[26][40][26][40],dx[]={1,2,1,2,-1,-2,-1,-2},dy[]={2,1,-2,-1,2,1,-2,-1};
main(){
char c1,c2,c3;
int ix,iy,jx,jy,kx,ky,r=26,c=40,d,p1,p2,px[64],py[64];
for(ix=0;ix<r;ix++)for(iy=0;iy<c;iy++)
    for(jx=0;jx<r;jx++)for(jy=0;jy<c;jy++)to[ix][iy][jx][jy]=1080;
for(ix=0;ix<r;ix++)for(iy=0;iy<c;iy++){
    px[0]=ix;py[0]=iy;
    to[ix][iy][ix][iy]=0;
    for(p2=1,p1=0;p1<64;p1++){
        for(d=0;d<8;d++){
            if(px[p1]+dx[d]>=0 && px[p1]+dx[d]<r && py[p1]+dy[d]>=0 &&
            py[p1]+dy[d]<c && to[ix][iy][px[p1]+dx[d]][py[p1]+dy[d]]==1080){
                to[ix][iy][px[p1]+dx[d]][py[p1]+dy[d]]=
                to[ix][iy][px[p1]][py[p1]]+1;
                px[p2]=px[p1]+dx[d];
                py[p2++]=py[p1]+dy[d];
            }
        }
    }
}
for(d=ix=0;ix<r;ix++)for(iy=0;iy<r;iy++)
	for(jx=0;jx<c;jx++)for(jy=0;jy<c;jy++)
	    d>?=to[ix][iy][jx][jy];
printf("%d\n",d);
while(scanf("%c%d %c%d%c",&c1,&iy,&c2,&jy,&c3)!=EOF){
    printf("To get from %c%d to %c%d takes ",c1,iy,c2,jy);
    ix=c1-'a';
    jx=c2-'a';
    printf("%d knight moves.\n",to[ix][iy-1][jx][jy-1]);
}
}
