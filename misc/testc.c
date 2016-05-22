/*Assignment 3 Problem 1*/

#include <stdio.h>

int main(void)
{
	int input[1000];
	int size;

	int hold;
	int stop;
	int times;
    int flag;
	int i;
	int j;

	times=0;
	scanf("%d", &size);
	for(i=0; i<size; i++){
		scanf("%d", &input[i]);
		
	}

	while(1)
	{
		for(j=0; j<size-1; j++){
            flag=0;
			for(i=0; i<size-1; i++){
				if(input[i]>input[i+1]){
					hold=input[i];
					input[i]=input[i+1];
					input[i+1]=hold;

					times=times+1;
					flag=1;
				}
			}
			if(flag==0)break;
		}

        
		printf("%d\n", times);
		
        times=0;

        if((stop = getchar()) == EOF)break;

		scanf("%d", &size);
		for(i=0; i<size; i++){
			scanf("%d", &input[i]);

		}
        

	}
	return 0;
}


