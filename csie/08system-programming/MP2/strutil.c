#include<stdlib.h>
#include<string.h>
extern char map[256][256];
char strxcmp(char a[],char b[],int n)
{
	int i;
	for(i=0;a[i] && b[i] && i<n;i++)
		if(!map[a[i]][b[i]])return 1;
	return i<n;
}
char strxstr(char s[],char str[])
{
	int i,n=strlen(s),n1=strlen(str);
	for(i=0;s[i];i++)
		if(!strxcmp(s+i,str,n1))
			return 1;
	return 0;
}
void replace(char s[],char str[],char new[])
{
	int i,j,n=strlen(s),n1=strlen(str),n2=strlen(new);
	char *o=malloc(strlen(s)+1);
	strcpy(o,s);
	for(i=j=0;n-i>=n1 && o[i];i++,j++)
		if(!strxcmp(o+i,str,n1))
		{
			i+=n1-1;
			strcpy(s+j,new);
			j+=n2-1;
		}
		else s[j]=o[i];
	free(o);
}
