#include "./Groups.h"
#include "../config.h"
#include "../DbConnection.h"
#include "../config.h"

#include <mariadb/conncpp.hpp>
#include <thread>
#include <iostream>
#include <chrono>

#define GROUPS_CACHE_EXPIRATION_SECONDS 15

GroupUsersCache Groups::cache = GroupUsersCache(std::chrono::seconds(GROUPS_CACHE_EXPIRATION_SECONDS));
std::map<int, std::vector<std::string>> Groups::groupToConnectionsMap{};

std::vector<int> Groups::getUserGroups(int userId) // static
{
	std::vector<int> groups;
	//std::chrono::steady_clock::time_point startTime, endTime;
	std::chrono::high_resolution_clock::time_point startTime, endTime;
	std::chrono::microseconds duration;

	if (IS_DEBUG)
	{
		startTime = std::chrono::high_resolution_clock::now();
	}

	// check cache
	//if (cache.get(userId, groups))
	if (false)
	{

		if (IS_DEBUG)
		{
			endTime = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			std::cout << "Groups::getUserGroups(): DEBUG:" << "Execution time: " << duration.count() << " microseconds (from cache)" << std::endl;
		}
		return groups;
	} 
	else 
	{
		// get from db
		DbConnection* db = DbConnection::wsrvDbConnection;
		if (db == nullptr)
		{
			db = new DbConnection();
			DbConnection::wsrvDbConnection = db;
		}

		groups = db->getUserGroups(userId);

		// Group owner as such is normally never a member of the group of which he is owner.
		// This user might still be the owner of a group with some members and thus indirectly (by the virtue of ownership) be the member of that group. 
		auto ownerGroups = db->getOwnerGroups(userId);

		for (int groupId : ownerGroups)
		{
			int count = db->getGroupMembersCount(groupId);
			if (count > 1) // ignore groups without members
			{
				groups.push_back(groupId);
			}
		}

		// to be on the safe side, remove duplicates
		std::sort(groups.begin(), groups.end());
		groups.erase(std::unique(groups.begin(), groups.end()), groups.end());


		// put in cache
		if (groups.size() > 0)
		{
			cache.put(userId, groups);
		}

		if (IS_DEBUG)
		{
			endTime = std::chrono::high_resolution_clock::now();
			duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
			std::cout << "Groups::getUserGroups():" << "Execution time: " << duration.count() << " microseconds" << std::endl;
		}
	}


	return groups;
}

void Groups::assignUserConnectionToUserGroups(std::string connectionId, std::vector<int> groups) // static
{
	//std::vector<int> groups = Groups::getUserGroups(userId);
	for (int groupId : groups)
	{
		std::vector<std::string> connections = Groups::groupToConnectionsMap[groupId];
		auto it = std::find(connections.begin(), connections.end(), connectionId);
		if (it == connections.end())
		{
			connections.push_back(connectionId);
			Groups::groupToConnectionsMap[groupId] = connections;
		}
	}
}

void Groups::removeUserConnectionFromUserGroups(std::string connectionId) // static
{
	for (auto it = groupToConnectionsMap.begin(); it != groupToConnectionsMap.end(); )
	{
		int groupId = it->first;
		std::vector<std::string>& connections = it->second;
		connections.erase(std::remove(connections.begin(), connections.end(), connectionId), connections.end());

		if (connections.size() == 0)
		{
			it = groupToConnectionsMap.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Groups::cleanCache() // static
{
	cache.clean();
}

void Groups::startCacheCleaningThread() // static
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

std::vector<std::string> Groups::getGroupConnections(int groupId)
{
	if (groupToConnectionsMap.find(groupId) == groupToConnectionsMap.end())
	{
		return std::vector<std::string>();
	}
	return groupToConnectionsMap[groupId];
}
