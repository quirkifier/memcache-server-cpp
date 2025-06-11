#include "command_processor.h"
int main() {
    CacheStore cache(1000, 0);
    std::cout << "Cache Store initialized with capacity: 1000\n";
    CommandProcessor processor(cache);
    processor.run();
    return 0;
}
