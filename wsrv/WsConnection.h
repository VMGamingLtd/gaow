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

enum class UserType
{
	RegisteredUser,
	GuestUser,
};


class WsConnection
{
private:
	double deviceId;
	int userId;
	int groupId;
	UserType userType;

	bool authenticated;

	std::vector<int> userGroups;

	static std::string gaoCert;
	static bool gaoCertLoaded;
	static void loadGaoCert();

	double getDeviceIdFromToken(auto& token);
	int getUserIdFromToken(auto& token);
	UserType getUserTypeFromToken(auto& token);


public:
	uWS::WebSocket<false, true, SocketContextData>* ws;
	static std::map<std::string, WsConnection*> connections;

	WsConnection(uWS::WebSocket<false, true, SocketContextData>* ws);


	static void addConnection(uWS::WebSocket<false, true, SocketContextData>* ws);
	static void removeConnection(uWS::WebSocket<false, true, SocketContextData>* ws);
	static WsConnection* findConnection(uWS::WebSocket<false, true, SocketContextData>* ws);

	WsConnectionAuthenticateResult authenticate(std::string jwt);
	bool isAuthenticated();

	double getDeviceId();
	int getUserId();

	std::string getId(); // unique it of this connection

	void setUserGroups(const std::vector<int>& groups);

	bool connectionUserIsMemberOfGroup(int groupId);
};