#include "../Common/headers.h"
#include "../Common/dataSt.h"
#include "declarations.h"

int main()
{
	int opt;
	int server_sock, client_sock;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_len;
#ifdef DEBUG
	printf("%s: ____BEGIN____\n",__func__);
#endif
	client_len = sizeof(client_addr);

	// Create main_listening socket
	server_sock = socket(AF_INET, SOCK_STREAM, 0);
	if(server_sock == -1)
	{
		perror("server_socket");
		exit(EXIT_FAILURE);
	}
	opt = 1;
	setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	server_addr.sin_port = htons(SERVER_PORT);

	if(bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		perror("Servermain: Bind");
		exit(EXIT_FAILURE);
	}

	listen(server_sock, 10);
	printf("Server Listening on %s:%d...\n", SERVER_IP, SERVER_PORT);

	while(1)
	{
		// Accept incoming Client connections
		client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len);
		if(client_sock < 0)
		{
			perror("ServerMain: client Accept");
			continue;
		}

		printf("New Client connected. \n");

		// Allocating memory for client socket descripter to pass to thread
		int *new_sock = malloc(sizeof(int));
		*new_sock = client_sock;

		pthread_t thread_id;
		if(pthread_create(&thread_id, NULL, clientHandler, (void*)new_sock) < 0)
		{
			perror("ServerMain: pthread_create line 56");
			free(new_sock);
			close(client_sock);
		}
		
		// Detach thread to automatically clean up resources when it finishes
		pthread_detach(thread_id);
	}
	
	close(server_sock);
#ifdef DEBUG
	printf("%s: ____ END ____\n",__func__);
#endif
	return 0;
}

