#include "./Authenticate.h"
#include "../Dispatcher.h"
#include "../../protobuf/Authenticate.pb.h"
#include "../../WsConnection.h"
#include "../../groups/Groups.h"


namespace message
{
	namespace websocket
	{
		void Authenticate::onAuthenticateRequest(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message)
		{
			try
			{
				uint32_t messageSize = message::Dispatcher::parseMessageaObjectSize(message);
				std::vector<char> messageBytes = message::Dispatcher::readBytesOrException(message, messageSize);
				GaoProtobuf::AuthenticateRequest request;
				request.ParseFromArray(messageBytes.data(), messageSize);

				// find the connection
				WsConnection* connection = WsConnection::WsConnection::findConnection(ws);
				if (connection == nullptr)
				{
					std::cout << "Authenticate::onAuthenticateRequest(): Connection not found" << std::endl;
					GaoProtobuf::AuthenticateResponse response;
					response.set_result(GaoProtobuf::AuthenticationResult::error);
					Authenticate::sendAuthenticateResponse(ws, response);
					return;
				}

				// authenticate the connection
				WsConnectionAuthenticateResult authResult = connection->authenticate(request.token());
				
				GaoProtobuf::AuthenticateResponse response;
				response.set_requestid(request.requestid());
				if (authResult.isAuthenticated)
				{
					response.set_result(GaoProtobuf::AuthenticationResult::success);

					std::vector<int> userGroups = Groups::getUserGroups(connection->getUserId());
					connection->setUserGroups(userGroups);
					Groups::addUserConnectionToGroups(userGroups, connection->getId());
				}
				else if (authResult.isUnauthorized)
				{
					response.set_result(GaoProtobuf::AuthenticationResult::unauthorized);
				}
				else
				{
					response.set_result(GaoProtobuf::AuthenticationResult::error);
				}
				Authenticate::sendAuthenticateResponse(ws, response);


			}
			catch (const std::exception& e)
			{
				std::cerr << "Authenticate::onAuthenticateRequest(): Exception: " << e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << "Authenticate::onAuthenticateRequest(): Unknown exception" << std::endl;
			}
		}

		void Authenticate::sendAuthenticateResponse(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::AuthenticateResponse& response)
		{
			try
			{
				std::ostringstream ostream;

				GaoProtobuf::MessageHeader messageHeader;
				messageHeader.set_namespaceid((int32_t)message::NamespaceIds::WebSocket);
				messageHeader.set_classid((int32_t)message::WebSocketClassIds::Authenticate);
				messageHeader.set_methodid((int32_t)message::WebSocketAuthenticateMethodIds::AuthenticateResponse);

				// serialize the message header
				Dispatcher::serializeMessageHeader(ostream, messageHeader);

				// serialize the message
				uint32_t size = response.ByteSizeLong();
				message::Dispatcher::serializeMessageaObjectSize(ostream, size);
				response.SerializeToOstream(&ostream);

				// send the message
				ws->send(ostream.str(), uWS::OpCode::BINARY);
			}
			catch (const std::exception& e)
			{
				std::cerr << "Authenticate::sendAuthenticateResponse(): Exception: " << e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << "Authenticate::sendAuthenticateResponse(): Unknown exception" << std::endl;
			}
		}
	}
}
