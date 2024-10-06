#include "./GaosBroadcast.h"
#include "../../groups/Groups.h"
#include "../Dispatcher.h"
#include "../../config.h"

namespace message
{
	namespace gaos
	{
		void GaosBroadcast::groupCreditsChange(struct us_socket_t* s, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
		{
			// get the target group id
			int groupId = messageHeader.groupid();

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
				if (!peerConnection->isAuthenticated())
				{
					// skip unauthenticated connections
					continue;
				}
				if (peerConnection->getUserId() == messageHeader.fromid())
				{
					// skip the user who updated credits
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
					std::cout << "gaos::GaosBroadcast::groupCreditsChange(): message was realyed to connection: " << peerConnection->getId() << std::endl;
				}
			}
		}
	}
}