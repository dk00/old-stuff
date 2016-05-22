#include<cstdio>
#include<cstdlib>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/socket.h>

class RequestReader
{
  public:
    RequestReader(){

    }

    ~RequestReader(){
      if (socket_descriptor != -1)
        close(socket_descriptor);
    }

    int Init(int port){
      socket_descriptor = socket(AF_INET,SOCK_STREAM,0);
      if (socket_descriptor < 0) {
        perror("socket");
        return -1;
      }
      sockaddr_in socket_address;
      socket_address.sin_family = AF_INET;
      socket_address.sin_port = htons(port);
      socket_address.sin_addr.s_addr = htonl(INADDR_ANY);
      if (bind(socket_descriptor,&socket_address,sizeof(socket_address)) < 0) {
        perror("bind");
        return -1;
      }
      return 0;
    }

    int GetRequest(int max_accept=1024){
      if (listen(socket_descriptor,max_accept) < 0) {
        perror("listen");
        return -1;
      }
      sockaddr client_address;
      int client_address_size,client_descriptor;
      client_descriptor=accept(socket_descriptor,&client_address,
                               &client_address_size);
      if (client_descriptor < 0) {
        perror("accept");
        return -1;
      }
      return client_descriptor;
    }

  private:
    int socket_descriptor;
}


int Parse(int client_descriptor) {
  const kMaxLen=512;
  FILE *client=fdopen(client_descriptor,"r");
  char method[kMaxLen],uri[kMaxLen];
  sscanf(client,"%s %s",method,uri);

}

main(int an,char **arg) {
  RequestReader reader0;
  if (reader0.Init() < 0) return 0;
  while (1) {
    int client_descriptor = reader0.GetRequest();
    Parse(client_descriptor);
  }
}
