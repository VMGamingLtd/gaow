#include "Dispatcher.h"
#include "./parser/Ping.h"

namespace message
{

    std::istringstream  Dispatcher::wsDataToInputStream(std::string_view data)
    {
        std::istringstream iss(data.data(), data.length());
        return iss;
    }

    uint32_t Dispatcher::toNetworkByteOrder(uint32_t value)
    {
        return ((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) << 8) |
            ((value & 0x00FF0000) >> 8) |
            ((value & 0xFF000000) >> 24);
    }

    uint32_t Dispatcher::fromNetworkByteOrder(uint32_t value)
    {
        // Note that this function is the same as toNetworkByteOrder becasuse bot operations
        // are actually only reversing the byte order of the value.

        return ((value & 0x000000FF) << 24) |
            ((value & 0x0000FF00) << 8) |
            ((value & 0x00FF0000) >> 8) |
            ((value & 0xFF000000) >> 24);
    }

    void Dispatcher::serializeMessageaObjectSize(std::ostream& ostream, uint32_t size)
    {
        uint32_t networkByteOrderSize = toNetworkByteOrder(size);
        ostream.write(reinterpret_cast<const char*>(&networkByteOrderSize), sizeof(networkByteOrderSize));
    }

    uint32_t Dispatcher::parseMessageaObjectSize(std::istream& istream)
    {
        uint32_t networkByteOrderSize;
        istream.read(reinterpret_cast<char*>(&networkByteOrderSize), sizeof(networkByteOrderSize));
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
            std::istringstream iss = wsDataToInputStream(message);
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

            // switch based on the namespaceId
            switch (namespaceId)
            {
            case (int32_t)NamespaceIds::WebSocket:
                Dispatcher::dispatchMessage_Namespace_Websocket(ws, message, namespaceId, classId, methodId);
                break;
            default:
                std::cerr << "Dispatcher::dispatchMessage(): no such namespaceId: " << namespaceId;
            }

        }
        catch (const std::exception& e)
        {
            std::cerr << "Dispatcher::dispatchMessage(): Exception: " << e.what() << std::endl;
        }
        catch (...)
        {
            std::cerr << "Dispatcher::dispatchMessage(): Unknown exception" << std::endl;
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
                parser::Ping::parse(message);
                break;
            case (int32_t)WebSocketPingPongMethodIds::Pong:
                parser::Pong::parse(message);
                break;
            default:
                std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket_Class_PingPong(): no such methodId: " << methodId;
            }
        }
        catch (const std::exception& e)
        {
            std::cerr << "Dispatcher::dispatchMessage_Namespace_Websocket_Class_PingPong(): Exception: " << e.what() << std::endl;
        }
    }
}
