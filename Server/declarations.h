#define SERVER_PORT 8080
#define SERVER_IP "127.0.0.1"

// Helper function to ensure all bytes are sent 
int sendExact(int, const void *, size_t);
// Helper function to ensure all bytes are received 
int recvExact(int, void *, size_t);

void *clientHandler(void *);
