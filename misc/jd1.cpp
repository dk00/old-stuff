#include<map>
#include<ctime>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<csignal>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/resource.h>
#include"sqlitedb.h"
using namespace std;
const int sign[]={SIGABRT,SIGALRM,SIGBUS,SIGCHLD,SIGCONT,SIGFPE,SIGHUP,
SIGILL,SIGINT,SIGKILL,SIGPIPE,SIGQUIT,SIGSEGV,SIGSTOP,SIGTERM,SIGTSTP,
SIGTTIN,SIGTTOU,SIGUSR1,SIGUSR2,SIGPOLL,SIGPROF,SIGSYS,SIGTRAP,SIGURG,
SIGVTALRM,SIGXCPU,SIGXFSZ};
const char sigstr[][20]={"SIGABRT","SIGALRM","SIGBUS","SIGCHLD","SIGCONT",
"SIGFPE","SIGHUP","SIGILL","SIGINT","SIGKILL","SIGPIPE","SIGQUIT",
"SIGSEGV","SIGSTOP","SIGTERM","SIGTSTP","SIGTTIN","SIGTTOU","SIGUSR1",
"SIGUSR2","SIGPOLL","SIGPROF","SIGSYS","SIGTRAP","SIGURG","SIGVTALRM",
"SIGXCPU","SIGXFSZ"};
const int Mbase=11555;
int get(sqlitedb& db,int& id,int& uid,int& pid,string& make)
{
    map<string,string> r;
    if(db.query("select id,pid,uid,lang from sub where res=\'Being Judged\' order by id limit 1",r))return 0;
	if(sscanf(r["id"].c_str(),"%d",&id)!=1)return 0;
	printf("%d\n",id);
    sscanf(r["uid"].c_str(),"%d",&uid);
    sscanf(r["pid"].c_str(),"%d",&pid);
    if(r["lang"]=="C")make="gcc";
    else if(r["lang"]=="C++")make="g++";
	return 1;
}
int count()
{
}
char tmp[999];
int id,uid,pid;
int result(sqlitedb& db,string res,int cpu=0)
{
	printf("Result: %s\nCPU time: %2d.%03d\n",res.c_str(),cpu/1000,cpu%1000);
    sprintf(tmp,"update sub set res=\'%s\',cpu=%d where id=%d",res.c_str(),cpu,id);
	//return 1;
	map<string,string> h;
    db.query(tmp,h);
    if(res=="Accepted")
    {
		sprintf(tmp,"update prob set acc=acc+1 where id=%d",pid);
		db.query(tmp,h);
    }
}
string getext(string make)
{
    if(make=="gcc")
        return "c";
    if(make=="g++");
        return "cpp";
    return "";
}
int run(const char exe[],const char in[],const char out[],const char spc[],int tl,int ml,string& res)
{
    ml+=Mbase;
    int p0,p1,p2,tu=0;
    if(p1=fork())
    {
        if(p2=fork())
        {
            int st1,st2;
            rusage ru;
            p0=wait3(&st1,0,&ru);
            if(p0==p1)
                wait(&st2);
            else
                st2=st1,wait3(&st1,0,&ru);
			tu+=ru.ru_utime.tv_sec*1000+ru.ru_utime.tv_usec/1000
				+ru.ru_stime.tv_sec*1000+ru.ru_stime.tv_usec/1000;
            if(WIFEXITED(st1))
            {
                if(WIFEXITED(st2))
                {
                    if(tu>tl)
						res="Time Limit Exceeded";
					else if(WEXITSTATUS(st2))
                        res="Wrong Answer";
					else
                        res="Accepted";
                }
                else res="System Error";
            }
            else if(WIFSIGNALED(st1))
            {
                int i,x=WTERMSIG(st1);
                for(i=0;i<28;i++)
                    if(sign[i]==x)break;
                if(i<28)
                    sprintf(tmp,"Runtime Error(%s)",sigstr[i]);
                else
                    sprintf(tmp,"Runtime Error(%d)",x);
                res=tmp;
                if(x==SIGXCPU)
                    res="Time Limit Exceeded";
                if(x==SIGKILL)
                    res="Memory Limit Exceeded";
            }
            else res="Undefined Error";
        }
        else            //matcher
        {
            int i,n,m,st=0;
            char buf0[4097],buf1[4097];
            freopen("tmp","rb",stdin);
            sprintf(buf0,"%04d/%s",pid,out);
            FILE *fp=fopen(buf0,"rb");
            while(!st)
            {
                n=fread(buf0,1,4096,fp);
                m=fread(buf1,1,4096,stdin);
				if(n!=m)
                	{st=1;break;}
				if(!n)break;
                for(i=0;i<n;i++)
                    if(buf0[i]!=buf1[i]){st=1;break;}
            }
            exit(st);
        }
    }
    else                //child
    {
        setrlimit(RLIMIT_CPU,&(rlimit){(tl+999)/1000+1,(tl+999)/1000+2});
        setrlimit(RLIMIT_AS,&(rlimit){ml*1024,ml*1024-1});
        sprintf(tmp,"%04d/%s",pid,in);
        freopen(tmp,"r",stdin);
        freopen("tmp","w",stdout);
        execl("./a.out",0);
    }
}
int judge0(const char exe[],const char cfg[],string& res)
{
    FILE *fp=fopen(cfg,"r");
    fscanf(fp,"%*d %d %d",&tl,&ml);
    puts("Type: batch");
	printf("Time Limit: %2d.%03d sec\n",cl/1000,cl%1000);
	printf("Memory Limit: %6d kb\n",ml);
    char in[99],out[99];
    tu=0;
    res="Accepted";
    while(res=="Accepted" && fscanf(fp,"%s %s",in,out)==2)
        tu+=run(exe,in,out,NULL,cl-tu,ml,res);
    fclose(fp);
    return tu;
}
void judge(const char exe[],string& res,int& tu)
{
    sprintf(tmp,"%04d/judge",pid);
    FILE *fp=fopen(tmp,"r");
    if(!fp)
    {
		puts("Judge config file not found.");
        res="Cant be judged";
        return;
    }
    int type,cl,ml;
    fscanf(fp,"%d ",&type);
    fclose(fp);
    if(type==0)
        tu==judge0(exe,tmp,res);
    else if(type==1)
        tu==judge1(exe,tmp,res);
    else
    {
        res="Cannot be judged";
        return;
    }
}

main(int _m,char **_c)
{
	int t=15,re=50;
	if(_m>1)
		sscanf(_c[1],"%d",&t);
	sqlitedb db("../judgedb");
	while(t)
	{
        string make="";
        if(!get(db,id,uid,pid,make))
		{
			usleep(50000);
            continue;
			if(!re--)
			{
				re=50;
				db.reopen();
			}
		}
		t--;
		puts("-----------------------------------");
		printf("Fetched submission %d\n",id);
		printf("User ID: %d\t",uid);
		printf("Problem ID: %d\n",pid);
		if(make=="")
		{
            puts("Cannot Compile");
            continue;
        }
		printf("Use %s to compile\n",make.c_str());
        FILE *fp=fopen("a.out","r");
        if(fp)
        {
            fclose(fp);
            system("rm a.out");
        }
		puts("Compiling...");
        sprintf(tmp,"./jm %s ../sub/%d.%s|tee .log/%d.log",
        make.c_str(),id,getext(make).c_str(),id);
        system(tmp);
        fp=fopen("a.out","r");
        if(fp)fclose(fp);
        else
        {
            result(db,"Compile Error");
            continue;
        }
		puts(" OK");
        string res;
        int cpu=0;
		puts("Running Judge");
        judge("a.out",res,cpu);
		result(db,res,cpu);
		db.reopen();
	}
}
