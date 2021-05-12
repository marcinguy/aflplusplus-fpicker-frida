# aflplusplus-fpicker-frida

Binaries and so files are aarch64

Start frida server, copy libandroid-shmem.so to re.frida.server

Run with run.sh

P.S You might need to create socket in /data/local/tmp/mysocket

```
heroltexx:/data/local/tmp # ls -la mysocket                                    
srwxrwxrwx 1 root root 0 2021-05-10 15:37 mysocket
heroltexx:/data/local/tmp # 
```

I think if you create a file and chnage the permissions (0777) it should be sufficient. If not try to run this, it should create it:

```
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

```

## aarch64

set CC to NDK compiler (aarch64)

Make afl (AFLplusplus-aarch64) with 

```
make all AFL_NO_X86=1
```

Make fpicker with (did in chroot linux env - termux)

```
make fpicker-linux 

```

## x86_64


set CC to NDK compiler (x86_64)

Make afl (AFLplusplus-x86_64) with 

```
make all AFL_NO_X86=1

```
Make fpicker with (did in chroot linux env - termux) (Not working yet)

```
make fpicker-linux 

```

For fpicker a NDK Andoird Project would be better. Maybe also for AFL++. VS building from chroot Clang12 (termux)







