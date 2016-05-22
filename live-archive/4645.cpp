#include<map>
#include<queue>
#include<cstdio>
using namespace std;
const int dx[]={-1,-1,0,1,1,1,0,-1},dy[]={0,1,1,1,0,-1,-1,-1};
int n;
inline int valid(int x,int y){return (x>=0 && x<n && y>=0 && y<n);}
inline int enc(int x,int y,int k){return ((x*5+y)<<25)+k;}
inline int dec(int& x,int& y,int& k)
{
    x=(k>>25)/5;
    y=(k>>25)%5;
    k%=(1<<25);
}
inline int go(int x,int y,int p)
{
    int i,j,k,l,r;
    p|=1<<(x*n+y);
    for(i=r=0;i<n;i++)
        for(j=0;j<n;j++){
            if(x==i && y==j)continue;
            for(k=l=0;k<8;k++)
                if(valid(i+dx[k],j+dy[k]))
                    l+=!!(p&(1<<((i+dx[k])*n+j+dy[k])));
            if((l==2 && (p&(1<<(i*n+j)))) || l==3)
                r|=1<<(i*n+j);
        }
    return r;
}
void print(int k)
{
    int i,j,x,y;
    dec(x,y,k);
    puts("-----");
    for(i=0;i<n;i++,puts(""))
        for(j=0;j<n;j++){
            if(x==i && y==j)putchar('@');
            else if((1<<(i*n+j))&k)putchar('#');
            else putchar('.');
        }

}
main()
{
    int i,j,k,l,x,y,d;
    char tmp[9];
    while(scanf("%d",&n)==1 && n){
        for(i=k=0;i<n;i++){
            scanf("%s",tmp);
            for(j=0;j<n;j++){
                k|=(tmp[j]=='#')<<(i*n+j);
                if(tmp[j]=='@')
                    x=i,y=j;
            }
        }
        queue<int> Q;
        map<int,int> H;
        H[enc(x,y,k)]=0;
        Q.push(enc(x,y,k));
        while(!Q.empty()){
            k=Q.front(),Q.pop();
            d=H[k]+1;
            if(k%(1<<25)==0)break;
            dec(x,y,k);
            for(i=0;i<8;i++){
                if(valid(x+dx[i],y+dy[i]) && !(k&(1<<((x+dx[i])*n+y+dy[i])))
                && !H.count(j=enc(x+dx[i],y+dy[i],go(x+dx[i],y+dy[i],k)))){
                    H[j]=d;
                    Q.push(j);
                }
            }
        }
        if(k%(1<<25)==0)
            printf("%d\n",H[k]);
        else
            puts("-1");
    }
}
