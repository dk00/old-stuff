/*
���J�Ƨ� (Insertion Sort)

�����|�һ�����k:
0) ���]��J 5 9 7 1
1) �@�}�l s[] �O�Ū�,�{�b�W�[ 5: s[]=5
2) �A�ӼW�[ 9,�ڭ̵o�{ 9 �� 5 �j�ҥH�W�[�b 5 ���᭱: s[]=5 9
3) �W�[ 7 �ɵo�{ 5<7<9,�������b 5 9 ����,�ҥH�� 9 ���h�@��,�A���J 7: s[]=5 7 9
4) �[�J 1,�]�� 1<5,�� 5 7 9 �����Ჾ�@��,�A��J 1: s[]=1 5 7 9
*/
#include <stdio.h>
main(){
    int i,j,k,t,n,s[1000];
    while(scanf("%d",&n)!=EOF){
        for(i=0;i<n;i++){
            scanf("%d",&k);
            for(j=i;j>=0;j--)   //�p�G�n���J���F��w�g��}�C�����Ȥj�F,�N���X
                if(k>s[j])      //�Ҧp�W�����ĤT�B,���� 7 �� 5 �j�ɸ��X
                    break;
            t=j+1;              //t �O�n���J����l
            for(j=i;j>t;j--)    //�ҥH������ t �᭱���F��V�Ჾ
                s[j]=s[j-1];
            s[t]=k;             //���J t
        }
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");
    }
}
