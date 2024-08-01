#pragma once

#include "../../WsSocketContext.h"
#include "../../protobuf/Authenticate.pb.h"

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <iostream>
#include <sstream>

namespace message
{
	namespace websocket
	{
		class Authenticate
		{
		private:
		public:
			static void onAuthenticateRequest(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message);

			static void sendAuthenticateResponse(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::AuthenticateResponse& response);
		};
	}
}
