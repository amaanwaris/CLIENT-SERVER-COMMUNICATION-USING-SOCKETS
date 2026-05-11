#include "../Common/headers.h"
#include "../Common/dataSt.h"
#include "declarations.h"

// Helper function to ensure all bytes are sent
int sendExact(int sockfd,const void *buf, size_t len)
{
	size_t sent = 0;
#ifdef DEBUG
	printf("%s: ____Begin____\n",__func__);
#endif
	while (sent < len)
	{
		ssize_t n = send(sockfd, (const char*)buf + sent, len - sent, 0);
		if(n <= 0)
			return -1;
		sent += n;
	}
#ifdef DEBUG
	printf("%s: ____ End ____\n",__func__);
#endif
	return 0;

}
