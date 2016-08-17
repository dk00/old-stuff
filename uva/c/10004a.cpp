/*
Q10004 Bicoloring
�򥻷Q�k:
    1.�u������C��A�ӥB�۾F���I�C�⥲�����P�A�ҥH�T�w�@���I���C�⤧��
    �M�L�۾F���I�N��W�t�@���C��C
    2.���Ҧ����Ѫk�A�����C�⴫�L�Ӥ���A�]�O�i�Ϊ��ѡA�o��ܧڭ�
    �Ĥ@�ӿ諸�I�A�C��ä����n�C
*/
#include<stdio.h>
int n,v[200],c[200][200];
/*
note:
    �J��w�g���L���I�A�u�n�P�_�C��藍��Y�i�A���ΦA�V�U�j�M�A
    �o�Ӯɭԥi�H�� return �����o�� function�C
    �S�����L���I�h�ФW�C��A�A���U�j�C
*/
int dfs(int s,int color)    // �p�G�i�H���ܦ^�� 1, �_�h 0
{
    if(v[s])                 // v[s] ���O 0, ��ܤw�g�ۦ�F
    {
        if(v[s]==color)return 1; // �p�G�L���C��M�{�b�n�Ϊ��C��@��
        return 0;                // �N��ܥi�H�A�_�h����
    }                            // �o���I�w�g���L�F�A�ҥH���ΦA���U�h
    v[s]=color;                  // ���C��
    for(int i=0;i<n;i++)
        if(c[s][i]==1)           // �H�t�@���C��b�۾F���I�ۦ�
            if(dfs(i,-color)==0) // �p�G���檺�ܴN�^�� 0
                return 0;
   return 1;    //�p�G���i�H���ܦ^�� 1
}
main()
{
    int i,j,m;
    while(scanf("%d %d",&n,&m) && n)
    {
        for(i=0;i<n;i++)         // �o�̥���Ҧ����ƭ��k�s
        {
            v[i]=0;              // v[i]�N���I i ���C��A0 ��ܩ|���ۦ�
            for(j=0;j<n;j++)     // 1, -1 �N���ؤ��P���C��
                c[i][j]=0;       // c[i][j] �N�� i,j �����O�_����s�b
        }                        // 1 -> ��, 0 -> �L
        while(m--)
        {
            scanf("%d %d",&i,&j);
            c[i][j]=c[j][i]=1;
        }
        if(dfs(0,1))puts("BICOLORABLE.");
        else puts("NOT BICOLORABLE.");
    }
}
