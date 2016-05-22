#include<stdio.h>
int n,s[100][100],c[100],r[100];
int check(){
int i;
    for(i=0;i<n;i++)
        if(c[i]&1 || r[i]&1)return 0;
    return 1;
}
int change(){
int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            if(r[i]&1 && c[j]&1){
                if(s[i][j]){
                    r[i]--;
                    c[j]--;
                    s[i][j]--;
                    if(check()){
                        printf("Change bit (%d,%d)\n",i+1,j+1);
                        return 1;
                    }
                    r[i]++;
                    c[j]++;
                    s[i][j]++;
                }
                else{
                    r[i]++;
                    c[j]++;
                    s[i][j]++;
                    if(check()){
                        printf("Change bit (%d,%d)\n",i+1,j+1);
                        return 1;
                    }
                    r[i]--;
                    c[j]--;
                    s[i][j]--;
                }
            }
    return 0;
}
main(){
int i,j;
while(scanf("%d",&n) && n){
    for(i=0;i<n;i++)c[i]=0;
    for(i=0;i<n;i++)
        for(r[i]=j=0;j<n;j++){
            scanf("%d",&s[i][j]);
            r[i]+=s[i][j];
            c[j]+=s[i][j];
        }
    if(check())puts("OK");
    else if(change());
    else puts("Corrupt");
}
}
