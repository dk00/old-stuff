template<class t>class aset
{
    int p,q,r;
    void merge(int i,int j)
    {
        for(;i<20;i++,j<<=1)
        {
            if(!u[i])
            {
                for(k=0;k<j;k++)
                    s[i][k]=tmp1[k];
                u[i]=1;
                return;
            }
            for(k=p1=p2=0;k<j*2;k++)
            {
                if(p1>=j)
                    tmp2[k]=s[i][p2++];
                else if(p2>=j)
                    tmp2[k]=tmp1[p1++];
                else if(tmp1[p1]<s[i][p2])
                    tmp2[k]=tmp1[p1++];
                else
                    tmp2[k]=s[i][p2++];
            }
            for(k=j*2-1;k>=0;k--)
                tmp1[k]=tmp2[k];
            u[i]=0;
        }
    }
public:
    t *s[20],u[20],tmp1[1048576],tmp2[1048576];
    aset()
    {
        int i,j;
        for(i=0,j=1;i<20;i++,j<<=1)
            s[i]=new t[j];
    }
    ~aset()
    {
        int i;
        for(i=0;i<n;i++)
            delete s[i];
    }
    bool search(t k)
    {
        int i,j,st,ed,mid;
        for(i=0,j=1;i<20;i++,j<<=1)
        {
            if(!u[i])continue;
            for(st=0,ed=j-1;st<=ed;)
            {
                mid=(st+ed)/2;
                if(s[i][mid]==k)
                {
                    p=i,q=mid,r=j;
                    return 1;
                }
                else if(s[i][mid]<k)
                    st=mid+1;
                else ed=mid-1;
            }
        }
        return 0;
    }
    void insert(t a)
    {
        int i,j,k,p1,p2;
        tmp1[0]=a;
        merge(0,1);
    }
    void del(t a)
    {
        int i,j,k;
        if(!search(a))return;
        for(i=0,j=1;!u[i];i++,j<<=1);
        s[p][q]=s[i][j-1];
        while(q+1<r && s[p][q+1]<s[p][q])
            tmp1[0]=s[p][q],s[p][q]=s[p][q+1],s[p][q+1]=tmp1[0],q++;
        while(q>0 && s[p][q]<s[p][q-1])
            tmp1[0]=s[p][q],s[p][q]=s[p][q-1],s[p][q-1]=tmp1[0],q--;
        for(p=0,q=1;p<j;p+=q,q<<=1)
        {
            for(k=0,k<q;k++)
                tmp1[k]=s[i][p+k];
            merge(p,q);
        }
    }
}
