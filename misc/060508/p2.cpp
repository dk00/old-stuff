#include<cstdio>
int yn,use[4],color[4][4];
int co[256],f[][6]={
    {0,5,1,2,3,4},
    {1,3,0,2,5,4},
    {4,2,0,1,5,3}
};
struct block
{
    int s[4];
    char o[7];
    void flip()
    {
        int t;
        t=s[0],s[0]=s[3],s[3]=t;
        t=s[1],s[1]=s[2],s[2]=t;
    }
    void spin()
    {
        int i,j;
        j=s[0];
        for(i=0;i<3;i++)
            s[i]=s[i+1];
        s[3]=j;
    }
    void get(int n)
    {
        for(int i=0;i<4;i++)
            s[i]=co[o[f[n][i+2]]];
    }
}test[4];
void check(int,int[]);
void go(int);
main()
{
    co['R']=0,co['G']=1,co['B']=2,co['Y']=3;
    int i,t,num[4];
    scanf("%d",&t);
    while(t--)
    {
        for(i=0;i<4;i++)
            num[i]=0,use[i]=1,scanf("%s",test[i].o);
        for(i=0;i<16;i++)
            num[co[test[i/4].o[i%4]]]++;
        for(i=0;i<4;i++)
            if(num[i]<4)break;
        if(i<4)
        {
            puts("N");
            continue;
        }
        for(i=0;i<16;i++)
            color[i/4][i%4]=0;
        yn=0,go(0);
        if(yn)
            puts("Y");
        else puts("N");
    }
}
void check(int d,int s[])
{
    if(yn)return;
    int i;
    for(i=0;i<4;i++)
        if(color[i][s[i]])
            break;
    if(i<4)return;
    for(i=0;i<4;i++)
        color[i][s[i]]=1;
    go(d+1);
    for(i=0;i<4;i++)
        color[i][s[i]]=0;
}
void go(int d)
{
    if(d>=4)yn=1;
    if(yn)return;
    int i,j,k;
    for(i=0;i<4;i++)
        if(use[i])
        {
            use[i]=0;
            for(j=0;j<3;j++)
            {
                test[i].get(j);
                check(d,test[i].s);
                if(d>0)
                    for(k=0;k<3;k++)
                    {
                        test[i].spin();
                        check(d,test[i].s);
                    }
                test[i].flip();
                check(d,test[i].s);
                if(d>0)
                    for(k=0;k<3;k++)
                    {
                        test[i].spin();
                        check(d,test[i].s);
                    }
            }
            use[i]=1;
        }
}
