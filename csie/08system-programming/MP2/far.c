#include<time.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
typedef struct dirent dirent;
extern char *str,*new;
void errmes(char[]);
void ins(int);
char find(int);
void replace(char[],char[],char[]);

void print_info(char name[])
{
	struct stat dat;
	if(lstat(name,&dat)<0)
	{
		errmes(name);
		return;
	}
	printf("  ");
	static char type[]="DCBRLSI?",perm[]="rwxrwxrwx";
	static int tc[]={S_IFDIR,S_IFCHR,S_IFBLK,S_IFREG,S_IFLNK,S_IFSOCK,S_IFIFO}
	,pc[]={S_IRUSR,S_IWUSR,S_IXUSR,S_IRGRP,S_IWGRP,S_IXGRP,S_IROTH,S_IWOTH,
		S_IXOTH};
	int i;
	for(i=0;(S_IFMT&dat.st_mode)!=tc[i] && i<7;i++);
	putchar(type[i]);
	for(i=0;i<9;i++)
		if(dat.st_mode&pc[i])
			putchar(perm[i]);
		else
			putchar('-');
	char tmp[50];
	strcpy(tmp,ctime(&dat.st_mtime));
	tmp[strlen(tmp)-1]=0;
	printf(" %s %6ld (%d/%d)\n",tmp,dat.st_size,
		major(dat.st_dev),minor(dat.st_dev));
}
void go()
{
	DIR *D=opendir(".");
	if(!D)return;
	dirent *ptr=readdir(D);
	char x,cwd[PATH_MAX+2],name[PATH_MAX+2];
	if(find(ptr->d_ino))return;	//check if the dir. is already visited
	ins(ptr->d_ino);	
	getcwd(cwd,PATH_MAX);		
	readdir(D);					//ignore ".."
	while(ptr=readdir(D))
	{
		x=(chdir(ptr->d_name)>=0);
		chdir(cwd);
		if(strxstr(ptr->d_name,str))
		{
			printf("%s/%s\n",getcwd(name,PATH_MAX+1),ptr->d_name);
			print_info(ptr->d_name);
			strcpy(name,ptr->d_name);
			if(!x && new)
			{
				replace(name,str,new);
				FILE *fp=fopen(name,"rb");
				if(fp)
				{
					fclose(fp);
					fprintf(stderr,"Error: file overwriting!\n");
				}
				else rename(ptr->d_name,name);
			}
		}
		if(x)
		{
			chdir(ptr->d_name);
			go();
			chdir(cwd);
		}
	}
	if(closedir(D))errmes("closedir");
}
void far(char path[])
{
	if(chdir(path)<0)			
	{
		errmes(path);
		return;
	}
	go();
}
