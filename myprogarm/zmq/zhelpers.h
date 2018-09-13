#include <zmq.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

static char * s_recv( void * socket)
{
	char buffer[256];
	int size = zmq_recv (socket, buffer, 255, 0);
	if(size ==-1)
		return NULL;
		
	buffer[size] = '\0';
	return strndup ( buffer, sizeof(buffer)-1);
}

