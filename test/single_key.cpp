#include <iostream>
#include <thread>
#include <vector>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void single_key_hammering(int id, int iterations) {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) return;
    
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    if (connect(sock, (sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        close(sock);
        return;
    }
    
    std::string key = "race_test_key";
    
    for (int i = 0; i < iterations; ++i) {
        std::string value = "value_from_thread_" + std::to_string(id) + "_iteration_" + std::to_string(i);
        
        std::string set_cmd = "set " + key + " " + value + "\n";
        std::string get_cmd = "get " + key + "\n";
        std::string del_cmd = "del " + key + "\n";
        
        send(sock, set_cmd.c_str(), set_cmd.size(), 0);
        char buffer[1024];
        recv(sock, buffer, sizeof(buffer) - 1, 0);
        
        send(sock, get_cmd.c_str(), get_cmd.size(), 0);
        recv(sock, buffer, sizeof(buffer) - 1, 0);
        
        if (i % 3 == 0) {
            send(sock, del_cmd.c_str(), del_cmd.size(), 0);
            recv(sock, buffer, sizeof(buffer) - 1, 0);
        }
    }
    
    std::string exit_cmd = "exit\n";
    send(sock, exit_cmd.c_str(), exit_cmd.size(), 0);
    close(sock);
}

int main() {
    const int num_threads = 50;
    const int iterations = 1000;
    std::cout<<"TEST BEGIN \n";
    std::vector<std::thread> threads;
    
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(single_key_hammering, i, iterations);
    }
    
    for (auto& t : threads) {
        t.join();
    }
    
    std::cout << "✅ Single key race test complete!\n";
    return 0;
}
