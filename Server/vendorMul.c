#include "../Common/headers.h"
#include "../Common/dataSt.h"
#include "declarations.h"

int main(int argc, char *argv[])
{
	if (argc != 2)
		return 1;
	int port, sock;
	struct sockaddr_in serverAddr;
	Request req;
	Response resp = {0, 0, 0};

#ifdef DEBUG
	printf("%s:%s: ____Begin____\n",__FILE__,__func__);
#endif
	port = -1;
	port = atoi(argv[1]);
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == -1)
	{
		perror("vendorMul: socket line no. 17");
		exit(EXIT_FAILURE);
	}
	memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
	serverAddr.sin_port = htons(port);

	printf("vendorMul Attempting to connect to port %d ..\n",port);
// Connect back to the specific thread spawned this vendor
	if(connect(sock, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("vendorMul: Connect line 30");
		close(sock);
		return 1;
	}


// Read request, process and send response 
	recvExact(sock, &req, sizeof(Request));

	printf("vendorMul Processing request for client PID %d\n", req.clientPid);

	if( req.opr == '*' )
        {
                printf("vendorMul Processing request for client PID %d\n", req.clientPid);

                resp.clientPid = req.clientPid;
                resp.result = req.op1 * req.op2;

                sendExact(sock, &resp, sizeof(Response));
        }
        else
        {   
                printf("vendorMUL Processing request for client PID %d\n", req.clientPid);
        }   

	close(sock);
#ifdef DEBUG
	printf("%s:%s: ____ End ____\n",__FILE__,__func__);
#endif
	return 0;
}
