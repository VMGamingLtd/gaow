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
			if (IS_DEBUG)
			{
				std::cout << "gaos::GaosBroadcast::groupCreditsChange(): " << std::endl;
			}
			// get the target group id
			int groupId = messageHeader.groupid();

			const std::vector<std::string> connectionIds = Groups::getGroupConnections(groupId);
			if (IS_DEBUG)
			{
				std::cout << "GroupBroadcast::groupCreditsChange(): DEBUG: " << connectionIds.size() << " connections found in the group" << std::endl;
			}

			for (const std::string& connectionId : connectionIds)
			{

				auto it = WsConnection::connections.find(connectionId);
				if (it == WsConnection::connections.end())
				{
					std::cerr << "GroupBroadcast::groupCreditsChange(): WARNING: connection not found" << std::endl;
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

				{
					    std::string data = ostream.str();
						// Print each byte in hexadecimal
						for (unsigned char c : data) {
							std::cerr << "gaos::GaosBroadcast::groupCreditsChange(): relaying message" << std::hex << std::setw(2) << std::setfill('0') << (int)c << ' ';
						}
						std::cerr << std::endl;
				}

				// send the message
				peerConnection->ws->send(ostream.str(), uWS::OpCode::BINARY);
				if (IS_DEBUG)
				{
					std::cout << "gaos::GaosBroadcast::groupCreditsChange(): DEBUG: message was realyed to connection: " << peerConnection->getId() << std::endl;
				}
			}
		}
	}
}