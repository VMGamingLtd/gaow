#pragma once

#include <iostream>
#include <unordered_map>
#include <chrono>
#include <thread>
#include <mutex>
#include <vector>

template<typename K, typename T>
class ExpiringCache {
public:
    ExpiringCache(std::chrono::seconds expirationTime) : cacheExiprationTime(expirationTime) {}

    void put(const K& key, const T& value);
    bool get(const K& key, T& value);
    void clean();

private:
    struct CacheEntry {
        T value;
        std::chrono::steady_clock::time_point timestamp;
    };

    std::unordered_map<K, CacheEntry> cache;
    std::chrono::seconds cacheExiprationTime;
    std::mutex cacheMutex;
};

