#ifndef PROTOCOL_PARSER_H
#define PROTOCOL_PARSER_H
#include "dynamic-array.h"
#include "sumairString.h"

class ProtocolParser {
public:
    static Dynamic_array<string> parseCommand(const string& input) {
        Dynamic_array<string> tokens;
        
        if (input.length()==0) {
            return tokens;
        }
        
        int start = 0;
        int len = input.length();
        while (start < len && input[start] == ' ') {
            start++;
        }
        
        while (start < len) {
            int end = start;
            while (end < len && input[end] != ' ') {
                end++;
            }
            
            if (end > start) {
                string token = input.substr(start, end - start);
                tokens.push(token);
            }
            
            while (end < len && input[end] == ' ') {
                end++;
            }
            
            start = end;
        }
        
        return tokens;
    }
    
    static Dynamic_array<string> parseCommandWithQuotes(const string& input) {
        Dynamic_array<string> tokens;
        
        if (input.length()==0) {
            return tokens;
        }
        
        int len = input.length();
        int i = 0;
        
        while (i < len) {
            // Skip spaces
            while (i < len && input[i] == ' ') {
                i++;
            }
            
            if (i >= len) break;
            
            string token;
            
            // Check if token starts with quote
            if (input[i] == '"') {
                i++; // Skip opening quote
                while (i < len && input[i] != '"') {
                    token += input[i];
                    i++;
                }
                if (i < len) i++; // Skip closing quote
            } else {
                // Regular token
                while (i < len && input[i] != ' ') {
                    token += input[i];
                    i++;
                }
            }
            
            if (token.length() == 0) {
                tokens.push(token);
            }
        }
        
        return tokens;
    }
};

#endif // PROTOCOL_PARSER_H
