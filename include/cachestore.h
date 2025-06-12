
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
            string raw = handler.read_string();
            if (!raw.isempty()) {
                int sep = raw.find_first(' ');
                if (sep >= 0) {
                    string key = raw.substr(0, sep);
                    string value = raw.substr(sep + 1, raw.length() - sep - 1);
                    store.add(key, value);
                    key_store.push(key);
                    count++;
                }
            }
        }
    }

    ~CacheStore() {
        
    }
    void dump_to_file(){
        for(int i = 0;i<key_store.size();i++){
            handler.save_from_hashmap(store,key_store[i]);
        }
    }
    string get(const string& key) {
        getCommand* cmd = new getCommand(key);
        cmd->execute(store);
        string result = cmd->getResult();
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
        return success;
    }

    const Dynamic_array<string>& keys() const { return key_store; }
    long long size() const { return count; }
};

#endif // CACHE_STORE_H

