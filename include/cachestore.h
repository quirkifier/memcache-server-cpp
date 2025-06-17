#ifndef CACHE_STORE_H
#define CACHE_STORE_H

#include "Hashmap.h"
#include "dynamic-array.h"
#include "baseCommand.h"
#include "binary_file_handler.h"
#include "sumairString.h"

/**
 * @class CacheStore
 * @brief Stores key value pairs in memory using a hashmap and writes to a binary file on destruction.
 */
class CacheStore {
    /// Hashmap to store key-value pairs.
    Hashmap<string, string> store;
     /// Array to store keys in insertion order.
    Dynamic_array<string> key_store;
    /// number of keys
    long long count;
    /// Maximum capacity of the store.
    long long capacity;
     /// Handles saving/loading from a binary file.
    BinaryFileHandler<string, string> handler;
public:
    /**
     * @brief Constructor that initializes the cache with given capacity and loads data if file exists.
     * @param filename The name of the file to load/store binary data.
     * @param capacity The number of entries the hashmap should handle.
     */
    CacheStore(const string& filename, long long capacity)
        : store(capacity, capacity)
        , key_store(0)
        , count(0)
        , capacity(capacity)
        , handler(filename)
    {
        if (handler.file_exists()) {
            handler.load_all(key_store, store);
        }
    }

    /**
     * @brief Destructor that saves all key-value pairs to file.
     */
    ~CacheStore() {
        handler.save_all(key_store, store);
    }

    /**
     * @brief Gets the value associated with the given key.
     * @param key The key to search for.
     * @return string The value associated with the key.
     */
    string get(const string& key) {
        getCommand* cmd = new getCommand(key);
        cmd->execute(store);
        string result = cmd->getResult();
        std::cout << cmd->getResult() << "JUST checking\n";
        delete cmd;
        return result;
    }

    /**
     * @brief Sets a new key-value pair into the cache.
     * @param key The key to set.
     * @param value The value to set for the key.
     * @return true if successfully set.
     * @return false otherwise.
     */
    bool set(const string& key, const string& value) {
        setCommand* cmd = new setCommand(key, value);
        cmd->execute(store);
        bool success = cmd->isSuccessful();
        delete cmd;
        key_store.push(key);
        count++;
        return success;
    }

    /**
     * @brief Updates the value of an existing key.
     * @param key The key whose value should be updated.
     * @param value The new value to assign.
     * @return true if update was successful.
     * @return false otherwise.
     */
    bool update(const string& key, const string& value) {
        updateCommand* cmd = new updateCommand(key, value);
        cmd->execute(store);
        bool success = cmd->isSuccessful();
        delete cmd;
        return success;
    }

    /**
     * @brief Removes the key-value pair from the cache.
     * @param key The key to remove.
     * @return true if the key was removed.
     * @return false if the key did not exist.
     */
    bool remove(const string& key) {
        deleteCommand* cmd = new deleteCommand(key);
        cmd->execute(store);
        bool success = cmd->isSuccessful();
        delete cmd;

        for (int i = 0; i < key_store.size(); i++) {
            if (key_store[i] == key) {
                for (int j = i; j < key_store.size() - 1; j++) {
                    key_store[j] = key_store[j + 1];
                }
                key_store.pop(); 
                break;
            }
        }
        return success;
    }

    /**
     * @brief Returns the array of all keys.
     * @return const Dynamic_array<string>& Reference to the array of keys.
     */
    const Dynamic_array<string>& keys() const { return key_store; }

    /**
     * @brief Returns the number of stored key-value pairs.
     * @return long long Total number of items in the cache.
     */
    long long size() const { return count; }
};

#endif // CACHE_STORE_H

