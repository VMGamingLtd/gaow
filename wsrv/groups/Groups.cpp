#include "./Groups.h"
#include "../config.h"
#include "../DbConnection.h"

#include <mariadb/conncpp.hpp>
#include <thread>

#define GROUPS_CACHE_EXPIRATION_SECONDS 15

GroupUsersCache Groups::cache = GroupUsersCache(std::chrono::seconds(GROUPS_CACHE_EXPIRATION_SECONDS));
std::map<int, std::vector<std::string>> Groups::groupConnections{};

std::vector<int> Groups::getUserGroups(int userId)
{
	std::vector<int> groups;

	// check cache
	if (cache.get(userId, groups))
	{
		return groups;
	} else {
		// get from db
		DbConnection* db = DbConnection::wsrvDbConnection;
		if (db == nullptr)
		{
			db = new DbConnection();
			DbConnection::wsrvDbConnection = db;
		}

		groups = db->getUserGroups(userId);

		// put in cache
		cache.put(userId, groups);
	}


	return groups;
}

void Groups::addUserConnectionToGroups(std::vector<int> groups, std::string connectionId)
{
	//std::vector<int> groups = Groups::getUserGroups(userId);
	for (int groupId : groups)
	{
		std::vector<std::string> connections = Groups::groupConnections[groupId];
		auto it = std::find(connections.begin(), connections.end(), connectionId);
		if (it == connections.end())
		{
			connections.push_back(connectionId);
			Groups::groupConnections[groupId] = connections;
		}
	}
}

void Groups::removeConnectionFromGroups(std::string connectionId)
{
	for (auto it = groupConnections.begin(); it != groupConnections.end(); )
	{
		int groupId = it->first;
		std::vector<std::string>& connections = it->second;
		connections.erase(std::remove(connections.begin(), connections.end(), connectionId), connections.end());

		if (connections.size() == 0)
		{
			it = groupConnections.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Groups::cleanCache()
{
	cache.clean();
}

void Groups::startCacheCleaningThread()
{
	std::thread t([]() {
		while (true)
		{
			std::this_thread::sleep_for(std::chrono::seconds(GROUPS_CACHE_EXPIRATION_SECONDS));
			Groups::cleanCache();
		}
	});

	t.detach();
}
