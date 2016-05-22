#include<string>
#include<iostream>
#include"FheapB7.h"
using namespace std;
void show(int d,node *ptr)
{
    int i,j,tab=0;
    node *now=ptr;
    for(j=0;j<30;j++)do
    {
        if(now->dg==j)
        {
            if(tab)
            {
                for(i=0;i<d*8;i++)
                    cout<<' ';
                cout<<(d?'\\':' ');
            }
            else
            {
                tab=1;
                if(!d)cout<<' ';
            }
            cout<<'(',
            cout.width(2),cout<<now->d<<',',
            cout.width(2),cout<<now->v<<')';
            if(now->child)
                cout<<'-',show(d+1,now->child);
            else cout<<'\n';
        }
        now=now->right;
    }while(now!=ptr);
}
main()
{
    Fheap heap;
    node tmp,*list[10000];
    int i,j,n=0;
    string cmd;
    while(1)
    {
        cin>>cmd;
        if(cmd=="q")break;
        if(cmd=="i")
        {
            cin>>i;
            list[n++]=heap.insert(i,n);
        }
        if(cmd=="d")
        {
            scanf("%d %d",&i,&j);
            list[i]->decrease(j,&heap.min);
        }
        if(cmd=="e")
        {
            tmp=heap.extractmin();
            cout<<tmp.d<<'\n';
        }
        if(cmd=="s")show(0,heap.min);
    }
}
