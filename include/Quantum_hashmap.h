#ifndef QUANTUM_HASHMAP
#define QUANTUM_HASHMAP
#include "command_processor.h"
class Quantum_hashmap_server {
private:
    CacheStore& cache;
    std::mutex cache_mutex;
    int server_sock;
    Dynamic_array<std::thread> threads;

public:
    Quantum_hashmap_server(CacheStore& store) : cache(store) {
        server_sock = socket(AF_INET, SOCK_STREAM, 0);

        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8080);
        addr.sin_addr.s_addr = INADDR_ANY;

        bind(server_sock, (sockaddr*)&addr, sizeof(addr));
        listen(server_sock, SOMAXCONN);
    }

    ~Quantum_hashmap_server() {
        close(server_sock);
        for (int i = 0; i < threads.size(); i++) {
            if (threads[i].joinable()) {
                threads[i].join();
            }
        }
    }

    void run() {
        std::cout << "Server listening on port 8080...\n";

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


