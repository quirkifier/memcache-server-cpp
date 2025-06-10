#ifndef BASECOMMAND_H
#define BASECOMMAND_H
#include "Hashmap.h"
#include <iostream>
#include <string> 
class baseCommand {
public:
    virtual void execute(Hashmap<std::string, std::string>& hashmap) = 0;
    baseCommand() = default;
    virtual ~baseCommand() = default;
};

class getCommand : public baseCommand {
    std::string Key;
    std::string result;
public:
    getCommand(std::string key) : Key(key) {}
    
    void execute(Hashmap<std::string, std::string>& hashmap) override;
    
    
    const std::string& getResult() const { return result; }
};

class setCommand : public baseCommand {
    std::string Key;
    std::string Value;
public:
    setCommand(std::string key, std::string value) 
        : Key(key), Value(value) {}
    
    void execute(Hashmap<std::string, std::string>& hashmap) override {
        hashmap.add(Key, Value);
        std::cout << "SET " << Key << " = " << Value << std::endl;
    }
};

class updateCommand : public baseCommand {
    std::string Key;
    std::string Value;
    bool success;
public:
    updateCommand(std::string key, std::string value) 
        : Key(key), Value(value), success(false) {}
    
    void execute(Hashmap<std::string, std::string>& hashmap) override;   
    
    bool isSuccessful() const { return success; }
};

class deleteCommand : public baseCommand {
    std::string Key;
    bool success;
public:
    deleteCommand(std::string key) : Key(key), success(false) {}
    
    void execute(Hashmap<std::string, std::string>& hashmap) override;
    bool isSuccessful() const { return success; }
};

#endif


