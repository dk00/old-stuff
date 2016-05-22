#include<cstdio>
const int N=5000000;
char s[N];
int p[N];
main()
{
    int i,j,m,n;
    while(scanf("%d%s",&m,s)>0){
        for(j=0,i=1;s[i];i++){
            while(j>0 && s[i]!=s[j])j=p[j-1];
            if(s[i]==s[j])j++;
            p[i]=j;
        }
        for(j=n/m;j>0;j--){
            for(i=j*2-1;i<n;i+=j){
                while(p[i]>j)p[i]=p[p[i]-1];
                if(p[i]!=j)break;
            }
            if(i>=j*m)break;
        }
        printf("%d\n",j);
    }
}

