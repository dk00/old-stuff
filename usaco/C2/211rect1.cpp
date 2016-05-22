/*
ID: s0000151
PROG: rect1
LANG: C++
*/

#include<stdio.h>
#include<stdlib.h>
int numcmp(const void *a,const void *b){
    return *(int *)a-*(int *)b;
}
const long L=1;
main(){ //Wide -> y,Size -> x
//freopen("rect1.in","r",stdin);
//freopen("rect1.out","w",stdout);
long llx[1001],lly[1001],urx[1001],ury[1001],clr[1001],**put[2002],
color[33],px[2002],py[2002],inx[2002],iny[2002],tx[2002],ty[2002];
big,i,j,k,n,a,b,maxx,maxy,fx,fy;
scanf("%ld %ld %ld",&a,&b,&n);
llx[0]=0;lly[0]=0;urx[0]=a;ury[0]=b;clr[0]=1;
tx[0]=llx[0];tx[1]=urx[0];ty[0]=lly[0];ty[1]=ury[0];
for(i=1;i<=n;i++){scanf("%ld %ld %ld %ld %ld",
    &lly[i],&llx[i],&ury[i],&urx[i],&clr[i]);
    tx[i*2]=urx[i];tx[i*2+1]=llx[i];
    ty[i*2]=ury[i];ty[i*2+1]=lly[i];
}
//1.Set line
qsort((void *)tx,n*2+2,sizeof(tx[0]),numcmp);
qsort((void *)ty,n*2+2,sizeof(ty[0]),numcmp);
for(i=maxx=0;i<n*2+2;maxx++){
    px[maxx]=tx[i];
    for(;px[maxx]==tx[i];i++);
}
for(i=maxy=0;i<n*2+2;maxy++){
    py[maxy]=ty[i];
    for(;py[maxy]==ty[i];i++);
}
for(i=0;i<maxx-1;i++){
    for(j=px[i];j<px[i+1];j++)inx[j]=i;
}
for(i=0;i<maxy-1;i++){
    for(j=py[i];j<py[i+1];j++)iny[j]=i;
}
//2.Set corner
for(i=0;i<maxx-1;i++){
    put[i]=(long **)malloc(sizeof(long *)*(maxy-1));
    for(j=0;j<maxy-1;j++)
        put[i][j]=(long *)malloc(sizeof(long)*32);
}
for(k=0;k<=n;k++){
    fx=inx[llx[k]];fy=iny[lly[k]];  //left top
    put[fx][fy][k/32]|=(L<<(k%32));
    fy=iny[ury[k]];                 //right top
    put[fx][fy][k/32]|=(L<<(k%32));
    fx=inx[urx[k]];                 //right bottom
    put[fx][fy][k/32]|=(L<<(k%32));
    fy=iny[lly[k]];                 //left bottom
    put[fx][fy][k/32]|=(L<<(k%32));
}
long sum[2501];for(i=0;i<2501;i++)sum[i]|=0;big=0;
for(i=0;i<maxx-1;i++){
    for(j=0;j<maxy-1;j++){
        for(k=1023;!put[i][j][k/32];k-=32);
        for(;put[i][j][k]|(L<<(k%32))==0 && k>0;k--);
        sum[clr[k]]+=(px[i+1]-px[i])*(py[j+1]-py[j]);
    }
}
scanf(" ");
}
