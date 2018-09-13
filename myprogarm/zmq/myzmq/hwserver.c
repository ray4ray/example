//  Hello World server

#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

int main (void)
{
    //  Socket to talk to clients
    int err;
    void *context = zmq_ctx_new ();	
    void *responder = zmq_socket (context, ZMQ_REP);
    //int rc = zmq_bind (responder, "tcp://127.0.0.1:5555");
    int rc = zmq_bind (responder, "tcp://169.254.64.2:5555");
    //int rc = zmq_bind (responder, "sctp://169.254.64.2:5555");
    err = zmq_errno();
    printf("error number: %s\n", zmq_strerror(err));
    //int rc = zmq_bind (responder, "sctp://169.254.64.3:5558");
    assert (rc != 0);
    printf("start recv msg\n");
    while (1) {
        char buffer [10];
        zmq_recv (responder, buffer, 10, 0);
        printf ("Received Hello\n");
        sleep (1);          //  Do some 'work'
        zmq_send (responder, "World", 5, 0);
    }
    return 0;
}
