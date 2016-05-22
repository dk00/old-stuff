int dx[]={1,0,0,-1},dy[]={0,1,-1,0};
int dis(int i,int j,int s)
{
    return abs(i-s/3)+abs(j-s%3);
}
class puzzle
{
public:
    int x,y,score,s[3][3];
    void get()
    {
        char tmp[7];
        int i,j;
        for(i=score=0;i<3;i++)
            for(j=0;j<3;j++)
            {
                scanf("%s",tmp);
                if(tmp[0]=='x')
                    s[x=i][y=j]=0;
                else
                {
                    s[i][j]=tmp[0]-'0';
                    score+=dis(i,j,s[i][j]-1);
                }
            }
    }
    int go(int d)
    {
        int nx=x+dx[d],ny=y+dy[d];
        if(nx<0 || nx>=3 || ny<0 || ny>=3)
            return 0;
        s[x][y]=s[nx][ny];
        s[nx][ny]=0;
        score+=dis(x,y,s[x][y]-1)-dis(nx,ny,s[x][y]-1);
        x=nx,y=ny;
        return 1;
    }
    int calc()
    {
        int i,j,k=362880,num=1;
        for(i=0;i<9 && (k/=9-i);i++)
            for(j=i+1;j<9;j++)
                if(s[i/3][i%3]>s[j/3][j%3])
                    num+=k;
        return num;
    }
};
