#include <stdio.h>
#include <sys/socket.h>

void setup_socket() {

  // AF_INET is the address family for IPv4
  // SOCK_STREAM for two way connection based byte streams
  // 0 is the protocol normally
  int new_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (new_socket < 0) {
    // handle error
    perror("Error creating socket");
  }
}

int main() { return 0; }
