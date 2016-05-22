#include<stdio.h>
#include<string.h>
main(){
    long base,i,j,n,k;
    char num1[17],num2[17],ch[20]={"0123456789ABCDEFGHI"};
    for(base=2;base<21;base++){
		printf("base: %d\n",base);
        for(k=1;k<=300;k++){
            n=k*k;
			for(j=16;n;j--){
                num1[j]=ch[n%base];
                n/=base;
            }
            for(i=0,j++;j<17;i++,j++)num1[i]=num1[j];
            num1[i]=num2[i]='\0';
			for(j=0;j<i;j++)num2[i-j-1]=num1[j];
            if(!strcmp(num1,num2))
                printf("%ld %s\n",k,num1);
        }
        gets(num1);
    }
}
