#include<cstdio>
char step[2500];
main()
{
    int i,j,k,t,per,diff,perfect,great,good,boo,miss,combo,ss,cb,dp;
    char act,tmp[9];
    scanf("%d:%d %s",&i,&j,tmp);
    scanf("%s",step);
    t=i*60+j;
    for(i=j=0;step[i];i++)j+=(step[i]!='N');
    per=1000,diff=1000000/(j*(j+1)/2);
    if(tmp[0]=='M')diff=2000000/(j*(j+1)/2),t*=2,per=500;
    if(tmp[0]=='H')diff=3000000/(j*(j+1)/2),t*=4,per=250;
    perfect=great=good=boo=miss=combo=0;
    for(i=ss=cb=dp=k=0,j=-1;i<t;i++)
    {
        while(j<i*per)
            if(scanf("%d %s",&j,tmp)==EOF)
                j=t*per+1,tmp[0]='N';
        if(step[i]=='N')continue;
        k++;
        if(j<(i+1)*per)act=tmp[0];
        else act='N';
        if(act==step[i])
        {
            combo++;
            if(j<i*per+per*4/10)
            {
                perfect++;
                ss+=10*diff*k;
                cb+=55*combo;
                if(dp>=0)dp+=2;
            }
            else if(j<i*per+per*7/10)
            {
                great++;
                ss+=5*diff*k;
                cb+=33*combo;
                if(dp>=0)dp++;
            }
            else good++;
        }
        else
        {
            combo=0;
            if(act=='N')boo++,dp-=4;
            else miss++,dp-=5;
        }
    }
    printf("Perfect: %d\nGreat: %d\nGood: %d\n",perfect,great,good);
    printf("Boo: %d\nMiss: %d\n",boo,miss);
    puts("--------------------");
    printf("Stage Score: %d\n",ss);
    printf("Combo Bonus: %d\n",cb);
    if(great+good+boo+miss==0)j=10000000;
    else if(good+boo+miss==0)j=1000000;
    else if(dp>=k*8/5)j=100000;
    else if(dp>=k*32/25)j=10000;
    else if(dp>=k)j=1000;
    else if(dp>=0)j=100;
    else j=0;
    printf("Dance Level Bonus: %d\n",j);
    printf("Total Score: %d\n",ss+cb+j);
}
