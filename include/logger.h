#ifndef logger_h
#define logger_h
#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include "sumairString.h"

class logger {
    std::fstream logfile;
public:
    logger(){}
    void initialize(const std::string& filename) {
        logfile.open(filename, std::ios::out | std::ios::app);
    }

    void cleanup() {
        logfile.close();
    }

    void write_get_value(const string& key, const string& value) {
        logfile << "get command ";
        logfile << key << " " << value;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();
    }

    void write_set_value(const string& key, const string& value) {
        logfile << "set command ";
        logfile << key << " " << value;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();

    }

    void write_update_value(const string& key, const string& new_value) {
        logfile << "update command ";
        logfile << key << " " << new_value;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();

    }

    void write_delete_value(const string& key) {
        logfile << "delete command ";
        logfile << key;
        time_t timestamp;
        time(&timestamp);
        logfile << ctime(&timestamp) << " \n";
        logfile.flush();
    }

    void write_current_event(const string& current_update) {
        logfile.write(current_update.isdata(), current_update.length());
        logfile.write(" current time", 12);
        time_t timestamp;
        time(&timestamp);
        logfile.write(ctime(&timestamp), 25);
        logfile.flush();
    }

    void writeerror(const std::string& error_message) {
        logfile.write(error_message.data(), error_message.size());
        logfile.write(" current time", 12);
        time_t timestamp;
        time(&timestamp);
        logfile.write(ctime(&timestamp), 25);
        logfile.flush();
    }

private:
};

#endif // logger_h

