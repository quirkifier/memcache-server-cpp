
#ifndef CACHE_STORE_H
#define CACHE_STORE_H
#include "Hashmap.h"
#include "dynamic-array.h"
#include "baseCommand.h"
#include "binary_file_handler.h"
#include "sumairString.h"

class CacheStore {
    Hashmap<string, string> store;
    Dynamic_array<string> key_store;
    long long count;
    long long capacity;
    BinaryFileHandler<string, string> handler;

public:
    CacheStore(const string& filename, long long capacity)
        : store(capacity, capacity)
        , key_store(0)
        , count(0)
        , capacity(capacity)
        , handler(filename)
    {
        if (handler.file_exists()) {
            handler.load_all(key_store,store);
        }
    }

    ~CacheStore() {
        handler.save_all(key_store, store);
    }
    string get(const string& key) {
        getCommand* cmd = new getCommand(key);
        cmd->execute(store);
        string result = cmd->getResult();
        std::cout<<cmd->getResult()<<"JUST checking\n";

        delete cmd;
        return result;
    }

    void set(const string& key, const string& value) {
        setCommand* cmd = new setCommand(key, value);
        cmd->execute(store);
        delete cmd;
        key_store.push(key);
        count++;

    }

    bool update(const string& key, const string& value) {
        updateCommand* cmd = new updateCommand(key, value);
        cmd->execute(store);
        bool success = cmd->isSuccessful();
        delete cmd;
        return success;
    }

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

    const Dynamic_array<string>& keys() const { return key_store; }
    long long size() const { return count; }
};

#endif // CACHE_STORE_H

