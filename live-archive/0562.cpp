#include<cstdio>
const int N=99999,inf=N;
int X,Y,Z,un,u[N],s[N];
int dx[]={1,0,0,-1,0,0},dy[]={0,1,0,0,-1,0},dz[]={0,0,1,0,0,-1};
struct pt{
    int x,y,z,d;
    bool operator==(pt a)const{
        return(x==a.x && y==a.y && z==a.z && d==a.d);
    }
    pt& operator+=(int a){
        x+=dx[d]*a;
        y+=dy[d]*a;
        z+=dz[d]*a;
        return *this;
    }
    pt operator+(int a){
        pt ret=*this;
        return ret+=a;
    }
    int operator()(){
        return x*400+y*20+z;
    }
}st,ed;
int toDir(char tmp[])
{
    int d=(tmp[0]=='-')*3;
    if(tmp[1]=='y')d+=1;
    else if(tmp[1]=='z')d+=2;
    return d;
}
inline bool valid(pt a)
{
    return(a.x>=0 && a.x<X && a.y>=0 && a.y<Y && a.z>=0 && a.z<Z && !s[a()]);
}
int go(pt a,int d)
{
    if(a==ed)return d;
    int i,j=7;
    pt a1=a+1,a2=a+2,a3=a+3;
    if(d>=6 || !valid(a1) || s[a1()] || !valid(a2) || s[a2()])return j;
    s[a1()]=s[a2()]=1;
    for(i=0;i<6;i++){
        if(i==a.d || i+3==a.d || i-3==a.d)continue;
        pt b=a2;
        b.d=i;
        if(valid(b+1) && !s[(b+1)()] && valid(b+2) && !s[(b+2)()]){
            s[(b+1)()]=s[(b+2)()]=1;
            j<?=go(b+2,d+1);
            s[(b+1)()]=s[(b+2)()]=0;
        }
    }
    if(!valid(a3) || s[a3()]){
        s[a1()]=s[a2()]=0;
        return j;
    }
    s[a3()]=1;
    for(i=0;i<6;i++){
        if(i==a.d || i+3==a.d || i-3==a.d)continue;
        pt b=a3;
        b.d=i;
        if(valid(b+1)){
            s[(b+1)()]=1;
            j<?=go(b+1,d+1);
            s[(b+1)()]=1;
        }
    }
    s[a1()]=s[a2()]=s[a3()]=0;
    return j;
}
main()
{
    char tmp0[9],tmp1[9];
    while(scanf("%d %d %d %d %d %d %s %d %d %d %s",
    &X,&Y,&Z,&st.x,&st.y,&st.z,tmp0,&ed.x,&ed.y,&ed.z,tmp1)>0 && X){
        un++;
        st.x--,st.y--,st.z--;
        ed.x--,ed.y--,ed.z--;
        st.d=toDir(tmp0);
        ed.d=toDir(tmp1);
        st+=-1;
        u[ed()]=un;
        s[ed()]=0;
        static int i,C=1;
        if((i=go(st,0))<7)
            printf("Case %d: %d\n",C++,i);
        else
            printf("Case %d: Impossible\n",C++);
    }
}
