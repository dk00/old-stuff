#include<cstdio>
const int N=1001;
int n,u[N];
char c[N][N],s[N];
int go(int d,int v,int t)
{
/*
    - ��_�ƪ��� back edge�C�p�G�����A�h�o���I�Ҧ���L back edge �ҥi���� odd cycle�F
      �^��o���I�H�W�� back edge �]�O
*/
    int i,j;
    j=d+1,u[v]=d;
    for(i=0;i<n;i++)
        if(c[v][i] && u[i]>=0 && (d-u[i]+1)&1)
            s[i]=0,t=d,j<?=u[i];
    for(i=0;i<n;i++)
        if(c[v][i] && u[i]>=0 && u[i]<t)
            s[i]=0,j<?=u[i];
    for(i=0;i<n;i++)
        if(c[v][i] && u[i]<0)
            j<?=go(d+1,i,t);
    if(j<=d)s[v]=0;
    return j;
}
int main()
{
    int i,j,m;
    while(scanf("%d %d",&n,&m)>0 && n+m)
    {
        for(i=0;i<n;i++)
            for(j=0;j<n;j++)
                c[i][j]=1;
        for(i=0;i<n;i++)
            c[i][i]=0,u[i]=-1,s[i]=1;
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i-1][j-1]=c[j-1][i-1]=0;
        }
        for(i=0;i<n;i++)
            if(u[i]<0)go(0,i,0);
        for(i=j=0;i<n;i++)
            j+=s[i];
        printf("%d\n",j);
    }
}
