#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char *str="",*new,map[256][256];
void clean();
void far(char[]);
void errmes(char mes[])
{
	fprintf(stderr,"far: %s : %s\n",mes,strerror(errno));
}
void usage_exit()
{
	printf("Usage: starting_search_point [OPTION]\nSearch for files in a directory hierachy whose filenames contain a given string.\n\nOptions:\n  -s <SearchingString>          The substring for searching filenames.\n  -r <NewString>                The string to replace with SearchingString.\n  -as <AdvancedSearchingString> Regard the symbol \'?\' in AdvancedSearchingString                                as all alphabet while searching\n  -b                            The searching is not case-sensitive.\n");
	exit(0);
}
main(int m,char *a[])
{
	{	//Options
		int i,n_s=0,n_r=0,n_as=0,b=0;
		for(i=2;i<m;i++)
		{
			if(!strcmp(a[i],"-s"))
				n_s++,str=a[++i];
			else if(!strcmp(a[i],"-r"))
				n_r++,new=a[++i];
			else if(!strcmp(a[i],"-as"))
				n_as++,str=a[++i];
			else if(!strcmp(a[i],"-b"))
				for(i=0;i<26;i++)
					map['A'+i]['a'+i]=map['a'+i]['A'+i]=1;
			else
				fprintf(stderr,"far: unrecongnized command line option \"%s\"\n",a[i]);
		}
		for(i='A';i<='Z';i++)
			map[i][i]=map[i]['?']=map['?'][i]=1;
		for(i='a';i<='z';i++)
			map[i][i]=map[i]['?']=map['?'][i]=1;
		for(i=0;i<256;i++)
			map[i][i]=1;
		if(n_s+n_as<1)
			usage_exit();
		else if(n_s+n_as>1)
			fprintf(stderr,"warning: More than one (Advanced)SearchingString specified, only the last one will be processed.\n");
		if(n_r>1)
			fprintf(stderr,"warning: More than one NewString specified, only the last one will be processed.\n");
	}
	far(a[1]);
	clean();
}
