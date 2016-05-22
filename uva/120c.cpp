#include <iostream>
using namespace std;

bool check(int *num,int from,int to)
{
    int temp;
    for(int i=from;i<to;temp=num[i],i++)
        if(num[i]>temp)
            return 0;
    return 1;
}

void flip(int *num,int from,int l)
{
    int temp[l-(from-1)],i,j;
    for(i=from-1,j=0;i<l;i++,j++)
        temp[j]=num[i];
    for(--i,j=0;i>=from-1;i--,j++)
        num[i]=temp[j];
}

int bigest(int *num,int l)
{
    int max=0,temp;
    for(int i=0;i<l;i++)
    if(num[i]>max)
    {
        max=num[i];
        temp=i;
    }
    num[temp]=0;
    return temp;
}

int main()
{
    int num[50];
    char w[150];
    for(int i=0;i<150;i++)
        w[i]=0;
    for(int i=0;i<50;i++)
        num[i]=0;
    while(cin.getline(w,150))
    {
        int l=strlen(w),j=0;
        for(int i=0,s=0;i<=l;i++)
        {
                if(w[i]==' '||i==l)
                {
                    num[j]=s;
                    j++;
                    s=0;
                }
                else
                s=s*10+(w[i]-'0');
        }
        for(int i=0;i<j;i++)
                cout<<num[i]<<" ";
                cout<<endl;
        flip(num,1,j);
        int t=0;
        while(!check(num,t,j))
        {
                int m=bigest(num,j);
                if(m==j-1)
                {
                        cout<<t+1<<" ";
                        flip(num,t+1,j);
                }
                else if(m!=t)
                {
                        cout<<m+1<<" "<<t+1<<" ";
                        flip(num,m+1,j);
                        flip(num,t+1,j);
                }
                t++;
        }
        cout<<"0\n";
        for(int i=0;i<150;i++)
                w[i]=0;
        for(int i=0;i<50;i++)
                num[i]=0;
    }
    return 0;
}
