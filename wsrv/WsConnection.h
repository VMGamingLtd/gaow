#pragma once

#include "./WsSocketContext.h"

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <string>
#include <map>

struct WsConnectionAuthenticateResult
{
	bool isAuthenticated;
	bool isUnauthorized;
	bool isError;
};


class WsConnection
{
private:
	int deviceId;
	int userId;
	int groupId;

	bool authenticated;

	static std::string gaoCert;
	static bool gaoCertLoaded;
	static void loadGaoCert();


public:
	uWS::WebSocket<false, true, SocketContextData>* ws;
	static std::map<std::string, WsConnection*> connections;

	WsConnection(uWS::WebSocket<false, true, SocketContextData>* ws);


	static void addConnection(uWS::WebSocket<false, true, SocketContextData>* ws);
	static void removeConnection(uWS::WebSocket<false, true, SocketContextData>* ws);
	static WsConnection* findConnection(uWS::WebSocket<false, true, SocketContextData>* ws);

	WsConnectionAuthenticateResult authenticate(std::string jwt);
	bool isAuthenticated();

	int getDeviceId();

	std::string getId()
	{
		return this->ws->getUserData()->uid;
	}
};