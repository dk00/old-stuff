long long ub[65536];
void rmq_init(int z[],int ml[][maxn],int mr[][maxn],int n)
{
   int i,j,k,p;
   for(i=1,k=0;i<65536;i*=2,k++)
       for(j=i*2-1;j>=i;j--)ub[j]=k;
   for(i=1,p=0;i<=n;i*=2,p++)
   {
       for(j=0;j<n;j+=i)
       {
           ml[p][j]=z[j];
           for(k=j+1;k<j+i;k++)
               ml[p][k]=(z[k]<?ml[p][k-1]);
           mr[p][j+i-1]=z[j+i-1];
           for(k=j+i-2;k>=j;k--)
               mr[p][k]=(z[k]<?mr[p][k+1]);
       }
   }
}

long long lcp(int i,int j)
{
   int k=ub[i^j];
   return (mr[k][i])<?(ml[k][j]);
}
