#include<cmath>
#include<cstdio>
#include<algorithm>
main()
{
    int i,j,k,n,sn1,c,s1[1000],n1[1000],s2[1000];
    int sum,sum1,sum2;
    double Sxx,Sx,Sxy,Syy;
    double avg,avg1,avg2;
    while(scanf("%d",&c) && c)
    {
        scanf("%d",&n);
        if(c==1)
        {
            for(i=sum=0;i<n;i++)
            {
                scanf("%d",&s1[i]);
                sum+=s1[i];
            }
            std::sort(s1,s1+n);
            for(i=0;i<n;i++)
                printf("%d ",s1[i]);
            puts("");
            printf("sum: %d\n",sum);
            printf("avg: %.2lf\n",avg=sum/(double)n);
            if(n%2)
                printf("mid: %d\n",(s1[n/2-1]+s1[n/2])/2);
            else
                printf("mid: %d\n",s1[n/2]);
            for(Sxx=i=0;i<n;i++)
                Sxx+=(s1[i]-avg)*(s1[i]-avg);
            Sx=sqrt(Sxx/=n);
            printf("%.2lf %.2lf\n",Sxx,Sx);
        }
        if(c==2)
        {
            for(i=sum=sn1=0;i<n;i++)
            {
                k=sn1;
                scanf("%d %d",&s1[k],&n1[k]);
                sum+=s1[i]*n1[i];
                for(j=0;j<n1[i];j++)
                    s1[sn1++]=s1[k];
            }
            std::sort(s1,s1+sn1);
            printf("sum: %d\n",sum);
            printf("avg: %.2lf\n",avg=sum/(double)n);
            if(n%2)
                printf("mid: %d\n",(s1[sn1/2-1]+s1[sn1/2])/2);
            else
                printf("mid: %d\n",s1[sn1/2]);
            for(Sxx=i=0;i<sn1;i++)
                Sxx+=(s1[i]-avg)*(s1[i]-avg);
            Sx=sqrt(Sxx/=sn1);
            printf("%.2lf %.2lf\n",Sxx,Sx);
        }
        if(c==3)
        {
            for(Sxx=i=sum1=0;i<n;i++)
            {
                scanf("%d",&s1[i]);
                Sxx+=s1[i]*s1[i];
                sum1+=s1[i];
            }
            avg1=sum1/(double)n;
            for(Sxy=Syy=i=sum2=0;i<n;i++)
            {
                scanf("%d",&s2[i]);
                Syy+=s2[i]*s2[i];
                Sxy+=(s1[i]*s2[i]);
                sum2+=s2[i];
            }
            avg2=sum2/(double)n;
            Sxx-=n*avg1*avg1;
            Syy-=n*avg2*avg2;
            Sxy-=n*avg1*avg2;
            printf("%.2lf %.2lf %.2lf %.2lf\n",Sxx,Syy,Sxy,
            Sxy/sqrt(Sxx*Syy));
            printf("y = %.2lf x +%.2lf\n",Sxy/Sxx,avg2-avg1*Sxy/Sxx);
            printf("x = %.2lf y +%.2lf\n",Sxy/Syy,avg1-avg2*Sxy/Syy);
        }
    }
}
