#include "../Common/headers.h"
#include "../Common/dataSt.h"
#include "declarations.h"


int recvExact(int sockfd, void *buf, size_t len)
{
	size_t received = 0;
#ifdef DEBUG
	printf("%s: ____Begin____\n",__func__);
#endif
	while (received < len)
	{
		ssize_t n = recv(sockfd, (char*)buf + received, len - received, 0);
		if(n <= 0)
			return -1;
		received += n;
	}
#ifdef DEBUG
	printf("%s: ____ End ____\n",__func__);
#endif
	return 0;

}
