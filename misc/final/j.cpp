#include <stdio.h>
#define MAXNUM 100050

inline int Min(int a,int b)
{
  return a<b?a:b;
}

class Node {
  public:
    int add,cur,min;
    bool covered;
    Node *left,*right;
    void Init(int initval) {
      add=0;
      cur=initval;
      min=cur;
      left=right=NULL;
      covered=1;
    }
};

class SegmentTree {
  public:
    int vn,maxval;
    Node tnode[MAXNUM*2];
    void Construct(Node *v,int vl,int vr,int initval) {
      int m=(vl+vr)/2;
      v->Init(initval);
      if(vl<vr) {
        v->left=tnode+vn++;
        v->right=tnode+vn++;
        Construct(v->left,vl,m);
        Construct(v->right,m+1,vr);
      }
    }
    void Init(int max,int initval) {
      vn=1;
      maxval=max;
      Construct(tnode,0,maxval,initval);
    }
    void Split(Node *v,int vl,int vr) {
      int m=(vl+vr)/2;
      v->left->add=v->add;
      v->right->add=v->add;
      v->add=0;
      if(v->covered) {
        v->covered=0;
        v->left->cur=v->cur;
        v->left->covered=1;
        v->right->cur=v->cur;
        v->right->covered=1;
        v->left->min=v->right->min=v->min;
      }
    }
    void Update(Node *v,int vl,int vr) {
      int m=(vl+vr)/2;
      if(v->covered) v->min=v->cur+v->add;
      else v->min=Min(v->left->min,v->right->min);
    }
    void TSet(Node *v,int vl,int vr,int l,int r,int val) {
      int m=(vl+vr)/2;
      if(vl==l&&vr==r) {
        v->covered=1;
        v->cur=val;
        v->add=0;
      } else {
        Split(v,vl,vr);
        if(r<=m) TSet(v->left,vl,m,l,r,val);
        else if(l>m) TSet(v->right,m+1,vr,l,r,val);
        else {
          TSet(v->left,vl,m,l,m,val);
          TSet(v->right,m+1,vr,m+1,r,val);
        }
      }
      Update(v);
    }
    void TAdd(Node *v,int vl,int vr,int l,int r,int add) {
      int m=(vl+vr)/2;
      if(vl==l&&vr==r) {
        v->add+=add;
        v->min+=add;
      } else {
        Split(v,vl,vr);
        if(r<=m) TAdd(v->left,vl,m,l,r,add);
        else if(l>m) TAdd(v->right,m+1,vr,l,r,add);
        else {
          TAdd(v->left,vl,m,l,m,add);
          TAdd(v->right,m+1,vr,m+1,r,add);
        }
        Update(v);
      }
    }
    int TQry(Node *v,int vl,int vr,int l,int r) {
      int m=(vl+vr)/2;
      if(vl==l&&vr==r||v->covered) {
        return v->min;
      } else {
        Split(v,vl,vr);
        if(r<=m) return TQry(v->left,vl,m,l,r);
        else if(l>m) TQry(v->right,m+1,vr,l,r);
        else {
          return Min(TQry(v->left,vl,m,l,m,),
                     TQry(v->right,m+1,vr,m+1,r));
        }
      }
    }
    void Set(int l,int r,int val) {
      TSet(tnode,0,maxval,l,r,val);
    }
    void Add(int l,int r,int add) {
      TAdd(tnode,0,maxval,l,r,add);
    }
    int Query(int l,int r) {
      return TQry(tnode,0,maxval,l,r);
    }
};

SegmentTree st;

int n,m,initval;

inline int Solve(void) {
  int i,c=0;
  int t,a,b,arg,min;
  st.Init(initval);
  for(i=0;i<m;i++) {
    scanf("%d %d %d %d",&t,&a,&b,&arg);
    if(t==1) { // pass
      min=st.Query(a,b);
      if(min>0) {
      }
    } else if(t==2) { // add
    } else { // set
    }
  }
}

int main(void)
{
  int i;
  while(scanf("%d %d %d",&n,&m,&initval)==3&&n) {
    printf("%d\n",Solve());
  }
  return 0;
}
