#ifndef BASECOMMAND_H
#define BASECOMMAND_H

#include "Hashmap.h"
#include "sumairString.h"

/**
 * @class baseCommand
 * @brief Abstract base class for all command types.
 */
class baseCommand {
public:
    /**
     * @brief Executes the command on the given hashmap.
     * @param hashmap The hashmap on which the command operates.
     */
    virtual void execute(Hashmap<string, string>& hashmap) = 0;

    /**
     * @brief Default constructor for baseCommand.
     */
    baseCommand() = default;

    /**
     * @brief Virtual destructor.
     */
    virtual ~baseCommand() = default;
};

/**
 * @class getCommand
 * @brief Represents a get operation for a key.
 */
class getCommand : public baseCommand {
    string Key;
    string result;
public:
    /**
     * @brief Constructs a getCommand with the specified key.
     * @param key The key to be retrieved.
     */
    getCommand(string key);

    /**
     * @brief Executes the get operation.
     * @param hashmap The hashmap to perform the operation on.
     */
    void execute(Hashmap<string, string>& hashmap) override;

    /**
     * @brief Returns the result of the get operation.
     * @return The value corresponding to the key.
     */
    const string& getResult() const;
};

/**
 * @class setCommand
 * @brief Represents a set operation to store a key-value pair.
 */
class setCommand : public baseCommand {
    string Key;
    string Value;
    bool success;
public:
    /**
     * @brief Constructs a setCommand with the specified key and value.
     * @param key The key to be inserted.
     * @param value The value to be associated with the key.
     */
    setCommand(string key, string value);

    /**
     * @brief Executes the set operation.
     * @param hashmap The hashmap to perform the operation on.
     */
    void execute(Hashmap<string, string>& hashmap) override;

    /**
     * @brief Checks if the operation was successful.
     * @return true if set succeeded, false otherwise.
     */
    bool isSuccessful() const;
};

/**
 * @class updateCommand
 * @brief Represents an update operation to modify an existing key-value pair.
 */
class updateCommand : public baseCommand {
    string Key;
    string Value;
    bool success;
public:
    /**
     * @brief Constructs an updateCommand with the specified key and new value.
     * @param key The key to be updated.
     * @param value The new value to be associated with the key.
     */
    updateCommand(string key, string value);

    /**
     * @brief Executes the update operation.
     * @param hashmap The hashmap to perform the operation on.
     */
    void execute(Hashmap<string, string>& hashmap) override;

    /**
     * @brief Checks if the operation was successful.
     * @return true if update succeeded, false otherwise.
     */
    bool isSuccessful() const;
};

/**
 * @class deleteCommand
 * @brief Represents a delete operation to remove a key.
 */
class deleteCommand : public baseCommand {
    string Key;
    bool success;
public:
    /**
     * @brief Constructs a deleteCommand with the specified key.
     * @param key The key to be deleted.
     */
    deleteCommand(string key);

    /**
     * @brief Executes the delete operation.
     * @param hashmap The hashmap to perform the operation on.
     */
    void execute(Hashmap<string, string>& hashmap) override;

    /**
     * @brief Checks if the operation was successful.
     * @return true if delete succeeded, false otherwise.
     */
    bool isSuccessful() const;
};

#endif

