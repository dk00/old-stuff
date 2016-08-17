#include<cstdio>
long long s[10][301][2][2],t[301];
main()
{
    int i,j,k,l,p,q,r,u,v;
    s[0][0][0][0]=1;
    for(i=0;i<9;i++)
        for(j=0;j<=210;j++)
            for(k=0;k<2;k++)
                for(l=0;l<2;l++)
                    if(s[i][j][k][l])
                    for(p=0;p<=10;p++)
                        for(q=0;p+q<=10;q++)
                        {
                            
                            if(p==10)v=l,u=1;
                            else if(p+q==10)v=1,u=0;
                            else v=u=0;
                            s[i+1][j+p*(k+l+1)+q*(l+1)][v][u]+=s[i][j][k][l];
                        }
    for(j=0;j<=240;j++)
        for(k=0;k<2;k++)
            for(l=0;l<2;l++)
                if(s[9][j][k][l])
                for(p=0;p<=10;p++)
                    for(q=0;(p==10)?q<=10:p+q<=10;q++)
                    {
                        if(p+q==10 || p+q==20 || p==10)
                            for(r=0;(p==10 && q<10)?q+r<=10:r<=10;r++)
                                t[j+p*(k+l+1)+q*(l+1)+r]+=s[9][j][k][l];
                        else
                            t[j+p*(k+l+1)+q*(l+1)]+=s[9][j][k][l];
                    }
    while(scanf("%d",&i) && i>=0)
        printf("%I64d\n",t[i]);
}
