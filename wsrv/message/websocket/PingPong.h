#pragma once

#include "../../WsSocketContext.h"

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <iostream>
#include <sstream>

namespace message
{
	namespace websocket
	{
		class PingPong
		{
		public:
			static void onPing(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message);
			static void onPong(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message);

			static void sendPing(uWS::WebSocket<false, true, SocketContextData>* ws, const std::string& message);
			static void sendPong(uWS::WebSocket<false, true, SocketContextData>* ws, const std::string& message);
		};
	}
}