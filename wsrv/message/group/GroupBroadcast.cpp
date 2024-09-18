#include "./GroupBroadcast.h"
#include "../../WsConnection.h"
#include "../../groups/Groups.h"
#include "../Dispatcher.h"
#include "../../config.h"

namespace message
{
	namespace group
	{		
		void GroupBroadcast::relayMessage(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
		{
			WsConnection* connection = WsConnection::findConnection(ws);
			if (connection == nullptr)
			{
				std::cerr << "GroupBroadcast::relayMessage(): warning: Connection not found" << std::endl;
				return;
			}

			// get the target group id
			int groupId = messageHeader.groupid();

			// verify that the connection is a member of the group
			if (connection->connectionUserIsMemberOfGroup(groupId) == false)
			{
				std::cerr << "GroupBroadcast::relayMessage(): warning: user is not a member of the group" << std::endl;
				return;
			}


			const std::vector<std::string> connectionIds = Groups::getGroupConnections(groupId);
			if (connectionIds.size() == 0)
			{
				std::cerr << "GroupBroadcast::relayMessage(): warning: no connections found in the group" << std::endl;
				return;
			}
			for (const std::string& connectionId : connectionIds)
			{
				auto it = WsConnection::connections.find(connectionId);
				if (it == WsConnection::connections.end())
				{
					std::cerr << "GroupBroadcast::relayMessage(): warning: connection not found" << std::endl;
					continue;
				}

				WsConnection* peerConnection = it->second;
				if (peerConnection->getId() == connection->getId())
				{
					// skip the current connection
					continue;
				}

				std::stringstream ostream;

				// write message header
				Dispatcher::serializeMessageHeader(ostream, messageHeader);

				// write the message
				ostream << message.rdbuf();

				// send the message
				peerConnection->ws->send(ostream.str(), uWS::OpCode::BINARY);
				if (IS_DEBUG)
				{
					std::cout << "GroupBroadcast::relayMessage(): message was realyed to connection: " << peerConnection->getId() << std::endl;
				}
			}

		}
	}
}
