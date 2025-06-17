#ifndef COMMAND_PROCESSOR
#define COMMAND_PROCESSOR

#include "protocolParser.h"
#include "cachestore.h"
#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <mutex>
#include <thread>

/**
 * @brief Reads data from a socket into a buffer
 * @param sock The socket file descriptor
 * @param buf The buffer to store the incoming data
 * @param size The size of the buffer
 * @return Number of bytes read
 */
int read_from_socket(int sock, char* buf, int size) {
    int bytes = recv(sock, buf, size - 1, 0);
    if (bytes <= 0) {
        std::cout << "Error reading from socket or client disconnected.\n";
        return 0;
    }
    buf[bytes] = '\0';
    return bytes;
}

/**
 * @brief Sends a string message to a socket
 * @param sock The socket file descriptor
 * @param msg The string message to send
 */
void write_to_socket(int sock, const string& msg) {
    send(sock, msg.isdata(), msg.length(), 0);
}

/**
 * @class CommandProcessor
 * @brief Handles processing of commands from clients using a cache store over sockets
 */
class CommandProcessor {
private:
    CacheStore& cache;           ///< Reference to the main cache store
    int sock;                    ///< Socket file descriptor for client communication
    std::mutex& mutex_store;    ///< Mutex for thread-safe cache access

    /**
     * @brief Sends a help message listing all available commands to the client
     */
    void printHelp() {
        string help =
            "\n=== QUANTUM_MEMCACHE COMMAND   ===\n"
            "SET <key> <value>     - Set a key-value pair\n"
            "GET <key>             - Get value by key\n"
            "UPDATE <key> <value>  - Update existing key\n"
            "DELETE <key>          - Delete key-value pair\n"
            "HELP                  - Show this help\n"
            "EXIT                  - Exit program\n"
            "============================\n\n";
        write_to_socket(sock, help);
    }

    /**
     * @brief Processes a parsed command and sends appropriate responses to the client
     * @param tokens Parsed tokens from the client's input command
     */
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
            {
                std::lock_guard<std::mutex> locking(mutex_store);
                if (cache.set(tokens[1], tokens[2])) {
                    write_to_socket(sock, "OK: Value set\n");
                } else {
                    write_to_socket(sock, "ERROR: The Hashmap already contains <key>\n");
                }
            }
        } else if (cmd == "GET" || cmd == "get") {
            if (tokens.size() < 2) {
                write_to_socket(sock, "ERROR: GET command requires: GET <key>\n");
                return;
            }
            {
                std::lock_guard<std::mutex> locking(mutex_store);
                string result = cache.get(tokens[1]);
                write_to_socket(sock, result + "\n");
            }
        } else if (cmd == "UPDATE" || cmd == "update") {
            if (tokens.size() < 3) {
                write_to_socket(sock, "ERROR: UPDATE command requires: UPDATE <key> <value>\n");
                return;
            }
            {
                std::lock_guard<std::mutex> locking(mutex_store);
                bool success = cache.update(tokens[1], tokens[2]);
                write_to_socket(sock, success ? "OK: Value updated\n" : "ERROR: Key not found\n");
            }
        } else if (cmd == "DELETE" || cmd == "delete" || cmd == "DEL" || cmd == "del") {
            if (tokens.size() < 2) {
                write_to_socket(sock, "ERROR: DELETE command requires: DELETE <key>\n");
                return;
            }
            {
                std::lock_guard<std::mutex> locking(mutex_store);
                bool success = cache.remove(tokens[1]);
                write_to_socket(sock, success ? "OK: Key deleted\n" : "ERROR: Key not found\n");
            }
        } else if (cmd == "HELP" || cmd == "help") {
            printHelp();
        } else {
            string unknown = cmd + " ERROR: Unknown command\nType 'HELP' for available commands\n";
            write_to_socket(sock, unknown);
        }
    }

    /**
     * @brief Removes newlines and control return
     * @param s The string to modify
     */
    void trimNewlines(string& s) {
        while (s.length() > 0 && (s[s.length() - 1] == '\n' || s[s.length() - 1] == '\r')) {
            s = s.substr(0, s.length() - 1);
        }
    }

public:
    /**
     * @brief Constructs the CommandProcessor with client socket and shared cache
     * @param sock The socket file descriptor for communication
     * @param store The shared cache store
     * @param mutex A shared mutex for thread synchronization
     */
    CommandProcessor(int sock, CacheStore& store, std::mutex& mutex)
        : sock(sock), cache(store), mutex_store(mutex) {}

    /**
     * @brief Starts the main command loop for processing client commands
     */
    void run() {
        char input[1000];
        string start = "=== CERN'S QUANTUM MEMCACHE ===\nType 'HELP' for available commands or 'EXIT' to quit\n\n";
        write_to_socket(sock, start);
        while (true) {
            memset(input, 0, sizeof(input));
            if (!read_from_socket(sock, input, 1000)) {
                break;
            }
            string sumair = input;
            trimNewlines(sumair);
            if (sumair.length() == 0) continue;

            if (sumair == "EXIT" || sumair == "exit" || sumair == "QUIT" || sumair == "quit") {
                write_to_socket(sock, "Goodbye\n");
                close(sock);
                break;
            }
            Dynamic_array<string> tokens = ProtocolParser::parseCommand(sumair);
            processCommand(tokens);
        }
    }

    /**
     * @brief Processes a single command line input directly
     * @param line The command string to process
     */
    void processLine(const string& line) {
        if (line.length() == 0) return;
        Dynamic_array<string> tokens = ProtocolParser::parseCommand(line);
        processCommand(tokens);
    }
};

#endif // COMMAND_PROCESSOR

