#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void client() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    perror("");
    exit(-1);
  }
  struct sockaddr_in a;
  struct hostent *he;
  he = gethostbyname("192.168.0.102");
  memset(&a, 0, sizeof(a));
  a.sin_family = AF_INET;
  a.sin_port = htons(8888);
  //   a.sin_addr.s_addr = inet_addr("192.168.0.102");
  a.sin_addr.s_addr = *(in_addr_t *)he->h_addr;
  memset(&a.sin_zero, 0, sizeof(a.sin_zero));

  int res = connect(fd, (const struct sockaddr *)&a, sizeof(a));
  send(fd, "我已出仓\n", strlen("我已出仓\n"), 0);

  char buf[1024];
  recv(fd, buf, sizeof(buf), 0);
  std::cout << "收到黄河消息：" << buf;
  close(fd);
}

void udp() {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    perror("");
    exit(-1);
  }
  struct sockaddr_in a;
  struct hostent *he;
  he = gethostbyname("192.168.0.102");
  memset(&a, 0, sizeof(a));
  a.sin_family = AF_INET;
  a.sin_port = htons(8888);
  //   a.sin_addr.s_addr = inet_addr("192.168.0.102");
  a.sin_addr.s_addr = *(in_addr_t *)he->h_addr;
  memset(&a.sin_zero, 0, sizeof(a.sin_zero));
  sendto(fd, "我已出仓\n", strlen("我已出仓\n"), 0, (struct sockaddr *)&a,
       sizeof(a));

  char buf[1024];
  socklen_t len = sizeof(a);
  recvfrom(fd, buf, sizeof(buf), 0,(struct sockaddr *)&a, &len);
  printf("收到黄河(%s)消息:%s",inet_ntoa(a.sin_addr),buf);
  close(fd);
}

int main(int argc, char const *argv[]) {
  udp();
  return 0;
}
