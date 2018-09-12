#include <zmq.hpp>
#include "zhelpers.hpp"

int main()
{
	zmq::context_t context(1);
	zmq::socket_t sink(context, ZMQ_ROUTER);
	sink.bind("inproc://example");

	zmq::socket_t anonymous (context, ZMQ_REQ);
	anonymous.connect("inproc://example");
	s_send (anonymous, "ROUTER uses a generated 5 byte identity");
	s_dump (sink);

	zmq::socket_t identified (context, ZMQ_REQ);
	identified.setsocket(ZMQ_IDENTITY, "PEER2",5);
	identified.connect("inproc://example");

	s_send (identified, "ROUTER socket uses REQ's socket identity");
	s_dump (sink);

	return 0;
}