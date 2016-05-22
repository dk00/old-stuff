void rename(char s[],char str[],char new[])
{
	int i,j,k,n=strlen(s),n1=strlen(str),n2=strlen(new);
	char *o=malloc(strlen(s)+1);
	strcpy(o,s);
	for(i=j=0;o[i];i++,j++)
		if(!strncmp(o+i,str,(n1<n-i?n1:n-i)))
		{
			i+=n1-1;
			strcpy(s+j,new);
			j+=n2-1;
		}
		else s[j]=o[i];
}
char s[999],s1[99],s2[99];
main()
{
	while(scanf("%s %s %s",s,s1,s2)==3)
	{
		rename(s,s1,s2);
		puts(s);
	}
}
