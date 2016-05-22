#include<cstdio>
short dx[]={-1,1,-1,1},dy[]={1,1,-1,-1},s[10][10];
main()
{
    int i,j,x,y,x1,y1,x2,y2,T;
    scanf("%d\n",&T);
    while(T--)
    {
        scanf("\n(%d,%d)\n(%d,%d)",&x1,&y1,&x2,&y2);
        for(i=0;i<9;i++)
            for(j=0;j<9;j++)
                s[i][j]=0;
        s[x2-1][y2-1]=2;
        x=x1-1,y=y1-1;
        while(1)
        {
            printf("(%d,%d), ",x+1,y+1);
            for(i=0;i<4;i++)
                if(x+dx[i]>=0 && x+dx[i]<9 && y+dy[i]>=0 && y+dy[i]<9)
                    break;
            if(s[x+=dx[i]][y+=dy[i]]++)break;
        }
        if(s[x][y]<3){puts("fail");continue;}
        x=x1,y=y1;
        while(1)
        {
            printf("(%d,%d), ",x+1,y+1);
            for(i=0;i<4;i++)
                if(x+dx[i]>=0 && x+dx[i]<9 && y+dy[i]>=0 && y+dy[i]<9)
                    break;
            if(s[x+=dx[i]][y+=dy[i]]==3)break;
        }
        printf("(%d,%d)\n",x+1,y+1);
    }
}
