#pragma once

#include "../../WsSocketContext.h"
#include "../../protobuf/MessageHeader.pb.h"

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <iostream>
#include <sstream>

namespace message
{
	namespace group
	{
		class GroupBroadcast
		{
		private:
		public:
			static void relayMessage(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message);
		};
	}
}
