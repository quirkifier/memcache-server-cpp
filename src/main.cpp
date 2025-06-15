#include "Quantum_hashmap.h"
int main() {
    CacheStore cache("sumair.bin",1000);
    std::cout << "Cache Store initialized with capacity: 1000\n";
    Quantum_hashmap_server server(cache);
    server.run();
    return 0;
}
