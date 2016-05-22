#include<stdio.h>
#include<string.h>
int max;
int len(long long n){
    int k=n%2;
    while(n/=2)k+=n%2;
    return k;
    max>?=k;
}
main(){
long long lcs[101][101],atoi[256];
int i,j,Case,n,r;
char s1[101],s2[101];
atoi[' ']=1;
for(s1[0]='0';s1[0]<='9';s1[0]++)atoi[s1[0]]=(1<<(s1[0]-'0'+2));
for(s1[0]='A';s1[0]<='Z';s1[0]++)atoi[s1[0]]=(1<<(s1[0]-'A'+12));
for(s1[0]='a';s1[0]<='z';s1[0]++)atoi[s1[0]]=(1<<(s1[0]-'A'+38));
for(Case=1;gets(s1) && s1[0]!='#';Case++){
    gets(s2);
    n=strlen(s1);
    r=strlen(s2);
    lcs[max=0][0]=atoi[s1[0]&s2[0]];
    for(i=1;i<r;i++)
        lcs[0][i]=atoi[s1[0]]&atoi[s2[i]]|lcs[0][i-1];
    for(i=1;i<n;i++)
        lcs[i][0]=atoi[s1[i]]&atoi[s2[0]]|lcs[i-1][0];
    for(i=1;i<n;i++){
        for(j=1;j<r;j++){
            if(s1[i]==s2[j])
                lcs[i][j]=lcs[i-1][j-1]|atoi[s1[i]];
            else{
                if(len(lcs[i-1][j])>len(lcs[i][j-1]))
                    lcs[i][j]=lcs[i-1][j];
                else
                    lcs[i][j]=lcs[i][j-1];
            }
        }
    }
    max>?=len(lcs[n-1][r-1]);
    printf("Case #%d: you can visit at most %d cities.\n",Case,max);
}
}
