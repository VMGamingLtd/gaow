#pragma once

#include "./../protobuf/MessageHeader.pb.h"
#include "./../protobuf/Ping.pb.h"
#include "./../WsSocketContext.h"

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <iostream>
#include <sstream>
#include <vector>

namespace message
{

    enum class NamespaceIds {
        WebSocket = 1
    };

    enum class WebSocketClassIds {
        PingPong = 1
    };

    enum class WebSocketPingPongMethodIds {
        Ping = 1,
        Pong = 2
    };


    class Dispatcher {
    public:
        static std::istringstream wsDataToInputStream(std::string_view data);
        static std::string toHexString(const std::string_view data);
        static std::string toHexString(const std::istream& istream);
        static std::string toHexString(const std::vector<char>& istream);

        static uint32_t toNetworkByteOrder(uint32_t value);
        static uint32_t fromNetworkByteOrder(uint32_t value);
        static void serializeMessageaObjectSize(std::ostream& ostream, uint32_t size);
        static uint32_t parseMessageaObjectSize(std::istream& istream);

        static std::vector<char> readBytesOrException(std::istream& istream, uint32_t size);

        static void serializeMessageHeader(std::ostream& ostream, const GaoProtobuf::MessageHeader& messageHeader);
        static GaoProtobuf::MessageHeader parseMessageHeader(std::istream& istream);

        static void handleMessage(uWS::WebSocket<false, true, SocketContextData>* ws, std::string_view message, uWS::OpCode opCode);
        static void dispatchMessage(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message);

        static void dispatchMessage_Namespace_Websocket(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId);

        static void dispatchMessage_Namespace_Websocket_Class_PingPong(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId);

    };
}
