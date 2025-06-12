#ifndef HASHMAP
#define HASHMAP
#include "dynamic-array.h"
#include "linked_list.h"
#include <cstdint>
#include "logger.h"


template<typename Key>
int64_t hash(Key);

template<>
inline int64_t hash(string hash_str) {
    int64_t total_sum = 0;
    for (size_t i = 0; i < hash_str.length(); i++) {
        total_sum += static_cast<int64_t>(hash_str[i]);
    }
    return total_sum;
}

template<typename Key, typename Value>
class Hashmap {
    int64_t capacity;
    int64_t count;
    Dynamic_array<LinkedList<Key, Value>> buckets;
    logger log;
    
public:
    Hashmap(int64_t capacity, int64_t count = 0)
        : capacity(capacity), count(count), buckets(capacity) {
        log.initialize("memcachelog.txt");
    }
    
    void add(Key key, Value value) {
        int64_t hashed = hash(key) % capacity;
        buckets[hashed].insert(key, value);
        count++;
        log.write_set_value(key, value);
    }
    
    void update(Key key, Value value) {
        int64_t hashed = hash(key) % capacity;
        buckets[hashed].remove(key);
        buckets[hashed].insert(key, value);
        log.write_update_value(key, value);
    }
    
    bool remove(Key key) {
        int64_t hashed = hash(key) % capacity;
        if (buckets[hashed].remove(key)) {
            count--;
            log.write_delete_value(key);
            return true;
        }
        return false;
    }
    
    bool contains(Key key) const {
        int64_t hashed = hash(key) % capacity;
        return buckets[hashed].find_ptr(key) != nullptr;
    }
    
    Value get(Key key) {
        int64_t hashed = hash(key) % capacity;
        Value result;
        if (buckets[hashed].find(key, result)) {
            log.write_get_value(key, result);
            return result;
        }
        return Value();
    }
    
    const Value* get_ptr(Key key) const {
        int64_t hashed = hash(key) % capacity;
        return buckets[hashed].find_ptr(key);
    }
    
    int64_t get_size() const {
        return count;
    }
    
    ~Hashmap() = default;
};
#endif


