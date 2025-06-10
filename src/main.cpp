#include "cachestore.h"

int main() {
    CacheStore cache(1000,0);
    
    // Using command objects directly
    getCommand getCmd("user:1");
    setCommand setCmd("user:1", "John Doe");
    cache.set("user:1","sumair");
    cache.update("user:1", "Jane Smith");  // UPDATED user:1 = Jane Smith
    cache.get("user:1");                   // GET user:1: Jane Smith
    cache.remove("user:1");                // DELETED user:1
    cache.get("user:1");                   // GET user:1: Not found
    // Using command polymorphism
    baseCommand* cmd = new deleteCommand("user:2");
    delete cmd;
    return 0;
}

