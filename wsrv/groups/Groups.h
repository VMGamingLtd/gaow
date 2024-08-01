# pragma once

#include "../WsConnection.h"
#include "../caching/GroupUsersCache.h"

#include <App.h> // this is the file 'uWebSockets/src/App.h' 
#include <vector>
#include <map>
#include <string>

class Groups
{
private:
	static GroupUsersCache cache;
public:
	static std::vector<int> getUserGroups(int userId);
	static std::map<int, std::vector<std::string>> groupConnections;
	static void addUserConnectionToGroups(std::vector<int> groups, std::string connectionId);
	static void removeConnectionFromGroups(std::string connectionId);
	static void cleanCache();
	static void startCacheCleaningThread();
};