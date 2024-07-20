#include "./ExpiringCache.h"

template<typename K, typename T>
void ExpiringCache<typename K, typename T>::put(const K& key, const T& value) {
	std::lock_guard<std::mutex> lock(cacheMutex);
	auto now = std::chrono::steady_clock::now();
	cache[key] = {value, now};
}

template<typename K, typename T>
bool ExpiringCache<typename K, typename T>::get(const K& key, T& value) {
	std::lock_guard<std::mutex> lock(cacheMutex);
	auto it = cache.find(key);
	if (it != cache.end()) {
		auto now = std::chrono::steady_clock::now();
		if (now - it->second.timestamp < cacheExiprationTime) {
			value = it->second.value;
			return true;
		} else {
			cache.erase(it);  // Remove expired item
		}
	}
	return false;
}

template<typename K, typename T>
void ExpiringCache<typename K, typename T>::clean() {
	std::lock_guard<std::mutex> lock(cacheMutex);
	auto now = std::chrono::steady_clock::now();
	for (auto it = cache.begin(); it != cache.end(); ) {
		if (now - it->second.timestamp >= cacheExiprationTime) {
			it = cache.erase(it);
		} else {
			++it;
		}
	}
}

template class ExpiringCache<int, std::vector<int>>;

