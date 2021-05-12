#include <sys/types.h> 
#include <sys/socket.h>
#include <sys/socket.h>
#include <sys/un.h>

int main()
{
  int return_value;
  const char *sock_path;
  struct sockaddr_un local;

  sock_path = "/data/local/tmp/mysocket";

  int sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("socket");
    exit(-1);
  }

  local.sun_family = AF_UNIX;
  strcpy(local.sun_path, sock_path);
  unlink(local.sun_path);
  int len = strlen(local.sun_path) + sizeof(local.sun_family);
  bind(sockfd, (struct sockaddr *)&local, len);

  chmod(sock_path, 0777);

  int retval = listen(sockfd,1);
  if (retval == -1)
  {
    perror("listen");
    exit(-1);
  }
}
