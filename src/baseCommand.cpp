#include "baseCommand.h"
void getCommand::execute(Hashmap<string, string>& hashmap) {

    if (hashmap.contains(Key)) {
        node<string,string>* sumair = hashmap.get(Key);
        std::cout << "GET " << Key << " = " << sumair->value << "\n";
        delete sumair;
    } else {
        std::cout << "GET " << Key << " = NOT_FOUND" << "\n";
    }
}

void setCommand::execute(Hashmap<string, string>& hashmap) {
    hashmap.add(Key, Value);
    std::cout << "SET " << Key << " = " << Value << "\n";

}

void updateCommand::execute(Hashmap<string, string>& hashmap) {
    if (hashmap.contains(Key)) {
        hashmap.remove(Key);
        hashmap.add(Key,Value);
        success = true;
        std::cout << "UPDATE " << Key << " = " << Value << "\n";
    } else {
        success = false;
        std::cout << "UPDATE " << Key << " = FAILED (key not found)" << "\n";
    }
}

void deleteCommand::execute(Hashmap<string, string>& hashmap) {
    if (hashmap.contains(Key)) {
        hashmap.remove(Key);
        success = true;
        std::cout << "DELETE " << Key << " = SUCCESS" << "\n";
    } else {
        success = false;
        std::cout << "DELETE " << Key << " = FAILED (key not found)" << "\n";
    }
}

