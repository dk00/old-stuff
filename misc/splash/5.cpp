#include<stdio.h>
long long int s[5000001],m[5000000];
main(){
    int n,i,j,k,a,su,b;
    while(scanf("%d",&n)!=EOF){
        if(n==0)
            break;
        for(i=0;i<n;i++)
            m[i]=0;//�k�s
        for(i=0;i<=n;i++)
            s[i]=0;//�k�s
        a=0;
        for(i=0;i<n;i++)
            scanf("%lld",&m[i]);//Ū�J�����ƦC
        for(i=m[0];;i--){
/*�]��S�ƦC�D���� �B S0+S1=M0*2 �ҥHS0<=M0<=S1�A�GS0�̤j�i��Ȭ�M0�C
  �P�z�AS1�̤j�i��Ȭ�M1,�G��S1�W�LM1�ɤ��A�����סA�G����*/
            su=0;//���]S0=M0�ɤ�����
            s[0]=i;
            for(j=1;j<=n;j++){//��J�C�ӼơC
                s[j]=m[j-1]*2-s[j-1];
                if(s[j-1]>m[j-1] || m[j-1]>s[j] || (s[j-1]+s[j])%2!=0){//�ˬd
                    su=0;
                    break;
/*1.�ѤW�i��S[K]<=M[K]<=S[K+1]
  2.m�ƦC�D��ƼƦC�A����J������ơA�Gs[k]+s[k+1]�������Ƥ~��㰣
  3.�Y�H�W����@�̦��ߪ�ܤ��ŦX�A�G�����ߡA���X�j��A�p�G�Ҧ��ߡA�h���߬������ߡ]su=1)
*/                }
                else
                    su=1;//��J���ƥN�J�B�Ҧ��ߡA�h��U�ӼơA�Y��J���C�ӼƳ����ߡA�h�i�J�U�Ӱj��
            }
            if(su==1){//�������ߪ�����
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
