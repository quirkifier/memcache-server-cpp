#ifndef logger_h
#define logger_h
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include "sumairString.h"

/**
 * @class logger
 * @brief Responsible for logging cache operations and events to a file with timestamps.
 */
class logger {
    std::fstream logfile;

public:
    /**
     * @brief Default constructor.
     */
    logger() {}

    /**
     * @brief Initializes the logger by opening the specified log file.
     * @param filename Name of the log file to write to.
     */
    void initialize(const std::string& filename) {
        logfile.open(filename, std::ios::out | std::ios::app);
    }

    /**
     * @brief Closes the log file.
     */
    void cleanup() {
        logfile.close();
    }

    /**
     * @brief Logs a get command with key and value.
     * @param key The key retrieved.
     * @param value The value associated with the key.
     */
    void write_get_value(const string& key, const string& value) {
        logfile << "get command ";
        logfile << key << " " << value;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();
    }

    /**
     * @brief Logs a set command with key and value.
     * @param key The key to be stored.
     * @param value The value to be assigned.
     */
    void write_set_value(const string& key, const string& value) {
        logfile << "set command ";
        logfile << key << " " << value;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();
    }

    /**
     * @brief Logs an update command with key and the new value.
     * @param key The key to be updated.
     * @param new_value The new value to assign to the key.
     */
    void write_update_value(const string& key, const string& new_value) {
        logfile << "update command ";
        logfile << key << " " << new_value;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();
    }

    /**
     * @brief Logs a delete command for the given key.
     * @param key The key to be removed.
     */
    void write_delete_value(const string& key) {
        logfile << "delete command ";
        logfile << key;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();
    }

    /**
     * @brief Logs a custom event with timestamp.
     * @param current_update The event description string.
     */
    void write_current_event(const string& current_update) {
        logfile.write(current_update.isdata(), current_update.length());
        logfile.write(" current time", 12);
        time_t timestamp;
        time(&timestamp);
        logfile.write(ctime(&timestamp), 25);
        logfile.flush();
    }

    /**
     * @brief Logs an error message with timestamp.
     * @param error_message The error message to log.
     */
    void writeerror(const std::string& error_message) {
        logfile.write(error_message.data(), error_message.size());
        logfile.write(" current time", 12);
        time_t timestamp;
        time(&timestamp);
        logfile.write(ctime(&timestamp), 25);
        logfile.flush();
    }

private:
    // Intentionally left empty.
};

#endif // logger_h

