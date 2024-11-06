#include "./gaos.h"
#include "../message/Dispatcher.h"

#include <iostream>
#include <iomanip>

namespace gaos
{
	/*
	char GaosServer::receiveBuffer[4 + MAX_MESSAGE_SIZE];
	int GaosServer::receivedLength;
	uint32_t GaosServer::messageSize; 
	int GaosServer::receiveState;
	*/




	GaosServer::ServerContext* GaosServer::getServerContext(struct us_socket_t* s) {
		struct us_socket_context_t* socket_context = us_socket_context(0, s);
		ServerContext* serverContext = (ServerContext*)us_socket_context_ext(0, socket_context);
		return serverContext;
	}

	GaosServer::SocketContext* GaosServer::getSocketContext(struct us_socket_t* s) {
		SocketContext* socketContext = (SocketContext*)us_socket_ext(0, s);
		return socketContext;
	}



	/* We don't need any of these */
	void GaosServer::on_wakeup(struct us_loop_t *loop) 
	{
	}

	void GaosServer::on_pre(struct us_loop_t *loop) 
	{
	}

	/* This is not HTTP POST, it is merely an event emitted post loop iteration */
	void GaosServer::on_post(struct us_loop_t *loop) 
	{
	}

	struct us_socket_t *GaosServer::on_socket_writable(struct us_socket_t *s) 
	{
		return s;
	}

	struct us_socket_t *GaosServer::on_socket_close(struct us_socket_t *s, int code, void *reason) 
	{
		std::cerr << "GaosServer::on_socket_close(): INFO: client disconnected." << std::endl;
		return s;
	}

	struct us_socket_t *GaosServer::on_socket_end(struct us_socket_t *s) 
	{
		/* HTTP does not support half-closed sockets */
		us_socket_shutdown(0, s);
		return us_socket_close(0, s, 0, NULL);
	}

	GaosServer::ReciveResult GaosServer::handleState_none(struct us_socket_t *s, char* data, int length)
	{
		SocketContext* sctx = sctx = getSocketContext(s);

		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		// print data in hex to stdout
		std::cerr << "GaosServer::handleState_none(): data: ";
		for (int i = 0; i < length; i++)
		{
			std::cerr << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)(unsigned char)(data[i]);
		}
		std::cerr << std::endl;
		//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		if (length >= 4)
		{
			memcpy((void*)sctx->receiveBuffer, data, 4);
			data += 4;
			length -= 4;
			sctx->receivedLength = 4;

			std::istringstream iss(std::string{ sctx->receiveBuffer, 4 });
			sctx->messageSize = message::Dispatcher::parseMessageaObjectSize(iss);
			if (sctx->messageSize > MAX_MESSAGE_SIZE)
			{
				std::cerr << "GaosServer::handleState_none(): ERROR: message too large" << std::endl;
				return GaosServer::ReciveResult{ data, length, 1 };
			}

			
			if (sctx->messageSize > 0)
			{
				std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  none --> message " << sctx->messageSize << std::endl;
				sctx->receiveState = RECEIVE_STATE__MESSAGE;
				return GaosServer::ReciveResult{ data, length, 0 };
			}
			else
			{
				std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  none --> none" << std::endl;
				sctx->receiveState = RECEIVE_STATE__NONE;
				return GaosServer::ReciveResult{ data, length, 0 };
			}

			/*
			if (length > 0)
			{
				continue;
			}
			else
			{
				break;
			}
			*/
		}
		else
		{
			memcpy((void*)sctx->receiveBuffer, data, length);
			data += length;
			length -= length;
			sctx->receivedLength = length;
			sctx->receiveState = RECEIVE_STATE__LENGTH;
			std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  none --> length" << std::endl;
			return GaosServer::ReciveResult{ data, length, 0 };
		}
	}

	GaosServer::ReciveResult GaosServer::handleState_length(struct us_socket_t *s, char* data, int length)
	{
		SocketContext* sctx = sctx = getSocketContext(s);

		if (sctx->receivedLength + length >= 4)
		{
			memcpy((void*)(sctx->receiveBuffer + sctx->receivedLength), data, 4 - sctx->receivedLength);
			data += 4 - sctx->receivedLength;
			length -= 4 - sctx->receivedLength;
			sctx->receivedLength += 4 - sctx->receivedLength;

			std::istringstream iss(std::string{ sctx->receiveBuffer, 4 });
			sctx->messageSize = message::Dispatcher::parseMessageaObjectSize(iss);
			if (sctx->messageSize > MAX_MESSAGE_SIZE)
			{
				std::cerr << "GaosServer::handleState_length(): ERROR: message too large" << std::endl;
				return GaosServer::ReciveResult{ data, length, 1 };
			}

			sctx->receiveState = RECEIVE_STATE__MESSAGE;
			std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  length --> message " << sctx->messageSize << std::endl;
			return GaosServer::ReciveResult{ data, length, 0 };

		}
		else
		{
			memcpy((void*)(sctx->receiveBuffer + sctx->receivedLength), data, length);
			sctx->receivedLength += length;
			data += length;
			length -= length;
			std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  length --> length" << std::endl;
			return GaosServer::ReciveResult{ data, length, 0 };
		}
	}

	GaosServer::ReciveResult GaosServer::handleState_message(struct us_socket_t *s, char* data, int length)
	{
		SocketContext* sctx = sctx = getSocketContext(s);
		ServerContext* serverContext = getServerContext(s);

		if (sctx->receivedLength + length >= 4 + sctx->messageSize)
		{
			memcpy((void*)(sctx->receiveBuffer + sctx->receivedLength), data, sctx->messageSize);
			data += sctx->messageSize;
			length -= sctx->messageSize;
			sctx->receivedLength += sctx->messageSize;

			if (false) {
				std::string message{ sctx->receiveBuffer, (size_t)sctx->receivedLength };
				{
					// write recivveBuffer to stderror
					std::cerr << "GaosServer::handleState_message(): message: ";
					for (int i = 0; i < sctx->receivedLength; i++)
					{
						std::cerr << std::hex << std::setw(2) << std::setfill('0') << (unsigned int)(unsigned char)(sctx->receiveBuffer[i]) << " ";
					}
					std::cerr << std::endl;
				}
				std::istringstream iss(message);
				/*
				{
					// iterate over iss stream and print characters in hexa
					char c;
					while (iss.get(c))
					{
						// Cast to unsigned char to handle characters with ASCII values > 127
						unsigned char uc = static_cast<unsigned char>(c);
						// Output the hexadecimal representation
						std::cerr << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(uc) << " ";
					}
					std::cerr << std::endl;
				}
				*/
				GaoProtobuf::MessageHeader messageHeader = message::Dispatcher::parseMessageHeader(iss);
			}


			// put the message dispatch in a lambda
			serverContext->loop->defer([s, rb = std::string{sctx->receiveBuffer + 4, (size_t)(sctx->receivedLength -4)}]() mutable {
                std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp 4000: loop defer\n";
				// create a string stream from the buffer
				std::istringstream iss(rb);

				message::Dispatcher::dispatchMessage_s(s, iss);
			});

			/*
            serverContext->loop->defer([]() {
                std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp 5000: loop defer";
			});
			*/

			sctx->receiveState = RECEIVE_STATE__NONE;
			sctx->receivedLength = 0;
			std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  message " << sctx->messageSize << "  --> none" << std::endl;
			return ReciveResult{ data, length, 0 };

		}
		else
		{
			memcpy((void*)(sctx->receiveBuffer + sctx->receivedLength), data, length);
			data += length;
			length -= length;
			sctx->receivedLength += length;
			std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  message --> message" << std::endl;
			return ReciveResult{ data, length, 0 };
		}
	}

	struct us_socket_t *GaosServer::on_socket_data(struct us_socket_t *s, char *data, int length) {
		SocketContext* sctx = sctx = getSocketContext(s);

		std::cerr << "@@@@@@@@@@@@@@@@@@@@@@@  on_socket_data()" << std::endl;
		while (true)
		{
			if (sctx->receiveState == RECEIVE_STATE__NONE) {
				GaosServer::ReciveResult result = GaosServer::handleState_none(s, data, length);
				if (result.err != 0)
				{
					std::cerr << "GaosServer::on_socket_data(): ERROR: malformed message, closing the socket" << std::endl;
					return us_socket_close(0, s, 0, NULL);
				}
				data = result.data;
				length = result.length;
				if (length == 0)
				{
					break;
				}
				else if (length < 0)
				{
					std::cerr << "GaosServer::on_socket_data(): ERROR: internal error, assertion lengh>=0 failed,  closing the socket" << std::endl;
					return us_socket_close(0, s, 0, NULL);
				}
			}
			else if (sctx->receiveState == RECEIVE_STATE__LENGTH)
			{
				GaosServer::ReciveResult result = handleState_length(s, data, length);
				if (result.err != 0)
				{
					std::cerr << "GaosServer::on_socket_data(): ERROR: malformed message, closing the socket" << std::endl;
					return us_socket_close(0, s, 0, NULL);
				}
				data = result.data;
				length = result.length;
				if (length == 0)
				{
					break;
				}
				else if (length < 0)
				{
					std::cerr << "GaosServer::on_socket_data(): ERROR: internal error, assertion lengh>=0 failed,  closing the socket" << std::endl;
					return us_socket_close(0, s, 0, NULL);
				}
			}
			else if (sctx->receiveState == RECEIVE_STATE__MESSAGE)
			{
				GaosServer::ReciveResult result = handleState_message(s, data, length);
				if (result.err != 0)
				{
					std::cerr << "GaosServer::on_socket_data(): ERROR: malformed message, closing the socket" << std::endl;
					return us_socket_close(0, s, 0, NULL);
				}
				data = result.data;
				length = result.length;
				if (length == 0)
				{
					break;
				}
				else if (length < 0)
				{
					std::cerr << "GaosServer::on_socket_data(): ERROR: internal error, assertion lengh>=0 failed,  closing the socket" << std::endl;
					return us_socket_close(0, s, 0, NULL);
				}
			}
			else
			{
				std::cerr << "GaosServer::on_socket_data(): ERROR: internal error, unknown receive state, closing the socket" << std::endl;
				return us_socket_close(0, s, 0, NULL);
			}
		}

		//us_socket_write(0, s, "Hello short message!", 20, 0);
		return s;
	}

	struct us_socket_t *GaosServer::on_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {
		SocketContext* sctx = sctx = getSocketContext(s);

		sctx->messageSize = 0;
		sctx->receivedLength = 0;
		sctx->receiveState = RECEIVE_STATE__NONE;

		std::cerr << "GaosServer::on_socket_open(): INFO: client connected" << std::endl;
		return s;
	}

	struct us_socket_t *GaosServer::on_socket_timeout(struct us_socket_t *s) {
		return s;
	}

	void GaosServer::create(uWS::Loop* loop)
	{
		/* Create the event loop */
		//struct us_loop_t *loop = us_create_loop(0, GaosServer::on_wakeup, GaosServer::on_pre, GaosServer::on_post, 0);

		/* Create the socket context */
		struct us_socket_context_options_t options = {};

		struct us_socket_context_t *socket_context = us_create_socket_context(0, (us_loop_t *)loop, sizeof(struct ServerContext), options);
		if (!socket_context) {
			std::cerr << "GaosServer::run(): ERROR: Could not create socket context" << std::endl;
			exit(1);
		}

		ServerContext* serverContext = (ServerContext*)us_socket_context_ext(0, socket_context);
		serverContext->loop = loop;


		/* Set up event handlers */
		us_socket_context_on_open(0, socket_context, GaosServer::on_socket_open);
		us_socket_context_on_data(0, socket_context, GaosServer::on_socket_data);
		us_socket_context_on_writable(0, socket_context, GaosServer::on_socket_writable);
		us_socket_context_on_close(0, socket_context, GaosServer::on_socket_close);
		us_socket_context_on_timeout(0, socket_context, GaosServer::on_socket_timeout);
		us_socket_context_on_end(0, socket_context, GaosServer::on_socket_end);

		struct us_listen_socket_t *listen_socket = us_socket_context_listen(0, socket_context, 0, 3000, 0, sizeof(struct SocketContext));
		if (listen_socket) 
		{
			std::cerr << "GaosServer::run(): INFO: Listening on port 3000" << std::endl;
			//us_loop_run(loop);
		} 
		else 
		{
			printf("Failed to listen!\n");
			std::cerr << "GaosServer::run(): ERROR: Failed to listen on port 3000!" << std::endl;
			std::exit(1);
		}
	}

	/*
	void GaosServer::runInThread()
	{
		std::thread t(run);
		t.detach();
	}
	*/
}
