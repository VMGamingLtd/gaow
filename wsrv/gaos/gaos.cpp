#include "./gaos.h"
#include "../message/Dispatcher.h"

#include <iostream>

namespace gaos
{
	char GaosServer::receiveBuffer[4 + MAX_MESSAGE_SIZE];
	int GaosServer::receivedLength;
	uint32_t GaosServer::messageSize; 
	int GaosServer::receiveState;

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
		printf("Client disconnected\n");
		return s;
	}

	struct us_socket_t *GaosServer::on_socket_end(struct us_socket_t *s) 
	{
		/* HTTP does not support half-closed sockets */
		us_socket_shutdown(0, s);
		return us_socket_close(0, s, 0, NULL);
	}

	struct us_socket_t *GaosServer::on_socket_data(struct us_socket_t *s, char *data, int length) {

		while (true)
		{
			if (receiveState == RECEIVE_STATE__NONE) {
				if (length >= 4)
				{
					memcpy((void*)&receiveBuffer, data, 4);
					data += 4;
					length -= 4;
					receivedLength = 4;

					std::istringstream iss(std::string{ receiveBuffer, 4 });
					messageSize = message::Dispatcher::parseMessageaObjectSize(iss);
					if (messageSize > MAX_MESSAGE_SIZE)
					{
						std::cerr << "GaosServer::on_socket_data(): ERROR: message too large, closing the socket" << std::endl;
						return us_socket_close(0, s, 0, NULL);
					}

					receiveState = RECEIVE_STATE__MESSAGE;

					if (length > 0)
					{
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					memcpy((void*)receiveBuffer, data, length);
					receivedLength = length;
					receiveState = RECEIVE_STATE__LENGTH;
					break;
				}
			}
			else if (receiveState == RECEIVE_STATE__LENGTH)
			{
				if (receivedLength + length >= 4)
				{
					memcpy((void*)(receiveBuffer + receivedLength), data, 4 - receivedLength);
					data += 4 - receivedLength;
					length -= 4 - receivedLength;
					receivedLength += 4 - receivedLength;

					std::istringstream iss(std::string{ receiveBuffer, 4 });
					messageSize = message::Dispatcher::parseMessageaObjectSize(iss);

					receiveState = RECEIVE_STATE__MESSAGE;

					if (length > 0)
					{
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					memcpy((void*)(receiveBuffer + receivedLength), data, length);
					receivedLength += length;
					break;
				}
			}
			else if (receiveState == RECEIVE_STATE__MESSAGE)
			{
				if (receivedLength + length >= 4 + messageSize)
				{
					memcpy((void*)(receiveBuffer + receivedLength), data, messageSize);
					data += messageSize;
					length -= messageSize;
					receivedLength += messageSize;

					std::istringstream iss(std::string{ receiveBuffer + 4, messageSize });
					message::Dispatcher::dispatchMessage(nullptr, iss);

					receiveState = RECEIVE_STATE__NONE;
					receivedLength = 0;

					if (length > 0)
					{
						continue;
					}
					else
					{
						break;
					}
				}
				else
				{
					memcpy((void*)(receiveBuffer + receivedLength), data, length);
					receivedLength += length;
					break;
				}
			}
		}



		//us_socket_write(0, s, "Hello short message!", 20, 0);
		return s;
	}

	struct us_socket_t *GaosServer::on_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length) {

		printf("Client connected\n");
		return s;
	}

	struct us_socket_t *GaosServer::on_socket_timeout(struct us_socket_t *s) {
		return s;
	}

	void GaosServer::run()
	{
		receivedLength = 0;
		messageSize = 0;
		receiveState = RECEIVE_STATE__NONE;

		/* Create the event loop */
		struct us_loop_t *loop = us_create_loop(0, GaosServer::on_wakeup, GaosServer::on_pre, GaosServer::on_post, 0);

		/* Create the socket context */
		struct us_socket_context_options_t options = {};

		struct us_socket_context_t *socket_context = us_create_socket_context(0, loop, 0, options);

		if (!socket_context) {
			std::cerr << "Could not create socket context" << std::endl;
			exit(0);
		}

		/* Set up event handlers */
		us_socket_context_on_open(0, socket_context, GaosServer::on_socket_open);
		us_socket_context_on_data(0, socket_context, GaosServer::on_socket_data);
		us_socket_context_on_writable(0, socket_context, GaosServer::on_socket_writable);
		us_socket_context_on_close(0, socket_context, GaosServer::on_socket_close);
		us_socket_context_on_timeout(0, socket_context, GaosServer::on_socket_timeout);
		us_socket_context_on_end(0, socket_context, GaosServer::on_socket_end);

		struct us_listen_socket_t *listen_socket = us_socket_context_listen(0, socket_context, 0, 3000, 0, 0);
	}
}
