#pragma once

#include <libusockets.h>
#include <cstdint> // Include this header for uint32_t

namespace gaos
{

	class GaosServer {
	private: 
		static const int MAX_MESSAGE_SIZE = 1024 * 10;

		static const int RECEIVE_STATE__NONE = 0;
		static const int RECEIVE_STATE__LENGTH = 1;
		static const int RECEIVE_STATE__MESSAGE = 2;

		static char receiveBuffer[4 + MAX_MESSAGE_SIZE];
		static int receivedLength;
		static uint32_t messageSize; 
		static int receiveState;


		static void on_wakeup(struct us_loop_t* loop);
		static void on_pre(struct us_loop_t* loop);
		static void on_post(struct us_loop_t* loop);

		static struct us_socket_t* on_socket_writable(struct us_socket_t* s);
		static struct us_socket_t *on_socket_close(struct us_socket_t *s, int code, void *reason);
		static struct us_socket_t *on_socket_end(struct us_socket_t *s);
		static struct us_socket_t *on_socket_data(struct us_socket_t *s, char *data, int length);
		static struct us_socket_t *on_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length);
		static struct us_socket_t *on_socket_timeout(struct us_socket_t* s);

	public:
		static void run();
	};

}
