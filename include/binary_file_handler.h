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
        std::ifstream file(filename.isdata());
        return file.good();
    }
    bool save_all(const Dynamic_array<Key>& keys, Hashmap<Key, Value>& store) {
        std::ofstream file(filename.isdata(), std::ios::binary);
        int count = keys.size();
        file.write((char*)(&count), sizeof(count));
        for (int i = 0; i < keys.size(); i++) {
            Key key = keys[i];
            Value value = store.get(key);
            
            string key_str = key;
            string value_str = value;
            
            int key_len = key_str.length();
            file.write(reinterpret_cast<const char*>(&key_len), sizeof(key_len));
            file.write(key_str.isdata(), key_len);
            
            int value_len = value_str.length();
            file.write(reinterpret_cast<const char*>(&value_len), sizeof(value_len));
            file.write(value_str.isdata(), value_len);
        }
        
        file.close();
        std::cout << "Saved " << count << " entries to binary file\n";
        return true;
    }
    
    bool load_all(Dynamic_array<Key>& keys, Hashmap<Key, Value>& store) {
        std::ifstream file(filename.isdata(), std::ios::binary);
        int count = 0;
        file.read((char*)(&count), sizeof(count));
        for (int i = 0; i < count; i++) {
            int key_len = 0;
            file.read((char*)(&key_len), sizeof(key_len));
            char* key_buffer = new char[key_len + 1];
            file.read(key_buffer, key_len);
            key_buffer[key_len] = '\0';
            Key key = Key(key_buffer);
            delete[] key_buffer;
            int value_len = 0;
            file.read((char*)(&value_len), sizeof(value_len));
            char* value_buffer = new char[value_len + 1];
            file.read(value_buffer, value_len);
            value_buffer[value_len] = '\0';
            Value value = Value(value_buffer);
            delete[] value_buffer;
            store.add(key, value);
            keys.push(key);
        }
        file.close();
        return true;
    }
};

#endif // BINARY_FILE_HANDLER_H

