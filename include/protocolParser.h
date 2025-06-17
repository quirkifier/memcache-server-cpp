#ifndef PROTOCOL_PARSER_H
#define PROTOCOL_PARSER_H
#include "dynamic-array.h"
#include "sumairString.h"
/**
*
* @class ProtocolParser
*
*/
class ProtocolParser {
public:
    /**
    *@brief Takes input a string and then turns it into tokens to use
    *@param input The string that will be tokenized
    *@return tokens tokens
    *
    */
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
    
};

#endif // PROTOCOL_PARSER_H
