#include"baseCommand.h"
void getCommand::execute(Hashmap<std::string, std::string>& hashmap) {
        node<std::string, std::string>* item = hashmap.get(Key);
        if (item) {
            result = item->value;
            std::cout << "GET " << Key << ": " << result << std::endl;
        } else {
            std::cout << "GET " << Key << ": Not found" << std::endl;
        }
    }
void updateCommand::execute(Hashmap<std::string, std::string>& hashmap){
        node<std::string, std::string>* existing = hashmap.get(Key);
        if (existing) {
            hashmap.remove(Key);
            hashmap.add(Key,Value);
            std::cout<<"Value updated";
        }else{
            hashmap.add(Key,Value);
            std::cout<<"had no existing value";
        }
    }
    
void deleteCommand::execute(Hashmap<std::string, std::string>& hashmap) {
        node<std::string, std::string>* existing = hashmap.get(Key);
        if (existing) {
            hashmap.remove(Key);
            success = true;
            std::cout << "DELETED " << Key << std::endl;
        } else {
            success = false;
            std::cout << "DELETE " << Key << ": Key not found" << std::endl;
        }
    }
    


