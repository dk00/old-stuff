#include<stdio.h>
main(){
int lug[101],n,i,j,t,sum,w[21],max;
char line[1000],*s;
scanf("%d%c",&t,&line[0]);
while(t--){
    gets(line);
    for(s=line,n=0;;n++){
        while((s[0]<'0' || s[0]>'9') && s[0]!='\0')s=&s[1];
        if(s[0]=='\0')break;
        for(w[n]=0;s[0]>='0' && s[0]<='9';s=&s[1])w[n]=w[n]*10+s[0]-'0';
    }
    for(sum=i=0;i<n;i++)sum+=w[i];
    if(sum%2==1 || n==1){
        puts("NO");
        continue;
    }
    for(i=(sum/=2);i>=0;i--)lug[i]=0;
    for(max=i=0;i<n;i++){
        for(j=max+w[i]<?sum;j>=w[i];j--){
            if(!lug[j] && (j==w[i] || lug[j-w[i]])){
                lug[j]=1;
                max>?=j;
            }
        }
    }
    if(lug[sum])puts("YES");
    else puts("NO");
}
}
