#include "../Common/headers.h"
#include "../Common/dataSt.h"
#include "declarations.h"

void *clientHandler(void *arg)
{
	int clientSock = *(int*)arg;
	free(arg); 			// free the allocated memory for socket descriptor
	char *vendorProg;
	struct sockaddr_in vendorAddr;

	Request req;
	Response resp = {0, 0, 0};

#ifdef DEBUG
	printf("%s:%s: ____Begin____\n",__FILE__,__func__);
#endif

// 1. Received request from client 
	if ( recvExact(clientSock, &req, sizeof(Request)) < 0)
	{
		perror("clienHandler: recvExact line no. 20");
		close(clientSock);
		pthread_exit(NULL);
	}

	printf("[Thread %lu] Recevied request from Clinet PID %d: %d %c %d\n", pthread_self(), req.clientPid, req.op1, req.opr, req.op2);

// 2. Determine which vendor program to invoke
	vendorProg = NULL;
	switch(req.opr)
	{
		case '+':
			vendorProg = "./vendorAdd";
			break;
		case '-':
			vendorProg = "./vendorSub";
			break;
		case '*':
			vendorProg = "./vendorMul";
			break;
		case '/':
			vendorProg = "./vendorDiv";
			break;
		case '%':
			vendorProg = "./vendorMod";
			break;
		default:
			resp.errorFlag = 1; // inavlid operator
			printf("[Thread %lu] invalid Operator .\n", pthread_self());
			sendExact(clientSock, &resp, sizeof(Response));
			close(clientSock);
			pthread_exit(NULL);
	}

// 3. Create a temporary listening socket for vendor to connect to 
	int vendorListenSock = socket(AF_INET, SOCK_STREAM, 0);
	if(vendorListenSock < 0)
	{
		perror("clienHandler: Vendor Socket line no. 56");
		pthread_exit(NULL);
	}
// Critical Fix: Zero out the struct memory to clear garbage data
	memset(&vendorAddr, 0, sizeof(vendorAddr));
	vendorAddr.sin_family = AF_INET;
	vendorAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	vendorAddr.sin_port = 0; // Let OS assign an ephemeral port
				  
	if ( (bind(vendorListenSock, (struct sockaddr *)&vendorAddr, sizeof(vendorAddr))) < 0)
	{
		perror("clienHandler: bind line no. 69");
		close(vendorListenSock);
		pthread_exit(NULL);
	}
	if((listen(vendorListenSock, 1)) < 0)
	{
		perror("clienHandler: listen line no. 75");
		close(vendorListenSock);
		pthread_exit(NULL);
	}

// Find out which port the OS assigned 
	socklen_t addrLen = sizeof(vendorAddr);
	if((getsockname(vendorListenSock, (struct sockaddr *)&vendorAddr, &addrLen)) < 0)
	{
		perror("clienHandler: getsockname line no. 75");
	}
	int vendorPort = ntohs(vendorAddr.sin_port);

// 4. Fork and execute the vendor program 
	pid_t pid = fork();
	if(pid == 0)
	{
		// Child Process: invoke Vendor
		char portStr[16];
		snprintf(portStr, sizeof(portStr), "%d", vendorPort);

		// execl replaces the child process with the vendor program
		execl(vendorProg, vendorProg, portStr, NULL);

		// if execl fails:
		perror("clientHander: execl failed");
		exit(1);
	}
	else if(pid > 0)
	{
		// Parent Process (Server Thread): Accept vendor connection
		printf("[Thread %lu] forked %s on port %d\n", pthread_self(), vendorProg, vendorPort);

		int vendorSock = accept(vendorListenSock, NULL, NULL);
		if(vendorSock < 0)
		{
			perror(" failed to accept vendor : clientHandler: accept");
			resp.errorFlag = 1;
		}
		else
		{
			//Send request to vendor
			sendExact(vendorSock, &req, sizeof(Request));

			//Receive response from vendor
			recvExact(vendorSock, &resp, sizeof(Response));

			printf("[Thread %lu] Received result from vendor for Client PID %d\n", pthread_self(), resp.clientPid);
			
			close(vendorSock);
		}

		close(vendorListenSock);

		//wait for child process to prevent zombies 
		waitpid(pid, NULL, 0);
		
// 5. Send final result back to client
			printf("[Thread %lu] Sending result to Client PID %d: %d\n", pthread_self(), resp.clientPid, resp.result);
			sendExact(clientSock, &resp, sizeof(Response));
	}
	else
	{
		perror("clientHandler: Fork failed");
		resp.errorFlag = 1;
		sendExact(clientSock, &resp, sizeof(Response));
	}
// 6. Close Client Socket and exit thread
	close(clientSock);

#ifdef DEBUG
	printf("%s:%s ____ End ____\n",__FILE__,__func__);
#endif
	pthread_exit(NULL);

//	return 0;
}
