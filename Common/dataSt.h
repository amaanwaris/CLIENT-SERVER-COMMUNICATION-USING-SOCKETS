#include "headers.h"

// Structure to send the arithmentic request 
typedef struct 
{
	pid_t clientPid;
	int op1;
	int op2;
	char opr; // '+', '-', '*', '/', '%'
}Request;

// Structure to send the calculated result 
typedef struct 
{

	pid_t clientPid;
	int result;
	int errorFlag; // 0 for Success, 1 for Error (e.g. Division by zero, Invalid OP)
}Response;
