#include <stdio.h>
#include "06fin4.h"
int main(){
	int i;
	Date day;
	initDate(&day, 1099, 1, 30);
	while(1) {
		printDate(&day);
		nextDate(&day);
		scanf("%d",&i);
	}
}
