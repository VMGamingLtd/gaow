#include "./UnityBrowserChannel.h"
#include "../../WsConnection.h"
#include "../Dispatcher.h"

namespace message
{
	namespace unity_browser_channel
	{
		void UnityBrowserChannel::relayMessage(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
		{
			WsConnection* connection = WsConnection::findConnection(ws);
			if (connection == nullptr)
			{
				std::cout << "UnityBrowserChannel::relayMessage(): warning: Connection not found" << std::endl;
				return;
			}

			if (connection->isAuthenticated() == false)
			{
				std::cout << "UnityBrowserChannel::relayMessage(): warning: Connection not authenticated" << std::endl;
				return;
			}

			double deviceId = connection->getDeviceId();
			bool wasRelayed = false;
			// Iterate through all connections and send the message to all connections with the same device id
			for (auto& pair : WsConnection::connections)
			{
				if (pair.second->ws == ws)
				{
					// skip the current connection
					continue;
				}
				if (pair.second->getDeviceId() == deviceId)
				{
					// relay the message

					std::stringstream ostream;

					// write message header
					Dispatcher::serializeMessageHeader(ostream, messageHeader);

					// write the message
					ostream << message.rdbuf();

					// send the message
					pair.second->ws->send(ostream.str(), uWS::OpCode::BINARY);
					std::cout << "UnityBrowserChannel::relayMessage(): message was realyed" << std::endl;

					wasRelayed = true;

				}
			}

			if (wasRelayed == false)
			{
				std::cout << "UnityBrowserChannel::relayMessage(): warning: message was not relayed" << std::endl;
			}

		}
	}
}
