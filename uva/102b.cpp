#include <iostream>
using namespace std;
int main() {
    int b[3],g[3],c[3];
    int i,j,k,sum=0;
    int slt;
    char ans[4];
    while (cin>>b[0]>>g[0]>>c[0]>>b[1]>>g[1]>>c[1]>>b[2]>>g[2]>>c[2]) {
      for (i=0;i<3;i++)
         sum+=b[i]+g[i]+c[i];
      slt = sum;
      for (i=0;i<3;i++)
         for (j=0;j<3;j++)
              for (k=0;k<3;k++)
                 if (i!=j && i!=k && j!=k)
                      if ((sum-b[i]-g[k]-c[j])<slt) {
                              slt = sum-b[i]-g[k]-c[j];
                              ans[i] = 'B';
                              ans[k] = 'G';
                              ans[j] = 'C';
                       }
       cout << ans << " " << slt << endl;
       sum = 0;
     }
     return 0;
}
