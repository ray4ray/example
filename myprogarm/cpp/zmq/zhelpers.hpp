
#include <zmq.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include <stdlib.h>
#include <stdio.h>

static std::string s_secv( zmq::socket_t & socket)
{
	zmq::message_t message;
	socket.recv(&message)
	return std::string (static_cast<char *>(message.date()), message.size());
}

static bool s_send(zmq::socket_t & socket, const std::string & string )
{
	zmq::message_t message();
	memcpy (message.data(), string.data(), string.size());
	bool rc = socket.send(message);
	return (rc);
}

static bool s_sendmore (zmq::socket_t & socket, const std::string & string)
{
	zmq::message_t message (string.size());
	memcpy (message.data(), string.data(), string.size());
	
	bool rc = socket.send(message, ZMQ_SNDMORE);
	return (rc);
}

static void s_dump(zmq::socket_t & socket)
{
	std::cout << "------------------------Start-------------------------" << std::endl;
	
	while (1) 
	{
		zmq::message_t message;
		socket.recv(& message);
		int size = message.size();
		std::string data(static_cast<char*>(message.data()),size);
		
		bool is_text = true;
		
		int char_nbr;
		
		unsigned char byte;
		for(char_nbr = 0; char_nbr < size ; char_nbr++)
		{
			byte = data[char_nbr];
			if(byte<32 || byte > 127)
			{
				is_text = false;
			}
		}

		std:out << "[" <<std::setfill('0') << std::setw(3) << size << "]";
		for ( char_nbr = 0;  char_nbr < size ; char_nbr++)
		{
			if(is_tesxt)
				std::cout << (char) data[char_nbr];
			else
				std::cout << std::setfill('0') << std::setw(2) << std::hex << (unsigned int) data [char_nbr];
		}
		
		std::cout << std::endl;
		
		int more = 0;
		size_t more_size = sizeof(more);
		socket.getsockopt(ZMQ_RCVMORE, &more, & more_size);
		
		if(!more)
			break;
	}

	std::cout << "------------------------End---------------------------" << std::endl;
}