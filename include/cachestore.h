#include "baseCommand.h"
class CacheStore {
    Hashmap<string, string> store;
    long long int count;
    long long int capacity;
public:
    CacheStore(long long int capacity, long long count) 
        : count(count), capacity(capacity), store(capacity, count) {
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
    
    void executeCommand(baseCommand* command) {
        command->execute(store);
        delete command;
    }
};
