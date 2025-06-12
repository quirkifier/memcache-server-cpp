#include "command_processor.h"
int main() {
    CacheStore cache("sumair.bin",1000);
    std::cout << "Cache Store initialized with capacity: 1000\n";
    CommandProcessor processor(cache);
    processor.run();
    cache.dump_to_file();
    return 0;
}
