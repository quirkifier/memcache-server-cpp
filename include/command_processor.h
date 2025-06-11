#ifndef COMMAND_PROCESSOR
#define COMMAND_PROCESSOR
#include "protocolParser.h"
#include "cachestore.h"
class CommandProcessor {
private:
    CacheStore& cache;
    
    void printHelp() {
        std::cout << "\n=== CACHE STORE COMMANDS ===" << "\n";
        std::cout << "SET <key> <value>     - Set a key-value pair" << "\n" ;
        std::cout << "GET <key>             - Get value by key" <<  "\n";
        std::cout << "UPDATE <key> <value>  - Update existing key" << "\n"; 
        std::cout << "DELETE <key>          - Delete key-value pair" << "\n";
        std::cout << "HELP                  - Show this help" << "\n";
        std::cout << "EXIT                  - Exit program" << "\n";
        std::cout << "============================\n" << "\n";
    }
    
    void processCommand(const Dynamic_array<string>& tokens) {
        if (tokens.empty()) {
            std::cout << "WARNING: Empty command entered\n";
            return;
        }
        std::cout<<tokens[0]<<"\n";
        std::cout<<tokens.size()<<"\n";
        string cmd = tokens[0];        
        if (cmd == "SET" || cmd == "set") {
            if (tokens.size() < 3) {
                std::cout << "ERROR: SET command requires: SET <key> <value>\n";
                return;
            }
            cache.set(tokens[1], tokens[2]);
            
        } else if (cmd == "GET" || cmd == "get") {
            if (tokens.size() < 2) {
                std::cout << "ERROR: GET command requires: GET <key>" << "\n";
                return;
            }
            string result = cache.get(tokens[1]);
            
        } else if (cmd == "UPDATE" || cmd == "update") {
            if (tokens.size() < 3) {
                std::cout << "ERROR: UPDATE command requires: UPDATE <key> <value>" << "\n";
                return;
            }
            bool success = cache.update(tokens[1], tokens[2]);
            
        } else if (cmd == "DELETE" || cmd == "delete" || cmd == "DEL" || cmd == "del") {
            if (tokens.size() < 2) {
                std::cout << "ERROR: DELETE command requires: DELETE <key>" << "\n";
                return;
            }
            bool success = cache.remove(tokens[1]);
            
        } else if (cmd == "HELP" || cmd == "help") {
            printHelp();
            
        } else {
            std::cout << "ERROR: Unknown command '" << cmd << "'" << "\n";
            std::cout << "Type 'HELP' for available commands" << "\n";
        }
    }
    
public:
    CommandProcessor(CacheStore& store) : cache(store) {}
    void run() {
        std::cout << "=== CACHE STORE INTERACTIVE SHELL ===" << "\n";
        std::cout << "Type 'HELP' for available commands or 'EXIT' to quit\n" << "\n";
        
        std::string input;
        while (true) {
            std::cout << "cache> ";
            getline(std::cin,input);
            string sumair;
            sumair = input;
            if (input.length()==0){
                continue;
            }
            if (sumair == "EXIT" || input == "exit" || input == "QUIT" || input == "quit") {
                std::cout << "Goodbye!" << "\n";
                break;
            }
            Dynamic_array<string> tokens = ProtocolParser::parseCommand(sumair);
            processCommand(tokens);
        }
    }
    
    void processLine(const string& line) {
        if (line.length()==0){

        
            return;
        }
        
        Dynamic_array<string> tokens = ProtocolParser::parseCommandWithQuotes(line);
        processCommand(tokens);
    }
};

#endif
