#include <complex.h>
#include <cstdio>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>

void setup_socket() {

  struct sockaddr_in server_address;

  // AF_INET is the address family for IPv4
  // SOCK_STREAM for two way connection based byte streams
  // 0 is the protocol normally
  int new_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (new_socket < 0) {
    // handle error
    perror("Error creating socket");
  }

  // Config socket
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  // Bind to any ip address
  server_address.sin_addr.s_addr = INADDR_ANY;

  int bind_status = bind(new_socket, (struct sockaddr *)&server_address,
                         sizeof(server_address));

  if (bind_status < 0) {
    perror("Error binding socket");
  }
  int listen_status = listen(new_socket, 5);
  if (listen_status == 0) {
    printf("Listening on port 8080\n");
  } else {
    perror("Error listening on port 8080");
  }
}

int main() {

  setup_socket();

  return 0;
}
