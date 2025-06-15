#ifndef COMMAND_PROCESSOR
#define COMMAND_PROCESSOR
#include "protocolParser.h"
#include "cachestore.h"
#include  <unistd.h>
#include <netinet/in.h>
#include <cstring>

int read_from_socket(int sock, char* buf, int size) {
    int bytes = recv(sock, buf, size - 1, 0);
    if (bytes <= 0) {
        std::cout << "Error reading from socket or client disconnected.\n";
        return 0;
    }
    buf[bytes] = '\0';
    return bytes;
}

void write_to_socket(int sock, const string& msg) {
    send(sock, msg.isdata(), msg.length(), 0);
}

class CommandProcessor {
private:
    CacheStore& cache;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    sockaddr_in client{};

    void printHelp() {
        string help =
            "\n=== CACHE STORE COMMANDS ===\n"
            "SET <key> <value>     - Set a key-value pair\n"
            "GET <key>             - Get value by key\n"
            "UPDATE <key> <value>  - Update existing key\n"
            "DELETE <key>          - Delete key-value pair\n"
            "HELP                  - Show this help\n"
            "EXIT                  - Exit program\n"
            "============================\n\n";
        write_to_socket(sock, help);
    }

    void processCommand(const Dynamic_array<string>& tokens) {
        if (tokens.empty()) {
            write_to_socket(sock, "WARNING: Empty command entered\n");
            return;
        }
        string cmd = tokens[0];        
        if (cmd == "SET" || cmd == "set") {
            if (tokens.size() < 3) {
                write_to_socket(sock, "ERROR: SET command requires: SET <key> <value>\n");
                return;
            }
            cache.set(tokens[1], tokens[2]);
            write_to_socket(sock, "OK: Value set\n");
        } else if (cmd == "GET" || cmd == "get") {
            if (tokens.size() < 2) {
                write_to_socket(sock, "ERROR: GET command requires: GET <key>\n");
                return;
            }
            string result = cache.get(tokens[1]);
            std::cout<<result<<"\n ";
            write_to_socket(sock, result + "\n");
        } else if (cmd == "UPDATE" || cmd == "update") {
            if (tokens.size() < 3) {
                write_to_socket(sock, "ERROR: UPDATE command requires: UPDATE <key> <value>\n");
                return;
            }
            bool success = cache.update(tokens[1], tokens[2]);
            write_to_socket(sock, success ? "OK: Value updated\n" : "ERROR: Key not found\n");
        } else if (cmd == "DELETE" || cmd == "delete" || cmd == "DEL" || cmd == "del") {
            if (tokens.size() < 2) {
                write_to_socket(sock, "ERROR: DELETE command requires: DELETE <key>\n");
                return;
            }
            bool success = cache.remove(tokens[1]);
            write_to_socket(sock, success ? "OK: Key deleted\n" : "ERROR: Key not found\n");
        } else if (cmd == "HELP" || cmd == "help") {
            printHelp();
        } else {
            string unknown = cmd + "ERROR: Unknown command  \nType 'HELP' for available commands\n";
            write_to_socket(sock, unknown);
        }
    }

    void trimNewlines(string& s) {
        while (s.length() > 0 && (s[s.length() - 1] == '\n' || s[s.length() - 1] == '\r')) {
            s = s.substr(0, s.length() - 1);
        }
    }

public:
    CommandProcessor(CacheStore& store) : cache(store) {
        sockaddr_in addr{};
        addr.sin_family = AF_INET;
        addr.sin_port = htons(8080);
        addr.sin_addr.s_addr = INADDR_ANY;
        bind(sock, (sockaddr*)&addr, sizeof(addr));
        listen(sock, SOMAXCONN);

        socklen_t client_size = sizeof(client);
        sock = accept(sock, (sockaddr*)&client, &client_size);
    }

    void run() {
        char input[1000];
        string start = "=== CACHE STORE INTERACTIVE SHELL ===\nType 'HELP' for available commands or 'EXIT' to quit\n\n";
        write_to_socket(sock, start);

        while (true) {
            memset(input, 0, sizeof(input));
            if (!read_from_socket(sock, input, 1000)) {
                break;
            }
            string sumair = input;
            trimNewlines(sumair);

            if (sumair.length() == 0) {
                continue;
            }

            if (sumair == "EXIT" || sumair == "exit" || sumair == "QUIT" || sumair == "quit") {
                write_to_socket(sock, "Goodbye\n");
                close(sock);
                break;
            }

            Dynamic_array<string> tokens = ProtocolParser::parseCommand(sumair);
            processCommand(tokens);
        }
    }

    void processLine(const string& line) {
        if (line.length() == 0) {
            return;
        }
        Dynamic_array<string> tokens = ProtocolParser::parseCommand(line);
        processCommand(tokens);
    }
};

#endif

