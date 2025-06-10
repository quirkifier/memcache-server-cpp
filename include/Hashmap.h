#ifndef HASHMAP
#define HASHMAP
#include "dynamic-array.h"
#include "linked_list.h"
#include <cstdint>
#include <string>

template<typename Key>
inline int64_t hash(Key);

template<>
inline int64_t hash(std::string hash) {
    int64_t total_sum = 0;
    for (int i = 0; i < hash.size(); i++) {
        total_sum += hash[i];
    }
    return total_sum;
}

template<typename Key, typename Value>
class Hashmap {
    int64_t capacity;
    int64_t count;
    Dynamic_array<LinkedList<Key, Value>> buckets;

public:
    Hashmap(int64_t capacity, int64_t count = 0)
        : capacity(capacity), count(count), buckets(capacity) {}

    void add(Key key, Value value) {
        int64_t hashed = hash(key) % capacity;
        buckets[hashed].insert(key, value);
        count++;
    }

    bool remove(Key key) {
        int64_t hashed = hash(key) % capacity;
        if (buckets[hashed].remove(key)) {
            count--;
            return true;
        }
        return false;
    }

    node<Key, Value>* get(Key key) {
        int64_t hashed = hash(key) % capacity;
        return buckets[hashed].find(key);
    }

    const node<Key, Value>* get(Key key) const {
        int64_t hashed = hash(key) % capacity;
        return buckets[hashed].find(key);
    }

    int64_t get_size() const {
        return count;
    }

    ~Hashmap() = default;
};
#endif
