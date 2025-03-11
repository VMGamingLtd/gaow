#include "./Authenticate.h"
#include "../Dispatcher.h"
#include "../../protobuf/Authenticate.pb.h"
#include "../../WsConnection.h"
#include "../../groups/Groups.h"
#include "../../config.h"


namespace message
{
	namespace websocket
	{
		void Authenticate::onAuthenticateRequest(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message)
		{
			GaoProtobuf::AuthenticateResponse response;
			try
			{
				std::cout << "Authenticate::onAuthenticateRequest(): @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp 100" << std::endl;
				uint32_t messageSize = message::Dispatcher::parseMessageaObjectSize(message);
				std::vector<char> messageBytes = message::Dispatcher::readBytesOrException(message, messageSize);
				GaoProtobuf::AuthenticateRequest request;
				request.ParseFromArray(messageBytes.data(), messageSize);

				response.set_requestid(request.requestid());

				// find the connection
				WsConnection* connection = WsConnection::WsConnection::findConnection(ws);
				if (connection == nullptr)
				{
					std::cout << "Authenticate::onAuthenticateRequest(): WARN: Connection not found" << std::endl;
					GaoProtobuf::AuthenticateResponse response;
					response.set_result(GaoProtobuf::AuthenticationResult::error);
					Authenticate::sendAuthenticateResponse(ws, response);
					return;
				}

				// authenticate the connection
				WsConnectionAuthenticateResult authResult = connection->authenticate(request.token());
				
				if (authResult.isAuthenticated)
				{
					response.set_result(GaoProtobuf::AuthenticationResult::success);

					std::vector<int> userGroups = Groups::getUserGroups(connection->getUserId());
					if (IS_DEBUG)
					{
						std::cout << "Authenticate::onAuthenticateRequest(): DEBUG: userGroups: " << std::endl;
						// iterate over the user groups
						for (int group : userGroups)
						{
							std::cout << group << std::endl;
						}
					}
					connection->setUserGroups(userGroups);
					Groups::assignUserConnectionToUserGroups(connection->getId(), userGroups);
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
				std::cerr << "Authenticate::onAuthenticateRequest(): ERROR: Exception: " << e.what() << std::endl;
				response.set_result(GaoProtobuf::AuthenticationResult::error);
				Authenticate::sendAuthenticateResponse(ws, response);
			}
			catch (...)
			{
				std::cerr << "Authenticate::onAuthenticateRequest(): ERROR: Unknown exception" << std::endl;
				response.set_result(GaoProtobuf::AuthenticationResult::error);
				Authenticate::sendAuthenticateResponse(ws, response);
			}
		}

		void Authenticate::sendAuthenticateResponse(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::AuthenticateResponse& response)
		{
			try
			{
				std::cout << "Authenticate::sendAuthenticateResponse(): INFO: @@@@@@@@@@@@@@@@@@@@@@@@@@@ Sending authenticate response" << std::endl;
				std::cout << "Authenticate::sendAuthenticateResponse(): INFO: response.result(): " << response.result() << std::endl;
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
