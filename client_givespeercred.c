#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main() {

  int sockfd;
  if(-1 == (sockfd = socket(AF_UNIX, SOCK_STREAM, 0))) {
    perror("socket creation failed");
  }
  struct sockaddr_un addr;
  addr.sun_family = AF_UNIX;
  strcpy(addr.sun_path, "/tmp/testsocket");

  pid_t pid;
  pid = getpid();
  printf("Process id before fork() and connect(): %d\n", pid);
  printf("Forking and connecting in 10 seconds\n");
  fflush(stdout);
  sleep(10);
  printf("Forking for the first time\n");
  if(-1 == (pid = fork())) {
    perror("First fork failed");
  }
  if(0 == pid) {
    if(-1 == connect(sockfd, (struct sockaddr*)&addr, sizeof(addr))) {
      perror("connect failed");
    }
    printf("We have forked the first time.  Advance the client...\n");
    printf("Forking again in 10 seconds\n");
    sleep(10);
    if(-1 == (pid = fork())) {
      perror("Second fork failed");
    }
    if(0 == pid) {
      printf("We have forked the second time.  Advance the client...\n");
      printf("Exiting in 10 seconds\n");
      sleep(10);
      close(sockfd);
      unlink("/tmp/testsocket");
    } else {
      printf("Second fork generated child process pid: %d\n", pid);
      exit(0);
    }
  } else {
    printf("Forking before connect() generated child process pid: %d\n", pid);
    exit(0);
  }
}
