#include "./Authenticate.h"
#include "../Dispatcher.h"
#include "../../protobuf/Authenticate.pb.h"
#include "../../WsConnection.h"


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
					return;
				}

				// authenticate the connection
				WsConnectionAuthenticateResult authResult = connection->authenticate(request.token());
				
				GaoProtobuf::AuthenticateResponse response;
				if (authResult.isAuthenticated)
				{
					response.set_result(GaoProtobuf::AuthenticationResult::success);
				}
				else if (authResult.isUnauthorized)
				{
					response.set_result(GaoProtobuf::AuthenticationResult::unauthorized);
				}
				else
				{
					response.set_result(GaoProtobuf::AuthenticationResult::error);
				}


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
