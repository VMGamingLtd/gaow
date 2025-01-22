#pragma once

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <libusockets.h>
#include <cstdint> // Include this header for uint32_t

namespace gaos
{

	class GaosServer {
	private: 
		enum ReceiveState {
			RECEIVE_STATE__NONE,
			RECEIVE_STATE__LENGTH,
			RECEIVE_STATE__MESSAGE
		};

		struct ReciveResult {
			char* data;
			int length;
			int err;
		};
		static const int MAX_MESSAGE_SIZE = 1024 * 10;

		struct SocketContext
		{
			char receiveBuffer[4 + GaosServer::MAX_MESSAGE_SIZE];
			int receivedLength;
			uint32_t messageSize;
			GaosServer::ReceiveState receiveState;
		};

		struct ServerContext
		{
			uWS::Loop* loop;
		};

		/*
		static const int RECEIVE_STATE__NONE = 0;
		static const int RECEIVE_STATE__LENGTH = 1;
		static const int RECEIVE_STATE__MESSAGE = 2;
		*/

		/*
		static char receiveBuffer[4 + MAX_MESSAGE_SIZE];
		static int receivedLength;
		static uint32_t messageSize; 
		static int receiveState;
		*/


		static void on_wakeup(struct us_loop_t* loop);
		static void on_pre(struct us_loop_t* loop);
		static void on_post(struct us_loop_t* loop);

		static struct us_socket_t* on_socket_writable(struct us_socket_t* s);
		static struct us_socket_t *on_socket_close(struct us_socket_t *s, int code, void *reason);
		static struct us_socket_t *on_socket_end(struct us_socket_t *s);
		static struct us_socket_t *on_socket_data(struct us_socket_t *s, char *data, int length);
		static struct us_socket_t *on_socket_open(struct us_socket_t *s, int is_client, char *ip, int ip_length);
		static struct us_socket_t *on_socket_timeout(struct us_socket_t* s);


		static ReciveResult handleState_none(struct us_socket_t *s, char* data, int length);
		static ReciveResult handleState_length(struct us_socket_t *s, char* data, int length);
		static ReciveResult handleState_message(struct us_socket_t *s, char* data, int length);

		static ServerContext* getServerContext(struct us_socket_t* s);
		static SocketContext* getSocketContext(struct us_socket_t* s);

	public:
		static void create(uWS::Loop *loop, const char* ip, int port);

	};

}
