#ifndef HASHMAP
#define HASHMAP
#include "dynamic-array.h"
#include "linked_list.h"
#include <cstdint>
#include "logger.h"


template<typename Key>
int64_t hash(Key);
template<>
/**
*@brief converts a string into a hash my adding it ascii value
*@param hash_str will be the key that will be hashed
*@return hash value will be returned
*/
inline int64_t hash(string hash_str) {
    int64_t total_sum = 0;
    for (size_t i = 0; i < hash_str.length(); i++) {
        total_sum += static_cast<int64_t>(hash_str[i]);
    }
    return total_sum;
}

template<typename Key, typename Value>
/**
 * @class Hashmap
 * @brief Hashmap consisting of an array of linked list to stop collisions with o(1) look up time
 * 
 */
class Hashmap {
    int64_t capacity;
    int64_t count;
    Dynamic_array<LinkedList<Key, Value>> buckets;
    logger log;
    
public:
    /**
     * @brief default constructor of the hashamp
    *@param capacity is the number of nodes allocated to the hashmap
    *@param count the number of key inside the hashmap
    */
    Hashmap(int64_t capacity, int64_t count = 0)
        : capacity(capacity), count(count), buckets(capacity) {
        log.initialize("memcachelog.txt");
    }

    /**
    *@brief adding two funcitons
    *
    *
    */

    
    void add(Key key, Value value) {
        int64_t hashed = hash(key) % capacity;
        buckets[hashed].insert(key, value);
        count++;
        log.write_set_value(key, value);
    }
    /*
    * @brief updates the keyvalue pair by first removing and then updating the value
    */
    
    void update(Key key, Value value) {
        int64_t hashed = hash(key) % capacity;
        buckets[hashed].remove(key);
        buckets[hashed].insert(key, value);
        log.write_update_value(key, value);
    }
    /*
     * @brief delete the key value pair of the hashmap
     *
     *
    */
    
    bool remove(Key key) {
        int64_t hashed = hash(key) % capacity;
        if (buckets[hashed].remove(key)) {
            count--;
            log.write_delete_value(key);
            return true;
        }
        return false;
    }
    /*
    * @brief checks if the key given is inside the hashmap
    */

    
    bool contains(Key key) const {
        int64_t hashed = hash(key) % capacity;
        return buckets[hashed].find_ptr(key) != nullptr;
    }
    /*
    * @brief fetches the key value from it's node inside the hashmap
    * */
    
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


