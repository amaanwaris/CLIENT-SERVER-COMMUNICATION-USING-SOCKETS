#include "../Common/headers.h"
#include "../Common/dataSt.h"
#include "declarations.h"


int main(int argc, char *argv[])
{
	int clientSock;
	struct sockaddr_in serverAddr;
	Request req;
	Response resp;
#ifdef DEBUG
	printf("%s:____Begin____\n",__func__);
#endif

	if (argc != 4)
	{
		printf("Usage: %s <operand> <op1> <op2>\n", argv[0]);
		printf("Example: %s 15+20 \n", argv[0]);
		printf("Note: use '\\*' for multiplication in shell to prevent globbing.\n");
		return 1;;
	}


//Parase command line arguments
	req.clientPid = getpid();
	req.op1 = atoi(argv[1]);
	req.opr = argv[2][0];
	req.op2 = atoi(argv[3]);

// Create socket 
	clientSock = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSock < 0)
	{
		perror("clientApp: Socket line 31");
		return 1;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serverAddr.sin_port = htons(SERVER_PORT);

// Connect to Server 
	if (connect(clientSock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("clientApp: Connect line 43");
		close(clientSock);
		return 1;
	}

	printf("Connected to server. Sending request (PID: %d): %d %c %d \n", req.clientPid, req.op1, req.opr, req.op2);

// Send request 
	if ( sendExact(clientSock, &req, sizeof(Request)) < 0)
	{
		perror("clientApp: sendExact line 53");
		close(clientSock);
		return 1;
	}

// Receive request 
	if ( recvExact(clientSock, &resp, sizeof(Response)) < 0)
	{
		perror("clientApp: recvExact line 60");
		close(clientSock);
		return 1;
	}

// Display result 
	if (resp.clientPid != req.clientPid)
	{
		printf("Warining: Received response for a diff. client PID (%d)!\n",resp.clientPid);
	}

	else if (resp.errorFlag)
	{
		printf("Server retured an Error (e.g., Division by Zero or Inavlid operator)!\n");
	}
	else
		printf("Result received from server for PID %d: %d \n", resp.clientPid, resp.result);

// Shutdown client 
	close(clientSock);
	printf("Client Shutting down.\n");

#ifdef DEBUG
	printf("%s:____ End ____\n",__func__);
#endif
	return 0 ;


}
