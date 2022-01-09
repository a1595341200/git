#include <arpa/inet.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

void server() {
  int fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd == -1) {
    exit(-1);
  }
  struct sockaddr_in a;
  memset(&a, 0, sizeof(a));
  a.sin_family = AF_INET;
  a.sin_port = htons(8888);
  a.sin_addr.s_addr = INADDR_ANY;
  memset(&a.sin_zero, 0, sizeof(a.sin_zero));
  int res = bind(fd, (const struct sockaddr *)&a, sizeof(a));
  if (res == -1) {
    exit(-1);
  }
  //监听服务
  res = listen(fd, 10);
  if (res == -1) {
    exit(-1);
  }

  struct sockaddr_in b;
  memset(&b, 0, sizeof(b));
  socklen_t len = sizeof(b);
  int asd = accept(fd, (struct sockaddr *)&b, &len);
  std::string s = inet_ntoa(b.sin_addr);
  std::cout << s << std::endl;
  char buf[1024];
  recv(asd, buf, sizeof(buf), 0);
  printf("黄河收到长江消息：　%s", buf);
  send(asd, "感觉良好\n", strlen("感觉良好\n"), 0);
  close(fd);
}

void udp() {
  int fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (fd == -1) {
    exit(-1);
  }
  struct sockaddr_in a;
  memset(&a, 0, sizeof(a));
  a.sin_family = AF_INET;
  a.sin_port = htons(8888);
  a.sin_addr.s_addr = INADDR_ANY;
  memset(&a.sin_zero, 0, sizeof(a.sin_zero));
  int res = bind(fd, (const struct sockaddr *)&a, sizeof(a));
  if (res == -1) {
    exit(-1);
  }

  struct sockaddr_in b;
  memset(&b, 0, sizeof(b));
  socklen_t len = sizeof(b);
  char buf[1024];
  recvfrom(fd, buf, sizeof(buf), 0, (struct sockaddr *)&b, &len);
  printf("收到长江(%s)消息:%s",inet_ntoa(b.sin_addr),buf);
  sendto(fd, "感觉良好\n", strlen("感觉良好\n"), 0, (struct sockaddr *)&b,
         len);
  close(fd);
}

int main(int argc, char const *argv[]) {
  udp();
  return 0;
}
