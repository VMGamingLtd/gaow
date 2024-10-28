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
	static std::map<int, std::vector<std::string>> groupToConnectionsMap;
public:
	static std::vector<int> getUserGroups(int userId);
	static void assignUserConnectionToUserGroups(std::string connectionId, std::vector<int> groups);
	static void removeUserConnectionFromUserGroups(std::string connectionId);
	static void cleanCache();
	static void startCacheCleaningThread();

	static std::vector<std::string> getGroupConnections(int groupId);
};