#include<map>
#include<ctime>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<cstring>
#include<fcntl.h>
#include<unistd.h>
#include<dirent.h>
#include<netinet/in.h>
#include<sys/socket.h>
using namespace std;

class Server
{
  public:
    Server(){

    }
    ~Server(){
      if (socket_des != -1)
        close(socket_des);
    }

    // Initialize & start the server
    int Init(int port,int max_accept=8){
      socket_des = socket(AF_INET,SOCK_STREAM,0);
      if (socket_des < 0) {
        perror("socket");
        return -1;
      }
      sockaddr_in socket_address;
      socket_address.sin_family = AF_INET;
      socket_address.sin_port = htons(port);
      socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
      if (bind(socket_des,(sockaddr *)&socket_address,
               sizeof(socket_address)) < 0) {
        perror("bind");
        return -1;
      }
      if (listen(socket_des,max_accept) < 0) {
        perror("listen");
        return -1;
      }      
      return 0;
    }

    //Wait for a client and accept
    int Accept(){
      sockaddr client_address;
      int client_des;
      socklen_t client_address_size;
      client_des =
      accept(socket_des,&client_address,&client_address_size);
      if (client_des < 0) {
        perror("accept");
        return -1;
      }
      return client_des;
    }
  private:
    int socket_des;
};

const int kMaxLen = 512;

// initialize file types
map<string,string>& InitType()
{
  map<string,string> *type = new map<string,string>;
  char ext[kMaxLen],type_s[kMaxLen];
  (*type)["default"] = "text/plain";
  FILE *fp=fopen(".types","r");
  if (fp == NULL)
    return *type;
  while (fscanf(fp,"%s %s",&ext,&type_s) == 2)
    (*type)[ext] = type_s;
  fclose(fp);
  return *type;
}

// determine Content-type
const char *GetType(const char file_name[])
{
  static map<string,string>& type = InitType();
  int i;  
  for(i=strlen(file_name)-1;i >= 0 && file_name[i]!='.' && file_name[i]!='/';i--);
  const char *ext_name = file_name + i;
  if (type.count(ext_name) > 0)
    return type[ext_name].c_str();
  return type["default"].c_str();
}

// decode %-encoded string
int DecodeURN(const char urn[],char file_name[]){
  int i, j, k;
  sprintf(file_name,"htdocs");
  for (i = 0,j = 6;urn[i] != 0;i++) {
    if (urn[i] != '%')
      file_name[j++] = urn[i];
    else {
      if (sscanf(urn + i + 1,"%02X",&k) == 1) {
        file_name[j++] = k;
        i+=2;
      }
      else {
        return -1;
      }
    }
  }
  file_name[j] = 0;
  if (file_name[6] != '/')
    return -1;
  return 1;
}

// Validate the path
bool Valid(char path[]){
  int len = strlen(path),fd = -1;
  DIR *dirent = opendir(path);
  if (dirent == NULL) 
    fd = open(path,O_RDONLY);
  else {
    closedir(dirent);
    if (path[len-1] != '/') path[len++ - 1] = '/';
    sprintf(path + len,"index.htm");
    fd = open(path,O_RDONLY);
    if (fd < 0) {
      sprintf(path + len,"index.html");
      fd = open(path,O_RDONLY);
    }
    fflush(stdout);
  }
  if (fd < 0) return false;
  close(fd);
  return true;
}

// Send file infomation and content to client
int SendFile(FILE *header_out,int data_out,const char file_path[],
             int send_content = 1){
  struct stat stat_buf;
  if (stat(file_path,&stat_buf) < 0) {
    perror("stat");
    return -1;
  }
  int fd = open(file_path,O_RDONLY);
  if (fd < 0) {
    perror("open");
    return -1;
  }
  const int kBufSize = 4096;
  char buf[kBufSize];
  time_t now = time(NULL);
  strftime(buf,kBufSize,"%a, %d %b %Y %T GMT",gmtime(&now));
  fprintf(header_out,"Date: %s\r\n",buf);
  strftime(buf,kBufSize,"%a, %d %b %Y %T GMT",gmtime(&stat_buf.st_mtime));
  fprintf(header_out,"Last-Modified: %s\r\n",buf);
  fprintf(header_out,"Content-Length: %d\r\n",stat_buf.st_size);
  fprintf(header_out,"Content-Type: %s\r\n\r\n",GetType(file_path));
  fflush(header_out);
  if (send_content != 1) return 0;
  int num_read;  
  while ((num_read = read(fd,buf,kBufSize)) > 0)
    write(data_out,buf,num_read);
  close(fd);
  return 0;
}

// Responce to clints
int Responce(int client_des) {
  FILE *client_in = fdopen(client_des,"r"),
       *client_out = fdopen(dup(client_des),"w");
  if (client_in == NULL || client_out == NULL) return -1;
  char method[kMaxLen],urn[kMaxLen],http_ver[kMaxLen],file_path[kMaxLen];
  fscanf(client_in,"%s %s %s",method,urn,http_ver);
  printf("Request: %s %s %s\n",method,urn,http_ver);
  if (strcmp(method,"GET") != 0 && strcmp(method,"HEAD") != 0) {
    fprintf(client_out,"HTTP/1.0 501 Method Not Implemented\r\n");
    SendFile(client_out,client_des,"501.html",1);
  } else if (DecodeURN(urn,file_path) != 1) {
    fprintf(client_out,"HTTP/1.0 401 Bad Request\r\n");
    SendFile(client_out,client_des,"401.html",1);
  } else if (Valid(file_path)) {
    fprintf(client_out,"HTTP/1.0 200 OK\r\n");
    SendFile(client_out,client_des,file_path,strcmp(method,"GET") == 0);
  } else {
    fprintf(client_out,"HTTP/1.0 404 Not Found\r\n");
    SendFile(client_out,client_des,"404.html",1);
  }
  fclose(client_in);
  fclose(client_out);
}

main(int an,char **arg) {
  Server s0;
  int port=6666;
  if (an > 1 && sscanf(arg[1],"%d",&port) != 1) 
    port=6666;
  printf("Using port %d\n",port);
  if (s0.Init(port) < 0) return 0;
  while (1) {
    int client_des = s0.Accept();
    if (client_des < 0) break;
    if (Responce(client_des) < 0) break;
  }
  return 0;
}
