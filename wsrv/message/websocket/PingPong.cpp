#include "./PingPong.h"
#include "../Dispatcher.h"
#include "../../protobuf/Ping.pb.h"


namespace message
{
	namespace websocket
	{
		void PingPong::onPing(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message)
		{
			try
			{
				uint32_t messageSize = message::Dispatcher::parseMessageaObjectSize(message);
				std::vector<char> messageBytes = message::Dispatcher::readBytesOrException(message, messageSize);
				GaoProtobuf::Ping ping;
				ping.ParseFromArray(messageBytes.data(), messageSize);

				std::cout << "PingPong::onPing(): received ping: " << ping.message() << std::endl;

				PingPong::sendPong(ws, "Hello from wsrv!");
			}
			catch (const std::exception& e)
			{
				std::cerr << "PingPong::onPing(): Exception: " << e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << "PingPong::onPing(): Unknown exception" << std::endl;
			}
		}

		void PingPong::onPong(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message)
		{
			try
			{
				uint32_t messageSize = message::Dispatcher::parseMessageaObjectSize(message);
				std::vector<char> messageBytes = message::Dispatcher::readBytesOrException(message, messageSize);
				GaoProtobuf::Pong pong;
				pong.ParseFromArray(messageBytes.data(), messageSize);

				std::cout << "PingPong::onPong(): received pong: " << pong.message() << std::endl;
			}
			catch (const std::exception& e)
			{
				std::cerr << "PingPong::onPong(): Exception: " << e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << "PingPong::onPong(): Unknown exception" << std::endl;
			}
		}

		void PingPong::sendPing(uWS::WebSocket<false, true, SocketContextData>* ws, const std::string& message)
		{
			try
			{
				std::ostringstream ostream;

				GaoProtobuf::MessageHeader messageHeader;
				messageHeader.set_namespaceid((int32_t)NamespaceIds::WebSocket);
				messageHeader.set_classid((int32_t)WebSocketClassIds::PingPong);
				messageHeader.set_methodid((int32_t)WebSocketPingPongMethodIds::Ping);
				message::Dispatcher::serializeMessageHeader(ostream, messageHeader);

				GaoProtobuf::Ping ping;
				ping.set_message(message);
				uint32_t size = ping.ByteSizeLong();
				message::Dispatcher::serializeMessageaObjectSize(ostream, size);
				ping.SerializeToOstream(&ostream);

				std::string serializedMessage = ostream.str();
				ws->send(serializedMessage, uWS::OpCode::BINARY);
			}
			catch (const std::exception& e)
			{
				std::cerr << "PingPong::sendPing(): Exception: " << e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << "PingPong::sendPing(): Unknown exception" << std::endl;
			}
		}

		void PingPong::sendPong(uWS::WebSocket<false, true, SocketContextData>* ws, const std::string& message)
		{
			try
			{
				std::ostringstream ostream;

				GaoProtobuf::MessageHeader messageHeader;
				messageHeader.set_namespaceid((int32_t)NamespaceIds::WebSocket);
				messageHeader.set_classid((int32_t)WebSocketClassIds::PingPong);
				messageHeader.set_methodid((int32_t)WebSocketPingPongMethodIds::Pong);
				message::Dispatcher::serializeMessageHeader(ostream, messageHeader);

				GaoProtobuf::Pong pong;
				pong.set_message(message);
				uint32_t size = pong.ByteSizeLong();
				message::Dispatcher::serializeMessageaObjectSize(ostream, size);
				pong.SerializeToOstream(&ostream);

				std::string serializedMessage = ostream.str();
				ws->send(serializedMessage, uWS::OpCode::BINARY);
			}
			catch (const std::exception& e)
			{
				std::cerr << "PingPong::sendPong(): Exception: " << e.what() << std::endl;
			}
			catch (...)
			{
				std::cerr << "PingPong::sendPong(): Unknown exception" << std::endl;
			}
		}	
	}
}
