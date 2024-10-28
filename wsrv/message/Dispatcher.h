#pragma once

#include "./../protobuf/MessageHeader.pb.h"
#include "./../WsSocketContext.h"

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <iostream>
#include <sstream>
#include <vector>
#include <libusockets.h>

namespace message
{

    enum class NamespaceIds {
        WebSocket = 1,
        UnityBrowserChannel = 2,
        Group = 3,
		Gaos = 4,
    };

    enum class WebSocketClassIds {
        PingPong = 1,
        Authenticate = 2,
    };

    enum class WebSocketPingPongMethodIds {
        Ping = 1,
        Pong = 2,
    };

    enum class WebSocketAuthenticateMethodIds {
        AuthenticateRequest = 1,
        AuthenticateResponse = 2,
    };

    enum class GroupClassIds {
		Broadcast = 1,
	};

    enum class GaosClassIds {
        Broadcast = 1,
    };

	enum class GaosBroadcastMethodIds {
		GroupCreditsChange = 1,
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
        static void dispatchMessage_s(struct us_socket_t* s, std::istream& message);

        // Websocket 
        static void dispatchMessage_Namespace_Websocket(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId);

        // Websocket.PingPong
        static void dispatchMessage_Namespace_Websocket_Class_PingPong(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId);
        // Websocket.Authenticate
        static void dispatchMessage_Namespace_Websocket_Class_Authenticate(uWS::WebSocket<false, true, SocketContextData>* ws, std::istream& message, int32_t namespaceId, int32_t classId, int32_t methodId);

        // UnityBrowserChannel
        static void dispatchMessage_Namespace_UnityBrowserChannel(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader,  std::istream& message);

        // Group
        static void dispatchMessage_Namespace_Group(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader,  std::istream& message);
        // Group.Broadcast
        static void dispatchMessage_Namespace_Group_Class_Broadcast(uWS::WebSocket<false, true, SocketContextData>* ws, const GaoProtobuf::MessageHeader& messageHeader,  std::istream& message);

		// Gaos
        static void dispatchMessage_Namespace_Gaos(struct us_socket_t *s, const GaoProtobuf::MessageHeader& messageHeader,  std::istream& message);
		// Gaos.Broadcast
        static void dispatchMessage_Namespace_Gaos_Class_Broadcast(struct us_socket_t *s, const GaoProtobuf::MessageHeader& messageHeader,  std::istream& message);

    };
}
