#ifndef QUANTUM_HASHMAP
#define QUANTUM_HASHMAP
#include "command_processor.h"
/**
*@class Quantum_hashmap_server
*@brief A multithreaded class that handles client connection for memcache server
*The server uses tcp to handles client connections although it does not ensure a clean shutdown
*/
class Quantum_hashmap_server {
private:
    CacheStore& cache;
    std::mutex cache_mutex;
    int server_sock;
    Dynamic_array<std::thread> threads;
public:
     /**
     * @brief Constructor: init the server socket .
     * 
     * @param store Reference to the store which contains the hasmap.
     */
    Quantum_hashmap_server(CacheStore& store) : cache(store) {
        server_sock = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in addr{};

        addr.sin_family = AF_INET;
        addr.sin_port = htons(8080);
        addr.sin_addr.s_addr = INADDR_ANY;
        bind(server_sock, (sockaddr*)&addr, sizeof(addr));
        listen(server_sock, SOMAXCONN);
    }
     /**
     * @brief Destructor: Closes the server socket and joins all client threads.
     *
     */

    ~Quantum_hashmap_server() {
        close(server_sock);
        for (int i = 0; i < threads.size(); i++) {
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }
    }
    /**
    *
    * @brief server loop that accepts clients connections and creates threads
    *
    *
    */
    void run() {
        std::cout <<"THE SERVER HAS STARTED RUNNING \n";

        while (true) {
            sockaddr_in client{};
            socklen_t client_size = sizeof(client);
            int client_sock = accept(server_sock, (sockaddr*)&client, &client_size);
            std::cout << "New client connected\n";
            std::thread t([this, client_sock]() {
                CommandProcessor session(client_sock, cache, cache_mutex);
                session.run();
            });

            threads.push_move(std::move(t));
        }
    }

};
#endif


