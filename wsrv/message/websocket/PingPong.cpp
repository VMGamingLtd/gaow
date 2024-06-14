#include "./PingPong.h"
#include "../parser/Ping.h"


namespace message
{
	namespace websocket
	{
		void PingPong::onPing(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message)
		{
			GaoProtobuf::Ping ping = parser::Ping::parse(message);
			std::cout << "PingPong::onPing(): received ping: " << ping.message() << std::endl;

			PingPong::sendPong(ws, "Hello from wsrv!");
		}

		void PingPong::onPong(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message)
		{
			GaoProtobuf::Pong pong = parser::Pong::parse(message);
			std::cout << "PingPong::onPong(): received pong: " << pong.message() << std::endl;
		}

		void PingPong::sendPing(uWS::WebSocket<false, true, SocketContextData>* ws, const std::string& message)
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
			parser::Ping::serialize(ostream, messageHeader, ping);

			std::string serializedMessage = ostream.str();
			ws->send(serializedMessage, uWS::OpCode::BINARY);
		}

		void PingPong::sendPong(uWS::WebSocket<false, true, SocketContextData>* ws, const std::string& message)
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
			parser::Pong::serialize(ostream, messageHeader, pong);

			std::string serializedMessage = ostream.str();
			ws->send(serializedMessage, uWS::OpCode::BINARY);
		}	
	}
}
