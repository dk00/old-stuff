#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
ssize_t n;
char *buf;
typedef struct _
{
	ssize_t len;
	char *buf;
	struct _ *next;
}node;
node *p;
int atomic_log_open(char name[])
{
	return open(name,O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
}
ssize_t log_string(char mes[])
{   //use linked list to store the log strings
	node *ptr=malloc(sizeof(node));
	if(!ptr)
    {
        fprintf(stderr,"Insufficent memory\n");
        return -1;
    }
	ptr->next=p;
	p=ptr;
	p->len=0;
	p->buf=malloc(p->len=strlen(mes));
	if(!p->buf)
    {
        fprintf(stderr,"Insufficent memory\n");
        return -1;
    }
	n+=p->len;
	memcpy(p->buf,mes,p->len);
	return p->len;
}
ssize_t atomic_log_send(int fd)
{
	char *buf=malloc(n);
	if(!buf)
	{
        fprintf(stderr,"Insufficent memory\n");
        return -1;
    }
	node *tmp;
	ssize_t m=n;
	for(;p;p=tmp)
	{
		memcpy(buf+m-p->len,p->buf,p->len);
		tmp=p->next;
		m-=p->len;
		free(p);
	}
    m=(write(fd,buf,n)==n)?n:-1;
    free(buf);
	return m;
}
