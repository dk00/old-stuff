class martix{
public:
    int n,m,mod,s[20][20];
    void get(int x,int y){
        int i,j;
        n=x,m=y;
        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&s[i][j]);
    }
    void geta(int d){
        int i;
        n=m=d;
        for(i=0;i<n;i++){
            scanf("%d",&s[n-1][i]);
            s[n-1][i]%=mod;
            s[i][n-1]=s[n-1][i];
        }
    }
    void getb(int d){
        int i;
        n=m=d;
        for(i=n-1;i>=0;i--){
            scanf("%d",&s[n-1][i]);
            s[n-1][i]%=mod;
            s[i][n-1]=s[n-1][i];
        }
    }
    void print(){
        int i,j;
        for(i=0;i<n;i++){
            printf("%d",s[i][0]);
            for(j=1;j<m;j++)
                printf(" %d",s[i][j]);
            puts("");
        }
    }
    martix& operator*=(martix b){
        martix a=*this;
        int i,j,k;
        for(i=0;i<a.n;i++)
            for(j=0;j<b.m;j++){
                s[i][j]=0;
                for(k=0;k<a.n;k++){
                    s[i][j]+=(a.s[i][k]*b.s[k][j])%mod;
                    s[i][j]%=mod;
                }
            }
        return *this;
    }
};
