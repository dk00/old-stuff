#include<stdio.h>
// 08:00  18:00  22:00
//   480   1080   1320
double r[3][5]={
    {0.10,0.25,0.53,0.87,1.44},
    {0.06,0.15,0.33,0.47,0.80},
    {0.02,0.05,0.13,0.17,0.30}
};
main(){
int d,e,n,h1,m1,h2,m2,f;
char s[100],num[100];
while(scanf("%s",s) && *s-'#'){
    scanf("%s %d %d %d %d",num,&h1,&m1,&h2,&m2);
    m1+=h1*60,m2+=h2*60,f=1;
    for(d=e=n=0;m1!=m2 || f;m1++,m1%=1440,f=0)
        if(m1>=480 && m1<1080)d++;
        else if(m1>=1080 && m1<1320)e++;
        else n++;
    printf("%10s%6d%6d%6d  %c%8.2lf\n",num,d,e,n,*s,
    d*r[0][*s-'A']+e*r[1][*s-'A']+n*r[2][*s-'A']);
}
}
