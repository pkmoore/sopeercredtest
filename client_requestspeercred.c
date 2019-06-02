#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>


int main() {
  int sockfd;
  if(-1 == (sockfd = socket(AF_UNIX, SOCK_STREAM, 0))) {
    perror("socket creation failed");
  }
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, "/tmp/testsocket");

  if(-1 == connect(sockfd, (struct sockaddr*)&addr, sizeof(addr))) {
    perror("connect failed");
  }

  struct ucred peercredbuf;
  socklen_t opt_length = sizeof(peercredbuf);
  int gso_result;
  if(-1 == (gso_result = getsockopt(sockfd,
                                   SOL_SOCKET,
                                   SO_PEERCRED,
                                   (void*)&peercredbuf,
                                   &opt_length))) {
    perror("getsockopt failed");
  }
  printf("Peer credentials before first fork:\n");
  printf("pid: %d\n", peercredbuf.pid);
  printf("uid: %d\n", peercredbuf.uid);
  printf("gid: %d\n", peercredbuf.gid);

  printf("Press enter after server has forked for the first time");
  getchar();

  opt_length = sizeof(peercredbuf);
  if(-1 == (gso_result = getsockopt(sockfd,
                                   SOL_SOCKET,
                                   SO_PEERCRED,
                                   (void*)&peercredbuf,
                                   &opt_length))) {
    perror("getsockopt failed");
  }

  printf("Peer credentials after first fork:\n");
  printf("pid: %d\n", peercredbuf.pid);
  printf("uid: %d\n", peercredbuf.uid);
  printf("gid: %d\n", peercredbuf.gid);

  printf("Press enter after server has forked for the __SECOND__ time");
  getchar();

  opt_length = sizeof(peercredbuf);
  if(-1 == (gso_result = getsockopt(sockfd,
                                   SOL_SOCKET,
                                   SO_PEERCRED,
                                   (void*)&peercredbuf,
                                   &opt_length))) {
    perror("getsockopt failed");
  }

  printf("Peer credentials before after second fork:\n");
  printf("pid: %d\n", peercredbuf.pid);
  printf("uid: %d\n", peercredbuf.uid);
  printf("gid: %d\n", peercredbuf.gid);

  close(sockfd);
}
