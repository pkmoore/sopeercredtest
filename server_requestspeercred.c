#define _GNU_SOURCE
#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>


int main() {

  int sockfd;
  if(-1 == (sockfd = socket(AF_UNIX, SOCK_STREAM, 0))) {
    perror("Socket creation failed");
  }
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, "/tmp/testsocket");

  if(-1 == (bind(sockfd, (struct sockaddr*)&addr, sizeof(addr)))) {
    perror("Bind failed");
  }

  if(-1 == (listen(sockfd, 1))) {
    perror("Listen failed");
  }

  int clientfd;
  if(-1 == (clientfd = accept(sockfd, NULL, NULL))) {
    perror("Accept failed");
  }

  struct ucred peercredbuf;
  socklen_t opt_length = sizeof(peercredbuf);
  int gso_result;
  if(-1 == (gso_result = getsockopt(clientfd,
                                   SOL_SOCKET,
                                   SO_PEERCRED,
                                   (void*)&peercredbuf,
                                   &opt_length))) {
    perror("getsockopt failed");
  }
  printf("Peer credentials after connect() (client has forked):\n");
  printf("pid: %d\n", peercredbuf.pid);
  printf("uid: %d\n", peercredbuf.uid);
  printf("gid: %d\n", peercredbuf.gid);

  printf("Press enter after server has forked for the second time");
  getchar();

  opt_length = sizeof(peercredbuf);
  if(-1 == (gso_result = getsockopt(clientfd,
                                   SOL_SOCKET,
                                   SO_PEERCRED,
                                   (void*)&peercredbuf,
                                   &opt_length))) {
    perror("getsockopt failed");
  }

  printf("Peer credentials after second fork:\n");
  printf("pid: %d\n", peercredbuf.pid);
  printf("uid: %d\n", peercredbuf.uid);
  printf("gid: %d\n", peercredbuf.gid);

  close(clientfd);
  close(sockfd);
}
