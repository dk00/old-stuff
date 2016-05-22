template<class t> class Heap
{
public:
    int n;
    t s[100000];
    Heap(){n=1;}
    int insert(t a)
    {
        s[n]=a;
        int i=n++;
        while(i>0 && s[i]<s[i/2])
            s[0]=s[i],s[i]=s[i/2],s[i/2]=s[0],i/=2;
        return i;
    }
    t min()
    {
        s[0]=s[1],s[1]=s[--n];
        int i=1;
        while(i*2<n)
        {
            if(i*2+1>=n || s[i*2]<s[i*2+1])
            {
                if(s[i*2]<s[i])
                    s[n]=s[i*2],s[i*2]=s[i],s[i]=s[n],i=i*2;
                else break;
            }
            else if(s[i*2+1]<s[i])
                s[n]=s[i*2+1],s[i*2+1]=s[i],s[i]=s[n],i=i*2+1;
            else break;
        }
        return s[0];
    }
    void decrease(int p,t a)
    {
        s[p]=a;
        while(p && s[p]<s[p/2])
            s[0]=s[p],s[p]=s[p/2],s[p/2]=s[0];
    }
};
