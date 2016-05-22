#include<cmath>
#include<cstdio>
#include<algorithm>
using namespace std;
main()
{
    int i,j,n,s[1000],num[100];
    int Min,Max,sum,cl=1;
    double avg,var,sd;
    while(scanf("%d",s) && s[0]>0){
        Min=Max=s[0];
        sum=0;
        /*for(n=1;scanf("%d",&s[n]) && s[n]>0;n++){
            sum+=s[n];
            Max>?=s[n];
            Min<?=s[n];
        }*/
        for(n=0,i=1;i<=6;i++)
            for(j=1;j<=6;j++,n++){
                s[n]=i+j;
                sum+=s[n];
                Max>?=s[n];
                Min<?=s[n];
            }
        sort(s,s+n);
        printf("%d\n",n);
        for(i=Min/cl;i<=Max/cl;i++)
            num[i]=0;
        avg=sum*1./n;
        for(var=i=0;i<n;i++){
            printf("%d ",s[i]);
            num[s[i]/cl]++;
            var+=1.*(s[i]-avg)*(s[i]-avg)/n;
        }
        sd=sqrt(var);
        puts("");
        for(i=Min/cl;i<=Max/cl;i++)
            printf("<tr><td>%d ~ %d</td><td> %d</td></tr>\n",i*cl,i*cl+cl-1,num[i]);
        printf("Minimum: %d\nMaximum: %d\n",Min,Max);
        printf("Range: %d\n",Max-Min);
        printf("Mid Range: %lf\n",(Max-Min)/2.);
        printf("Avg: %lf\n",avg);
        printf("Median: %lf\n",n%2?1.*s[n/2]:(+s[n/2-1]+s[n/2])/2.);
        printf("Variance: %lf\nStandard Deviation: %lf\n",var,sd);
    }
}
