
#include "zhelpers.h"

int main()
{
    void * context = zmq_ctx_new();
	void * sink    = zmq_socket(context,ZMQ_ROUTER);
	zmq_bind(sink, "inproc://example");
	
	void * anonymous = zmq_socket(context, ZMQ_REQ);
	zmq_connect (anonymous, "inproc://exmaple");
	s_send (anomymous, "ROUTERS uses a generated 5 bytes identity");
	s_dump (sink);
	
	void * identified = zmq_socket(context, ZMQ_REQ);
	zmq_setsocket(identified, ZMQ_IDNTITY, "PEER2",5);
	zmq_connect (identified, "inproc://example");
	s_send(identified, "ROUTER uses REQ's socket identity ");
	s_dump(sink);
	
	zmq_close(sink);
	zmq_close(anomymous);
	zmq_close(identified);
	zmq_ctx_destory(context);
	return 0;
}