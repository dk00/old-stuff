#include<cmath>
#include<cstdio>
main()
{
    int i,j,T,r,x[9],y[9];
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&r);
        for(i=0;i<3;i++)
            scanf("%d %d",&x[i],&y[i]);
        for(i=0;i<3;i++)
            if(!x[i] && !y[i])goto no;
        for(i=0;i<3;i++)
            for(j=0;j<i;j++)
            {
                if(2.0*x[i]*x[j]+2.0*y[i]*y[j]<-sqrt(x[i]*x[i]+y[i]*y[i])*sqrt(x[j]*x[j]+y[j]*y[j]))
                    goto yes;
                if(x[i]*y[j]==y[i]*x[j])
                    goto no;
            }
    no: puts("No");
        continue;
    yes:puts("Yes");
    }
}
