#include "./WsConnection.h"
#include "./config.h"
#include "./Utils.h"
#include "./groups/Groups.h"

#include <fstream>
#include <iostream>
#include <jwt-cpp/jwt.h>

std::map<std::string, WsConnection*> WsConnection::connections;

bool WsConnection::gaoCertLoaded = false;
std::string WsConnection::gaoCert = "unknown";

WsConnection::WsConnection(uWS::WebSocket<false, true, SocketContextData>* ws)
{
	this->ws = ws;
	this->authenticated = false;
}

void WsConnection::addConnection(uWS::WebSocket<false, true, SocketContextData>* ws)
{
	WsConnection *connection = new WsConnection(ws);
	WsConnection::connections[connection->getId()] = connection;
}

void WsConnection::removeConnection(uWS::WebSocket<false, true, SocketContextData>* ws)
{
	WsConnection *connection = WsConnection::findConnection(ws);
	if (connection != nullptr)
	{
		Groups::removeUserConnectionFromUserGroups(connection->getId());
		WsConnection::connections.erase(connection->getId());
		delete connection;
	}
}

void WsConnection::loadGaoCert() {
	try
	{

		WsConnection::gaoCert = Utils::readFileContents(VERIFY_TOKEN_PUB_CERT_FILE_PATH);
	}
	catch (const std::exception& e)
	{
		std::cerr << "WsConnection::loadGaoCert(): Error loading GAO certificate: " << e.what() << std::endl;
		throw std::runtime_error("Error loading GAO certificate");
	}
}

double WsConnection::getDeviceIdFromToken(auto& token)
{
	if (token.find("device_id") != token.end())
	{
		double id = token["device_id"].template get<double>();
		return id;
	}
	else
	{
		std::cerr << "WsConnection::getDeviceIdFromToken(): device_id not found in token" << std::endl;
		throw std::runtime_error("device_id not found in token");
	}
}

int WsConnection::getUserIdFromToken(auto& token)
{
	if (token.find("user_id") != token.end())
	{
		double id = token["user_id"].template get<double>();
		return static_cast<int>(id);
	}
	else
	{
		std::cerr << "WsConnection::getDeviceIdFromToken(): user_id not found in token" << std::endl;
		throw std::runtime_error("user_id not found in token");
	}
}
UserType WsConnection::getUserTypeFromToken(auto& token)
{
	if (token.find("user_type") != token.end())
	{
		std::string userType = token["user_type"].template get<std::string>();
		if (userType == "RegisteredUser")
		{
			return UserType::RegisteredUser;
		}
		else if (userType == "GuestUser")
		{
			return UserType::GuestUser;
		}
		else
		{
			std::cout << "WsConnection::getUserTypeFromToken(): user_type not recognized in token" << std::endl;
			throw std::runtime_error("user_type not recognized in token");
		}
	}
	else
	{
		std::cerr << "WsConnection::getUserTypeFromToken(): user_type not found in token" << std::endl;
		throw std::runtime_error("user_type not found in token");
	}
}

WsConnectionAuthenticateResult WsConnection::authenticate(std::string jwt) {

	if (!WsConnection::gaoCertLoaded) {
		loadGaoCert();
		WsConnection::gaoCertLoaded = true;
	}

	try
	{
		std::string token = jwt;
		std::string rsa_pub_key = WsConnection::gaoCert;
		auto verify = jwt::verify()
			// We only need an RSA public key to verify tokens
			.allow_algorithm(jwt::algorithm::rs256(rsa_pub_key, "", "", ""));

		auto decoded = jwt::decode(token);

		verify.verify(decoded);

		if (IS_DEBUG) {
			for (auto& e : decoded.get_header_json())
				std::cout << e.first << " = " << e.second << std::endl;
			for (auto& e : decoded.get_payload_json())
				std::cout << e.first << " = " << e.second << std::endl;
		}
		this->authenticated = true;

		auto payload = decoded.get_payload_json();
		this->userId = WsConnection::getUserIdFromToken(payload);
		this->userType = WsConnection::getUserTypeFromToken(payload);
		this->deviceId = WsConnection::getDeviceIdFromToken(payload);

		return WsConnectionAuthenticateResult{ true, false, false };
	}
	catch (const jwt::error::token_verification_exception& e)
	{
		this->authenticated = false;
		std::cout << "WsConnection::authenticate(): warning: unauthorized" << e.what() << std::endl;
		return WsConnectionAuthenticateResult{ false, true, false };
	}
	catch (const std::exception& e)
	{
		this->authenticated = false;
		std::cout << "WsConnection::authenticate(): error: " << e.what() << std::endl;
		return WsConnectionAuthenticateResult{ false, false, true };
	}
}

WsConnection* WsConnection::findConnection(uWS::WebSocket<false, true, SocketContextData>* ws)
{
	if (WsConnection::connections.find(ws->getUserData()->uid) != WsConnection::connections.end())
	{
		return WsConnection::connections[ws->getUserData()->uid];
	}
	else
	{
		return nullptr;
	}
}

bool WsConnection::isAuthenticated()
{
	return this->authenticated;
}

double WsConnection::getDeviceId()
{
	return this->deviceId;
}

int WsConnection::getUserId()
{
	return this->userId;
}

std::string WsConnection::getId()
{
	return this->ws->getUserData()->uid;
}

void WsConnection::setUserGroups(const std::vector<int>& groups)
{
	userGroups = groups;
}
bool WsConnection::connectionUserIsMemberOfGroup(int groupId)
{
	for (int group : userGroups)
	{
		if (group == groupId)
		{
			return true;
		}
	}
	return false;
}


