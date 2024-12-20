/* Toralize.c */

#include "toralizer.h"

int main(int argc, char *argv[]) {
   char *host;
   int port, sock_fd, cd;
   struct sockaddr_in sock;

   if(argc<3) {
      fprintf(stderr,"Usage : %s <host> <port>\n",argv[0]);
      return -1;
   }
   
   host = argv[1];
   port = atoi(argv[2]);

   sock_fd = socket(AF_INET,SOCK_STREAM,0);

   if(sock_fd < 0) {
      perror("Socket");
      close(sock_fd);
      return -1;
   }

   sock.sin_family = AF_INET;
   sock.sin_port = htons(port);
   sock.sin_addr.s_addr = inet_addr(host);

   if(sock.sin_addr.s_addr == INADDR_NONE) {
      fprintf(stderr,"Invalid IP Address : %s,\n",host);
      return -1;
   }

   cd = connect(sock_fd,(struct sockaddr *)&sock, sizeof(sock));

   if(cd < 0) {
      perror("connection to proxy server failed");
      close(sock_fd);
      return -1;
   }

   printf("connected to proxy at %s:%d\n",host,port);
   close(sock_fd);
   return 0;
}
