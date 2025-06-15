#ifndef BASECOMMAND_H

#define BASECOMMAND_H
#include "Hashmap.h"
#include "sumairString.h"
class baseCommand {
public:
    virtual void execute(Hashmap<string, string>& hashmap) = 0;
    baseCommand() = default;
    virtual ~baseCommand() = default;
};

class getCommand : public baseCommand {
    string Key;
    string result;
public:
    getCommand(string key) : Key(key) {}
    
    void execute(Hashmap<string, string>& hashmap) override;
    
    const string& getResult() const { return result; }
};

class setCommand : public baseCommand {
    string Key;
    string Value;
    bool success;
public:
    setCommand(string key, string value) 
        : Key(key), Value(value) {}
    
  void execute(Hashmap<string, string>& hashmap) override;
};

class updateCommand : public baseCommand {
    string Key;
    string Value;
    bool success;
public:
    updateCommand(string key, string value) 
        : Key(key), Value(value), success(false) {}
    
    void execute(Hashmap<string, string>& hashmap) override;   
    
    bool isSuccessful() const { return success; }
};

class deleteCommand : public baseCommand {
    string Key;
    bool success;
public:
    deleteCommand(string key) : Key(key), success(false) {}
    
    void execute(Hashmap<string, string>& hashmap) override;
    bool isSuccessful() const { return success; }
};

#endif


