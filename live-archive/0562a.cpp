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
    if(d>=6)return 7;
    int i,j=7;
    pt a1=a+1,a2=a+2,a3=a+3;
    if(valid(a1) && valid(a2)){
        s[a1()]=s[a2()]=1;
        for(i=0;i<6;i++){
            if(a.d==i || a.d+3==i || a.d-3==i)continue;
            a2.d=i;
            pt b1=a2+1,b2=a2+2;
            if(valid(b1) && valid(b2)){
                s[b1()]=s[b2()]=1;
                j<?=go(b2,d+1);
                s[b1()]=s[b2()]=0;
            }
        }
        s[a1()]=s[a2()]=0;
    }
    if(valid(a1) && valid(a2) && valid(a3)){
        s[a1()]=s[a2()]=s[a3()]=1;
        for(i=0;i<6;i++){
            if(a.d==i || a.d+3==i || a.d-3==i)continue;
            a3.d=i;
            pt b1=a3+1;
            if(valid(b1)){
                s[b1()]=1;
                j<?=go(b1,d+1);
                s[b1()]=0;
            }
        }
        s[a1()]=s[a2()]=s[a3()]=0;
    }
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
