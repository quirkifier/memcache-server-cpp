#include "baseCommand.h"

class CacheStore {
    Hashmap<std::string, std::string> store;
    long long int count;
    long long int capacity;
public:
    CacheStore(long long int capacity,long long count) :count(count),capacity(capacity),store(capacity,count) {
    }
    void executeCommand(baseCommand* command) {
        command->execute(store);
    }
    
    // Convenience methods
    void get(const std::string& key) {
        executeCommand(new getCommand(key));
    }
    
    void set(const std::string& key, const std::string& value) {
        executeCommand(new setCommand(key, value));
    }
    
    void update(const std::string& key, const std::string& value) {
        executeCommand(new updateCommand(key, value));
    }
    
    void remove(const std::string& key) {
        executeCommand(new deleteCommand(key));
    }
};
