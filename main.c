#include <complex.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/socket.h>

void setup_socket(int *server_socket) {

  struct sockaddr_in server_address;

  // AF_INET is the address family for IPv4
  // SOCK_STREAM for two way connection based byte streams
  // 0 is the protocol normally
  int aux_socket = *server_socket;
  aux_socket = socket(AF_INET, SOCK_STREAM, 0);
  if (aux_socket < 0) {
    perror("Error creating socket");
  }

  // Config socket
  server_address.sin_family = AF_INET;
  server_address.sin_port = htons(8080);
  // Bind to any ip address
  server_address.sin_addr.s_addr = INADDR_ANY;

  int bind_status = bind(aux_socket, (struct sockaddr *)&server_address,
                         sizeof(server_address));

  if (bind_status < 0) {
    perror("Error binding socket");
  }

  int listen_status = listen(aux_socket, 5);
  if (listen_status == 0) {
    printf("Listening on port 8080\n");
  } else {
    perror("Error listening on port 8080");
  }
}

void *client_handler(void *args) {}

void client_connection(int *server_socket) {
  // Always being executed
  while (1) {
    struct sockaddr_in client_address;
    socklen_t client_connection_size = sizeof(client_address);

    // Accept the connection
    // client socket will copy the type of socket from the server socket
    // To accept the connection, the server socket must be binded and listening
    int client_connection_socket =
        accept(*server_socket, (struct sockaddr *)&client_address,
               &client_connection_size);

    if (client_connection_size < 0) {
      perror("Error doing the connection");
    }

    pthread_t thread;
    // client handler will be executed in a new thread
    pthread_create(&thread, NULL, client_handler,
                   (void *)&client_connection_socket);

    pthread_detach(thread);
  }
}

int main() {

  int server_socket;

  setup_socket(&server_socket);

  client_connection(&server_socket);

  return 0;
}
