//�Ʊ�T�رƧǳ���ݤ@��,�M��g�@�g,�W�[�� C �y�k�����x��
//�]�i�H�V�m��j�骺�ϥ�,����g�� 3 �����@�رƧǬO�̦n��
//�H�᪺��,�u�n�|�T�ؤ������@�ӴN�i�H�F

/*
��w�Ƨ� (Bubble Sort)

�t��k:
s[0] �P s[1] ���,��j����� s[1];
s[1] �P s[2] ���,��j����� s[2];
s[2] �P s[3] ���,��j����� s[3];
......���_����......
s[n-1] �P s[n] ��,��j����� s[n];
�o�Ӯɭԥi�H�T�w:�̤j�̤j���Ȥw�g��� s[n] ���F.
�ڭ̦p�G�A���@�w�W�����B�J,�i�H�A�⦸�j����� s[n-1] �̭�,
���`�@�� n �Ӽƭn�Ƨ�,�ҥH�o�ǨB�E�������� n ��.

���� n ��:  i �j��
�洫���B�J: j �j��
*/
#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
        printf("�п�J���X�ӼƦr�n�Ƨ�(Sort): ");
        if(scanf("%d",&n)==EOF)         //n �O�N���X�ӼƦr�n�Ƨ�,CTRL+Z �i�H���X
            break;
        printf("�п�J %d �ӼƦr: ",n);
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);          //�o�̭n��J n �ӼƦr���@�U�n�ƧǥΪ�
        for(i=0;i<n;i++)
            for(j=1;j<n;j++)            //��h�j��i���w�Ƨ�
                if(s[j]<s[j-1]){        //�p�G�e�����p��᭱��,�N�洫
                    t=s[j];             //�洫:�Ԩ��̤U��
                    s[j]=s[j-1];
                    s[j-1]=t;
                }
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");                       //puts("") �N�䵥�� printf("\n") �N�O����
    }
}
/*
����洫 a �M b,�ڭ̥����Τ@���{���ܼ� (t) ������,
1) t=a  2) a=b  3) b=t(=���e�� a)
�p�G�S�����O t=a ����,�b�ĤG�B a=b ��,a ���ȴN�û��S���H���D�O�h�֤F,
�|�Ө�,a=10,b=20,�{�b�n�� a �M b �洫:
1) t=a=10 ==> t=10
2) a=b=20 ==> a=20
3) b=t=10 ==> b=10
�����᪺���G�O a=20,b=10,��̦��\�洫�F.
*/

/*
�A�ӽФj�a�ݤ@�U�{�������c,�̭��|�G�N���h�ť�,
�o�O���F��K�\Ū�Ӱ�����,�@�}�l�ڤ]�O�����D���̸Ӫŭ��̤���,
����ӷ|�C�C�F��,�ߺD����,�ݵ{���u���M���\�h,
�{�b�H�W���� Code �|�һ������̭n�ť� (�ťեi�� TAB ��):

1) �@�}�l�O�����S���ťժ����p

#include <stdio.h>
main(){
int i,j,t,n,s[1000];
while(1){
printf("�п�J���X�ӼƦr�n�Ƨ�(Sort): ");
if(scanf("%d",&n)==EOF)
break;
printf("�п�J %d �ӼƦr: ",n);
for(i=0;i<n;i++)
scanf("%d",&s[i]); 
for(i=0;i<n;i++)
for(j=1;j<n;j++)
if(s[j]<s[j-1]){
t=s[j];
s[j]=s[j-1];
s[j-1]=t;
}
for(i=0;i<n;i++)
printf("%d ",s[i]);
puts("");
}
}

2) �ڭ̥��o�{,�Ҧ����{��,���O�b main(){...} ����,�ҥH��̭����F�詹���Y

#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
    printf("�п�J���X�ӼƦr�n�Ƨ�(Sort): ");
    if(scanf("%d",&n)==EOF)
    break;
    printf("�п�J %d �ӼƦr: ",n);
    for(i=0;i<n;i++)
    scanf("%d",&s[i]);
    for(i=0;i<n;i++)
    for(j=1;j<n;j++)
    if(s[j]<s[j-1]){
    t=s[j];
    s[j]=s[j-1];
    s[j-1]=t;
    }
    for(i=0;i<n;i++)
    printf("%d ",s[i]);
    puts("");
    }
}

3) �A�o�{�j�������{���O�b while(1){...} �̭�,��O�A��̭��������Y

#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
        printf("�п�J���X�ӼƦr�n�Ƨ�(Sort): ");
        if(scanf("%d",&n)==EOF)
        break;
        printf("�п�J %d �ӼƦr: ",n);
        for(i=0;i<n;i++)
        scanf("%d",&s[i]);
        for(i=0;i<n;i++)
        for(j=1;j<n;j++)
        if(s[j]<s[j-1]){
        t=s[j];
        s[j]=s[j-1];
        s[j-1]=t;
        }
        for(i=0;i<n;i++)
        printf("%d ",s[i]);
        puts("");
    }
}

4) break; �o�@��O�ݩ� if(...) ��,�ҥH�V���Y
   scanf("%d",&s[i]); �ݩ� for �j��,�]�����Y
   �̤U���� printf("%d ",s[i]); �P�z���V���Y

#include <stdio.h>
main(){
    int i,j,t,n,s[1000];
    while(1){
        printf("�п�J���X�ӼƦr�n�Ƨ�(Sort): ");
        if(scanf("%d",&n)==EOF)
            break;
        printf("�п�J %d �ӼƦr: ",n);
        for(i=0;i<n;i++)
            scanf("%d",&s[i]);
        for(i=0;i<n;i++)
        for(j=1;j<n;j++)
        if(s[j]<s[j-1]){
        t=s[j];
        s[j]=s[j-1];
        s[j-1]=t;
        }
        for(i=0;i<n;i++)
            printf("%d ",s[i]);
        puts("");
    }
}

5) �̫�ڭ̳B�z�o�@�����������:
        for(i=0;i<n;i++)
        for(j=1;j<n;j++)
        if(s[j]<s[j-1]){
        t=s[j];
        s[j]=s[j-1];
        s[j-1]=t;
        }
   �o�̬O��� for �|�b�@�_,�A�[�@�� if,
   �N��O�o��: if �ݩ�ĤG�� for,�ӲĤG�� for �S�ݩ�Ĥ@�� for
   ���N�i�H�ഫ��:
        for(i=0;i<n;i++)
            for(j=1;j<n;j++)
                if(s[j]<s[j-1]){
                    t=s[j];
                    s[j]=s[j-1];
                    s[j-1]=t;
                }
                
6) �N�O�o�˦Ӥw,�o�ܭ��n,�D~�D~�D�`���n!
   ��ĳ�j�a�i�H��t�~��� Code ���Y�ƧR��,�M��ۤv�ոլ�...
