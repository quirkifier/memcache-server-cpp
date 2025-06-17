#include "baseCommand.h"
void getCommand::execute(Hashmap<string, string>& hashmap) {

    if (hashmap.contains(Key)) {
        string sumair = hashmap.get(Key);
        std::cout << "GET " << Key << " = " << sumair<< "\n";
        result = sumair;
    } else {
        std::string sumair2= "Value not found";
        result = sumair2;
    }
}

void setCommand::execute(Hashmap<string, string>& hashmap) {
    if (hashmap.contains(Key)) {
        std::cout<<"Cannot set this value as it already contain stuff\n";
        success = false;
    }else {
        hashmap.add(Key,Value);
        success = true;
        std::cout << "SET " << Key << " = "<< Value << "\n";
    }
}

void updateCommand::execute(Hashmap<string, string>& hashmap) {
    if (hashmap.contains(Key)) {
        hashmap.update(Key,Value);
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

getCommand::getCommand(string key) : Key(key) {}
setCommand::setCommand(string key, string value) : Key(key), Value(value), success(false) {}
updateCommand::updateCommand(string key, string value) : Key(key), Value(value), success(false) {}
deleteCommand::deleteCommand(string key) : Key(key), success(false) {}

const string& getCommand::getResult() const {
    return result;
}
bool setCommand::isSuccessful() const {
    return success;
}
bool updateCommand::isSuccessful() const {
    return success;
}
bool deleteCommand::isSuccessful() const {
    return success;
}

