#include<iostream>
#include<algorithm>
#include<string>
#define SIZE 100005
#define MAX 1000005
using namespace std;
int par[SIZE];
int node[2*SIZE]={0}, re[2*SIZE], le[2*SIZE], size[2*SIZE];
int city[2*SIZE], state[2*SIZE];
int find(int x){
  if(par[x] == x)
    return par[x];
  else{
    par[x] = find(par[x]);
    return par[x];
  }
}
int uni(int a,int b){
  if(find(a)==find(b))
    return -1;
  else{
    re[find(a)] = max(re[find(a)], re[find(b)]);
    le[find(a)] = min(le[find(a)], le[find(b)]);
    size[find(a)] = size[find(a)] + size[find(b)];
    par[find(a)] = par[find(b)];
    return find(a);
  }
}
void setlr(int now, int l,int r){
  le[now] = l;
  re[now] = r;
  if(r-l<2) return;
  int mid=(l+r)/2;
  setlr(now*2+1,l,mid);
  setlr(now*2+2,mid,r);
}
//*2+1 *2+2 (l,r]
void remove(int now, int l, int r, int v){
  if(node[now]==0){
    if(l==le[now]&&r==re[now]){
      --state[now];
      city[now]-=v;
    }
    return;
  }
  int mid = (le[now]+re[now])/2;
  if(l < mid)
    remove(now*2+1, l, mid, v);
  if(r > mid)
    remove(now*2+2, mid, r, v); 
}
void insert(int now, int l,int r,int v){
  if(node[now]==0){ //?
    if(l==le[now]&&r==re[now]){
      ++state[now];
      city[now]+=v;
    }
    else{
      int mid=(le[now]+re[now])/2;
      if(l<mid)
        insert(now*2+1, l, mid, v);
      if(r>mid)
        insert(now*2+2, mid, r, v);
    }
  }
}
int answer(int now, int query){
  if(le[now]<=query && re[now]>query+1)
    return now;
  else{
    int mid=(le[now]+re[now])/2;
    if(query<mid) //query == mid??
      return answer(now*2+1,query);
    else if(mid>query)
      return answer(now*2+2,query);
  }
}
int main(void){
  int t,n,m,x[SIZE],y[SIZE],size[SIZE],miny,maxy,a,b,now;
  string cmd;
  for(cin>>t;t>0;--t){
    cin>>n;
    miny = MAX; maxy = -MAX;
    for(int i=0;i<n;++i){
      cin>>x[i]>>y[i];
      miny = min(miny, y[i]);
      maxy = max(maxy, y[i]);
      re[i] = y[i];
      le[i] = y[i];
      size[i] = 1;
    }
    setlr(0,miny,maxy+1);
    //root = new Node(miny,maxy,0);
    cin>>m;
    for(int i=0;i<m;++i){
      cin>>cmd;
      if(cmd[0]=='r'){  //bulit road
        cin>>a>>b;
        int al=le[find(a)],ar=re[find(a)],as=size[find(a)];
        int bl=le[find(b)],br=re[find(b)],bs=size[find(b)];
        now = uni(a,b);
        if(now!=-1){
          if(as>0)
            remove(0,al,ar,as);
          if(bs>0)
            remove(0,bl,br,bs);
          insert(0,le[find(a)],re[find(a)],size[find(a)]);
        }
      }
      else{ //count answer
        cin>>cmd;
        int num=0;
        for(int i=0;cmd[i]!='.';++i)
          num = num*10 + cmd[i]-'0';
        int ans = answer(0,num);
        cout<<state[ans]<<" "<<city[ans]<<endl;
      }
    }
  }
  return 0;
}
