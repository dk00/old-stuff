#include<stdio.h>
long long int s[5000001],m[5000000];
main(){
    int n,i,j,k,a,su,b;
    while(scanf("%d",&n)!=EOF){
        if(n==0)
            break;
        for(i=0;i<n;i++)
            m[i]=0;//歸零
        for(i=0;i<=n;i++)
            s[i]=0;//歸零
        a=0;
        for(i=0;i<n;i++)
            scanf("%lld",&m[i]);//讀入平均數列
        for(i=m[0];;i--){
/*因為S數列非遞減 且 S0+S1=M0*2 所以S0<=M0<=S1，故S0最大可能值為M0。
  同理，S1最大可能值為M1,故當S1超過M1時不再有答案，故結束*/
            su=0;//假設S0=M0時不成立
            s[0]=i;
            for(j=1;j<=n;j++){//填入每個數。
                s[j]=m[j-1]*2-s[j-1];
                if(s[j-1]>m[j-1] || m[j-1]>s[j] || (s[j-1]+s[j])%2!=0){//檢查
                    su=0;
                    break;
/*1.由上可知S[K]<=M[K]<=S[K+1]
  2.m數列非整數數列，但輸入必為整數，故s[k]+s[k+1]必為偶數才能整除
  3.若以上任何一者成立表示不符合，故不成立，跳出迴圈，如果皆成立，則成立紀錄成立（su=1)
*/                }
                else
                    su=1;//填入的數代入且皆成立，則填下個數，若填入的每個數都成立，則進入下個迴圈
            }
            if(su==1){//紀錄成立的次數
                a++;
            }
            if(s[1]>m[1]){
                printf("m%d\n",m[1]);
                break;
            }
        }
    printf("%d\n",a);
    }
}
