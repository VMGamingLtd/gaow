#include "./ExpiringCache.h"

class GroupUsersCache
{
private:
	ExpiringCache<int, std::vector<int>> cache;
public:
	GroupUsersCache(std::chrono::seconds expirationSeconds) : cache(expirationSeconds) {}

	void put(int groupId, const std::vector<int>& users);

	bool get(int groupId, std::vector<int>& users);

    void clean();
};
