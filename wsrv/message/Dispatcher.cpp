#include "./Dispatcher.h"
#include "./websocket/PingPong.h"
#include "./websocket/Authenticate.h"
#include "./unity_browser_channel/UnityBrowserChannel.h"
#include "./group/GroupBroadcast.h"
#include "./gaos/GaosBroadcast.h"
#include "../WsConnection.h"

#include <iomanip>
#include <iostream>

namespace message
{
    std::string Dispatcher::toHexString(const std::string_view data)
    {
        std::ostringstream oss;
        for (size_t i = 0; i < data.length(); i++)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)data[i];
        }
        return oss.str();
    }
    std::string Dispatcher::toHexString(const std::istream& istream)
    {
        // clone the istream and it's data
        std::istream istreamClone(istream.rdbuf());

        std::ostringstream oss;
        char c;
        while (istreamClone.get(c))
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)c;
        }
        return oss.str();
    }
    std::string Dispatcher::toHexString(const std::vector<char>& istream)
    {
        std::ostringstream oss;
        for (size_t i = 0; i < istream.size(); i++)
        {
            oss << std::hex << std::setw(2) << std::setfill('0') << (int)istream[i];
        }
        return oss.str();
    }

    uint32_t Dispatcher::toNetworkByteOrder(uint32_t value)
    {
        // to big endian
        return ((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) << 8) |
            ((value & 0x00FF0000) >> 8) |
            ((value & 0xFF000000) >> 24);
    }

    uint32_t Dispatcher::fromNetworkByteOrder(uint32_t value)
    {
        // Note that this function is the same as toNetworkByteOrder becasuse bot operations
        // are actually only reversing the byte order of the value.

        // from big endian
        return ((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) << 8) |
            ((value & 0x00FF0000) >> 8) |
            ((value & 0xFF000000) >> 24);
    }

    std::vector<char> Dispatcher::readBytesOrException(std::istream& istream, uint32_t size)
    {
        std::vector<char> v(size);
        istream.read(v.data(), size);
        return v;
    }

    void Dispatcher::serializeMessageaObjectSize(std::ostream& ostream, uint32_t size)
    {
        uint32_t networkByteOrderSize = toNetworkByteOrder(size);
        ostream.write(reinterpret_cast<const char*>(&networkByteOrderSize), sizeof(networkByteOrderSize));
    }

    uint32_t Dispatcher::parseMessageaObjectSize(std::istream& istream)
    {
        { //@@@@@@@@@@@@@@@@@@@@@@@@@
            // print the hex content of the istream
            //std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@ cp 300: istream content: " << toHexString(istream) << std::endl;
        } // @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
        uint32_t networkByteOrderSize;
        istream.read(reinterpret_cast<char*>(&networkByteOrderSize), sizeof(networkByteOrderSize));
        if (istream.fail())
        {
            throw std::runtime_error("Dispatcher::parseMessageaObjectSize(): Failed to read message object size");
        }
        return fromNetworkByteOrder(networkByteOrderSize);
    }
    void Dispatcher::serializeMessageHeader(std::ostream& ostream, const GaoProtobuf::MessageHeader& messageHeader)
    {
        // get the size of the message header
        uint32_t messageHeaderSize = messageHeader.ByteSizeLong();
        Dispatcher::serializeMessageaObjectSize(ostream, messageHeaderSize);

        if (!messageHeader.SerializeToOstream(&ostream))
        {
            throw std::runtime_error("Dispatcher::serializeMessageHeader(): Failed to serialize message header");
        }
    }

    GaoProtobuf::MessageHeader Dispatcher::parseMessageHeader(std::istream& istream)
    {
        // get the size of the message header
        uint32_t messageHeaderSize = Dispatcher::parseMessageaObjectSize(istream);

        // read the message header
        std::vector<char> messageHeaderBuffer(messageHeaderSize);
        istream.read(messageHeaderBuffer.data(), messageHeaderSize);

        GaoProtobuf::MessageHeader messageHeader;
        if (!messageHeader.ParseFromArray(messageHeaderBuffer.data(), messageHeaderSize))
        {
            throw std::runtime_error("Dispatcher::parseMessageHeader(): Failed to parse message header");
        }

        return messageHeader;
    }

    void Dispatcher::handleMessage(uWS::WebSocket<false, true, SocketContextData>* ws, std::string_view message, uWS::OpCode opCode)
    {
        if (opCode == uWS::OpCode::BINARY)
        {
            std::istringstream iss(std::string{message});
            Dispatcher::dispatchMessage(ws, iss);
        }
        else
        {
            std::cerr << "Dispatcher::handleMessage(): Received a non-binary message, opCode: " << opCode << ", message will be ignored" << std::endl;
        }
    }

    void Dispatcher::dispatchMessage(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message)
    {
        try
        {
            // parse the message header
            GaoProtobuf::MessageHeader messageHeader = parseMessageHeader(message);

            // dispatch the message
            int32_t namespaceId = messageHeader.namespaceid();
            int32_t classId = messageHeader.classid();
            int32_t methodId = messageHeader.methodid();

            //@@@@@@@@@@@@@@@@@@@@@@@@@@@
            std::cout << "Dispatcher::dispatchMessage(ws): namespaceId: " << namespaceId << ", classId: " << classId << ", methodId: " << methodId << std::endl;
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@

            // switch based on the namespaceId
            switch (namespaceId)
            {
            case (int32_t)NamespaceIds::WebSocket:
                Dispatcher::dispatchMessage_Namespace_Websocket(ws, message, namespaceId, classId, methodId);
                break;
            case (int32_t)NamespaceIds::UnityBrowserChannel:
                Dispatcher::dispatchMessage_Namespace_UnityBrowserChannel(ws, messageHeader, message);
                break;
            case (int32_t)NamespaceIds::Group:
				dispatchMessage_Namespace_Group(ws, messageHeader, message);
				break;
            default:
                std::cerr << "Dispatcher::dispatchMessage(ws): no such namespaceId: " << namespaceId;
            }

        }
        catch (const std::exception& e)
        {
            std::cerr << "Dispatcher::dispatchMessage(ws): Exception: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Dispatcher::dispatchMessage(ws): Unknown exception" << std::endl;
        }
    }

    void Dispatcher::dispatchMessage_s(struct us_socket_t *s, std::istream& message)
    {
        try
        {
            // parse the message header
            GaoProtobuf::MessageHeader messageHeader = parseMessageHeader(message);

            // dispatch the message
            int32_t namespaceId = messageHeader.namespaceid();
            int32_t classId = messageHeader.classid();
            int32_t methodId = messageHeader.methodid();

            //@@@@@@@@@@@@@@@@@@@@@@@@@@@
            std::cout << "Dispatcher::dispatchMessage(s): namespaceId: " << namespaceId << ", classId: " << classId << ", methodId: " << methodId << std::endl;
            //@@@@@@@@@@@@@@@@@@@@@@@@@@@

            // switch based on the namespaceId
            switch (namespaceId)
            {
            case (int32_t)NamespaceIds::Gaos:
				dispatchMessage_Namespace_Gaos(s, messageHeader, message);
				break;
            default:
                std::cerr << "Dispatcher::dispatchMessage(s): no such namespaceId: " << namespaceId << std::endl;
            }

        }
        catch (const std::exception& e)
        {
            std::cerr << "Dispatcher::dispatchMessage(s): Exception: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Dispatcher::dispatchMessage(s): Unknown exception" << std::endl;
        }
    }

    void Dispatcher::dispatchMessage_Namespace_Websocket(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId)
    {
        try
        {
            // switch based on the classId
            switch (classId)
            {
            case (int32_t)WebSocketClassIds::PingPong:
                Dispatcher::dispatchMessage_Namespace_Websocket_Class_PingPong(ws, message, namespaceId, classId, methodId);
                break;
            case (int32_t)WebSocketClassIds::Authenticate:
                Dispatcher::dispatchMessage_Namespace_Websocket_Class_Authenticate(ws, message, namespaceId, classId, methodId);
                break;
            default:
                std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket(): no such classId: " << classId;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket(): Exception: " << e.what() << std::endl;
        }

    }

    void Dispatcher::dispatchMessage_Namespace_Websocket_Class_PingPong(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId)
    {
        try
        {
            // switch based on the methodId
            switch (methodId)
            {
            case (int32_t)WebSocketPingPongMethodIds::Ping:
                message::websocket::PingPong::onPing(ws, message);
                break;
            case (int32_t)WebSocketPingPongMethodIds::Pong:
                message::websocket::PingPong::onPong(ws, message);
                break;
            default:
                std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket_Class_PingPong(): no such methodId: " << methodId << std::endl;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket_Class_PingPong(): Exception: " << e.what() << std::endl;
        }
    }

    void Dispatcher::dispatchMessage_Namespace_Websocket_Class_Authenticate(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId)
    {
        try
        {
            // switch based on the methodId
            switch (methodId)
            {
            case (int32_t)WebSocketAuthenticateMethodIds::AuthenticateRequest:
                message::websocket::Authenticate::onAuthenticateRequest(ws, message);
                break;
            default:
                std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket_Class_Authenticate(): no such methodId: " << methodId;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket_Class_Authenticate(): Exception: " << e.what() << std::endl;
        }
    }

    void Dispatcher::dispatchMessage_Namespace_UnityBrowserChannel(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
    {
        message::unity_browser_channel::UnityBrowserChannel::relayMessage(ws, messageHeader, message);
    }

    void Dispatcher::dispatchMessage_Namespace_Group(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
    {
        try
        {
			WsConnection* connection = WsConnection::findConnection(ws);
			if (connection == nullptr)
			{
				std::cout << "Dispatcher::dispatchMessage_Namespace_Group(): warning: Connection not found" << std::endl;
				return;
			}
			if (connection->isAuthenticated() == false)
			{
				std::cout << "Dispatcher::dispatchMessage_Namespace_Group(): warning: Connection not authenticated" << std::endl;
				return;
			}

			// switch based on the classId
			switch (messageHeader.classid())
			{
			case (int32_t)GroupClassIds::Broadcast:
				dispatchMessage_Namespace_Group_Class_Broadcast(ws, messageHeader, message);
				break;
			default:
				std::cerr << "Dispatcher::dispatchMessage_Namespace_Group(): no such classId: " << messageHeader.classid();
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "Dispatcher::dispatchMessage_Namespace_Group(): Exception: " << e.what() << std::endl;
		}
    }

    void Dispatcher::dispatchMessage_Namespace_Group_Class_Broadcast(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
	{
		message::group::GroupBroadcast::relayMessage(ws, messageHeader, message);
	}

    void Dispatcher::dispatchMessage_Namespace_Gaos(struct us_socket_t *s, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
    {
        try
        {
			// switch based on the classId
			switch (messageHeader.classid())
			{
			case (int32_t)GaosClassIds::Broadcast:
				dispatchMessage_Namespace_Gaos_Class_Broadcast(s, messageHeader, message);
				break;
			default:
				std::cerr << "Dispatcher::dispatchMessage_Namespace_Gaos(): no such classId: " << messageHeader.classid();
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "Dispatcher::dispatchMessage_Namespace_Gaos(): Exception: " << e.what() << std::endl;
		}
    }

    void Dispatcher::dispatchMessage_Namespace_Gaos_Class_Broadcast(struct us_socket_t *s, const GaoProtobuf::MessageHeader& messageHeader, std::istream& message)
    {
        try
        {
			// switch based on the classId
			switch (messageHeader.methodid())
			{
            case (int32_t)GaosBroadcastMethodIds::GroupCreditsChange:
				message::gaos::GaosBroadcast::groupCreditsChange(s, messageHeader, message);
				break;
			default:
				std::cerr << "Dispatcher::dispatchMessage_Namespace_Gaos_Class_Broadcast(): no such classId: " << messageHeader.classid();
			}
		}
		catch (const std::exception& e)
		{
			std::cerr << "Dispatcher::dispatchMessage_Namespace_Gaos_Class_Broadcast(): Exception: " << e.what() << std::endl;
		}
    }

}
