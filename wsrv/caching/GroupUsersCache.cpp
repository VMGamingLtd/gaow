#include "./GroupUsersCache.h"
#include "./ExpiringCache.h"

void GroupUsersCache::put(int groupId, const std::vector<int>& users) 
{
	cache.put(groupId, users);
}

bool GroupUsersCache::get(int groupId, std::vector<int>& users) 
{
	return cache.get(groupId, users);
}

void GroupUsersCache::clean() 
{
	cache.clean();
}
