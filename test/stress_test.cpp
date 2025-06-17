#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include <chrono>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void client_worker(int id, int iterations) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "[Client " << id << "] Failed to create socket\n";
        return;
    }
    
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "[Client " << id << "] Failed to connect\n";
        close(sock);
        return;
    }
    
    std::cout << "[Client " << id << "] Connected, starting " << iterations << " operations\n";
    
    for (int i = 0; i < iterations; ++i) {
        std::string key = "key" + std::to_string(id) + "_" + std::to_string(i);
        std::string val = "value" + std::to_string(i);
        
        std::string cmds[] = {
            "set " + key + " " + val + "\n",
            "get " + key + "\n",
            "del " + key + "\n"
        };
        
        for (const auto& cmd : cmds) {
            send(sock, cmd.c_str(), cmd.size(), 0);
            char buffer[1024];
            int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
            if (bytes > 0) {
                buffer[bytes] = '\0';
            }
        }
        
    }
    
    close(sock);
    std::cout << "[Client " << id << "] Completed all operations\n";
}

int main() {
    const int num_clients = 50;
    const int iterations_per_client = 100;
    
    std::cout << "Starting stress test: " << num_clients << " clients, " 
              << iterations_per_client << " iterations each\n";
    
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_clients; ++i) {
        threads.emplace_back(client_worker, i, iterations_per_client);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    return 0;
}
