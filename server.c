#include <stdio.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>

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

  char buf[256];
  size_t result;
  do {
  if(-1 == (result = recv(clientfd, &buf, sizeof(buf - 1), 0))) {
    perror("Recv encountered an error");
    break;
  }
  if(0 != result) {
    buf[result + 1] = '\0';
    printf("%s\n", buf);
  } else {
    printf("Client cleanly closed socket\n");
  }
  } while(0 != result);

  close(sockfd);
  unlink("/tmp/testsocket");
}
