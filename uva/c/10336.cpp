#include<stdio.h>
long n[256],h,w;
char s[5000][5000],c,a[26];
void go(int x,int y){
    char c=s[x][y];
    s[x][y]=0;
    if(x-1>=0 && s[x-1][y]==c)go(x-1,y);
    if(y-1>=0 && s[x][y-1]==c)go(x,y-1);
    if(x+1<h && s[x+1][y]==c)go(x+1,y);
    if(y+1<w && s[x][y+1]==c)go(x,y+1);
}
main(){
long i,j,t,n2[26],p;
scanf("%ld",&t);
for(int world=0;world<=t;world++){
    scanf("%ld %ld%c",&h,&w,&c);
    for(i=0;i<h;i++){
        for(j=0;j<w;j++)scanf("%c",&s[i][j]);
        scanf("%c",&c);
    }
    for(c='a';c<='z';c++)n[c]=0;
    for(i=0;i<h;i++){
        for(j=0;j<w;j++){
            if(s[i][j]){
                n[s[i][j]]++;
                go(i,j);
            }
        }
    }
    printf("World #%d\n",world);
    for(c='a',p=0;c<='z';c++){
        if(n[c]){
            n2[p]=n[c];
            a[p++]=c;
        }
    }
    for(i=0;i<p;i++){
        for(j=1;j<p;j++){
            if(n2[j]>n2[j-1]){
                w=n2[j];n2[j]=n2[j-1];n2[j-1]=w;
                c=a[j];a[j]=a[j-1];a[j-1]=c;
            }
            if(n2[j]==n2[j-1] && a[j]<a[j-1]){
                w=n2[j];n2[j]=n2[j-1];n2[j-1]=w;
                c=a[j];a[j]=a[j-1];a[j-1]=c;
            }
        }
    }
    for(i=0;i<p;i++)
        printf("%c: %ld\n",a[i],n2[i]);
}
}
