#ifndef BINARY_FILE_HANDLER_H
#define BINARY_FILE_HANDLER_H

#include <iostream>
#include <fstream>
#include "sumairString.h"
#include "Hashmap.h"

template<typename Key, typename Value>
class BinaryFileHandler {
public:
    string filename;
    BinaryFileHandler(const string& file) : filename(file) {}

    bool file_exists() {
        std::ifstream file_stream(filename.isdata(), std::ios::binary);
        return file_stream.good();
    }

    string read_string() {
        std::ifstream file_stream(filename.isdata(), std::ios::binary);
        if (!file_stream.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for reading\n";
            return string();
        }

        size_t length{};
        file_stream.read(reinterpret_cast<char*>(&length), sizeof(length));
        if (file_stream.fail()) {
            std::cerr << "Error: Could not read string length\n";
            return string();
        }

        char* buffer = new char[length + 1];
        file_stream.read(buffer, length);
        buffer[length] = '\0';
        if (file_stream.fail()) {
            std::cerr << "Error: Could not read string data\n";
            delete[] buffer;
            return string();
        }
        file_stream.close();

        string result(buffer);
        delete[] buffer;
        return result;
    }

    bool save_string(const string& data) {
        std::ofstream file_stream(filename.isdata(), std::ios::binary);
        if (!file_stream.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing\n";
            return false;
        }

        size_t length = data.length();
        file_stream.write(reinterpret_cast<const char*>(&length), sizeof(length));
        file_stream.write(data.isdata(), length);
        if (file_stream.fail()) {
            std::cerr << "Error: Could not write to file\n";
            file_stream.close();
            return false;
        }
        file_stream.close();
        std::cout << "Saved custom string to binary: " << data << "\n";
        return true;
    }

    bool save_from_hashmap(Hashmap<Key, Value>& hashmap, const Key& key) {
        if (!hashmap.contains(key)) {
            std::cerr << "Error: Key '" << key << "' not found in hashmap\n";
            return false;
        }
        Value value = hashmap.get(key);
        string data = key.concat(string(" ")).concat(value);
        return save_string(data);
    }

    bool load_to_hashmap(Hashmap<Key, Value>& hashmap) {
        if (!file_exists()) {
            std::cerr << "Error: File '" << filename << "' does not exist\n";
            return false;
        }

        string raw = read_string();
        if (raw.isempty()) return false;

        int sep = raw.find_first(' ');
        if (sep < 0) {
            std::cerr << "Error: Invalid format in file. Expected 'key value'\n";
            return false;
        }

        Key key = raw.substr(0, sep);
        Value value = raw.substr(sep + 1, raw.length() - sep - 1);
        hashmap.add(key, value);
        std::cout << "Loaded from binary: " << key << " = " << value << "\n";
        return true;
    }
};

#endif // BINARY_FILE_HANDLER_H

