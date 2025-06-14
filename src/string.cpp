#include "sumairString.h"
#include <stdexcept>
#include <iostream>

int string::get_size(const char* s) const {
    if (s == nullptr) return 0;
    int i = 0;
    while(s[i] != '\0') {
        i++;
    }
    return i;
}
const char* string::isdata() const{
    return str;
}
// Default constructor
string::string() {
    len = 0;
    cap = 50;
    str = new char[cap];
    str[0] = '\0';
}

string::string(const char* s, int n) {
    if (s == nullptr) {
        cap = 50;
        len = 0;
        str = new char[cap];
        str[0] = '\0';
        return;
    }
    
    len = (n < 0) ? get_size(s) : n;
    cap = (len < 50) ? 50 : len + 1;
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s[i];
    }
    str[len] = '\0';
}
bool string::operator==(const char* other) const {
    int i = 0;
    while (other[i] && i < this->length()) {
        if (str[i] != other[i]) return false;
        i++;
    }
    return i == this->length() && other[i] == '\0';
}


string::string(const string &s) {
    if (s.str == nullptr) {
        cap = 0;
        len = 0;
        str = nullptr;
    } else {
        cap = s.cap;
        len = s.len;
        str = new char[cap];
        for (int i = 0; i < len; i++) {
            str[i] = s.str[i];
        }
        str[len] = '\0';
    }
}

string::string(const char* s) {
    if (s == nullptr) {
        cap = 50;
        len = 0;
        str = new char[cap];
        str[0] = '\0';
        return;
    }
    
    cap = 50;
    len = get_size(s);
    if (len >= cap) {
        cap = len + 1;
    }
    str = new char[cap];
    for (int i = 0; i < len; i++) {
        str[i] = s[i];
    }
    str[len] = '\0';
}

string::string(int n) {
    *this = itos(n);
}

string::~string() {
    delete[] str;
}
string& string::operator=(const std::string& s) {
        delete[] str; 
        len = s.size();
        str = new char[len + 1];
        std::copy(s.begin(), s.end(), str);
        str[len] = '\0';
    return *this; 
}
string& string::operator=(const string& s) {
    if (this == &s)
        return *this;
    
    delete[] str;
    
    if (s.str == nullptr) {
        cap = 0;
        len = 0;
        str = nullptr;
    } else {
        cap = s.cap;
        len = s.len;
        str = new char[cap];
        for (int i = 0; i < len; i++) {
            str[i] = s.str[i];
        }
        str[len] = '\0';
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const string& s) {
    os << s.str;
    return os;
}

bool string::isempty(){
    return get_size(str)==0;
}
std::istream& operator>>(std::istream& in, string& s) {
    char buffer[1024];
    in >> buffer;
    s = string(buffer);
    return in;
}

string string::operator+(const string& s) const {
    string result;
    result.len = len + s.len;
    result.cap = result.len + 1;
    result.str = new char[result.cap];
    
    for (int i = 0; i < len; i++) {
        result.str[i] = str[i];
    }
    for (int i = 0; i < s.len; i++) {
        result.str[len + i] = s.str[i];
    }
    result.str[result.len] = '\0';
    return result;
}

string& string::operator+=(const string& s) {
    int newLen = len + s.len;
    if (newLen >= cap) {
        cap = newLen * 2 + 1;
        char* newStr = new char[cap];
        for (int i = 0; i < len; i++) {
            newStr[i] = str[i];
        }
        delete[] str;
        str = newStr;
    }
    
    for (int i = 0; i < s.len; i++) {
        str[len + i] = s.str[i];
    }
    len = newLen;
    str[len] = '\0';
    return *this;
}

bool string::operator==(const string& m) const {
    if (m.len != len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (str[i] != m.str[i]) {
            return false;
        }
    }
    return true;
}

const char string::operator[](int i) const {
    if (i < 0 || i >= len) {
        throw std::out_of_range("Index out of bounds");
    }
    return str[i];
}

char& string::operator[](int i) {
    if (i < 0 || i >= len) {
        throw std::out_of_range("Index out of bounds");
    }
    return str[i];
}

string string::itos(int n) {
    if (n == 0) {
        string s("0");
        return s;
    }

    bool isNeg = false;
    if (n < 0) {
        isNeg = true;
        n = -n;
    }
    
    char buffer[20];
    int i = 0;
    while (n > 0) {
        buffer[i++] = '0' + (n % 10);
        n /= 10;
    }
    
    if (isNeg) {
        buffer[i++] = '-';
    }
    buffer[i] = '\0';
    
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
    
    return string(buffer);
}

string string::insert_char(int n, char ch) {
    if (n < 0 || n > len) {
        throw std::out_of_range("Position out of range");
    }
    
    if (len + 1 >= cap) {
        cap = cap * 2 + 1;
        char* newStr = new char[cap];
        for (int i = 0; i < len; i++) {
            newStr[i] = str[i];
        }
        delete[] str;
        str = newStr;
    }
    
    for (int i = len; i > n; i--) {
        str[i] = str[i - 1];
    }
    str[n] = ch;
    len++;
    str[len] = '\0';
    return *this;
}

string string::insert_string(int n, const string& sub) {
    if (n < 0 || n > len) {
        throw std::out_of_range("Position out of range");
    }
    
    int newLen = len + sub.len;
    if (newLen >= cap) {
        cap = newLen * 2 + 1;
        char* newStr = new char[cap];
        
        for (int i = 0; i < n; i++) {
            newStr[i] = str[i];
        }
        
        for (int i = 0; i < sub.len; i++) {
            newStr[n + i] = sub.str[i];
        }
        
        for (int i = n; i < len; i++) {
            newStr[i + sub.len] = str[i];
        }
        
        delete[] str;
        str = newStr;
        len = newLen;
        str[len] = '\0';
    } else {
        for (int i = len - 1; i >= n; i--) {
            str[i + sub.len] = str[i];
        }
        
        for (int i = 0; i < sub.len; i++) {
            str[n + i] = sub.str[i];
        }
        
        len += sub.len;
        str[len] = '\0';
    }
    
    return *this;
}

string& string::replace_first(char ch) {
    if (len > 0)
        str[0] = ch;
    return *this;
}

void string::to_upper() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            str[i] -= 32;
        }
    }
}

void string::to_lower() {
    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] += 32;
        }
    }
}

string& string::trim() {
    int start = 0;
    int end = len - 1;
    while (start < len && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n')) {
        start++;
    }
    while (end >= start && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n')) {
        end--;
    }
    int new_len = end - start + 1;
    for (int i = 0; i < new_len; i++) {
        str[i] = str[start + i];
    }
    str[new_len] = '\0';
    len = new_len;
    return *this;
}

int string::stoi() const {
    int i = 0;
    int num = 0;
    bool isNeg = false;
    if (str[0] == '-') {
        isNeg = true;
        i = 1;
    }
    while (i < len) {
        if (str[i] < '0' || str[i] > '9') {
            throw std::invalid_argument("Invalid character in integer string");
        }
        num = num * 10 + (str[i] - '0');
        i++;
    }
    return isNeg ? -num : num;
}

void string::display() const {
    std::cout << str;
}

bool string::is_equal(const string& m) const {
    if (m.len != len) {
        return false;
    }
    for (int i = 0; i < len; i++) {
        if (str[i] != m.str[i]) {
            return false;
        }
    }
    return true;
}

bool string::is_less(const string& m) const {
    int min_len = (len < m.len) ? len : m.len;
    for (int i = 0; i < min_len; i++) {
        if (str[i] < m.str[i]) {
            return true;
        }
        if (str[i] > m.str[i]) {
            return false;
        }
    }
    return len < m.len;
}

bool string::is_greater(const string& m) const {
    int min_len = (len < m.len) ? len : m.len;
    for (int i = 0; i < min_len; i++) {
        if (str[i] > m.str[i]) {
            return true;
        }
        if (str[i] < m.str[i]) {
            return false;
        }
    }
    return len > m.len;
}

string string::concat(const string& s) const {
    return *this + s;
}

string string::lower() const {
    string copy(*this);
    copy.to_lower();
    return copy;
}

string* string::split(char delimiter, int &count) const {
    count = 1;
    for (int i = 0; i < len; i++) {
        if (str[i] == delimiter) {
            count++;
        }
    }
    
    string* splitArr = new string[count];
    int current = 0;
    int start = 0;
    
    for (int i = 0; i <= len; i++) {
        if (i == len || str[i] == delimiter) {
            int substrLen = i - start;
            splitArr[current] = string(&str[start], substrLen);
            start = i + 1;
            current++;
        }
    }
    
    return splitArr;
}

string* string::split(const string& delimiters, int &count) const {
    count = 1;
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < delimiters.len; j++) {
            if (str[i] == delimiters.str[j]) {
                count++;
                break;
            }
        }
    }
    
    string* splitArr = new string[count];
    int current = 0;
    int start = 0;
    
    for (int i = 0; i <= len; i++) {
        bool isDelim = false;
        if (i < len) {
            for (int j = 0; j < delimiters.len; j++) {
                if (str[i] == delimiters.str[j]) {
                    isDelim = true;
                    break;
                }
            }
        }
        
        if (i == len || isDelim) {
            int substrLen = i - start;
            splitArr[current] = string(&str[start], substrLen);
            start = i + 1;
            current++;
        }
    }
    
    return splitArr;
}

void string::remove_char(int n) {
    if (n < 0 || n >= len) return;
    
    for (int i = n; i < len - 1; i++) {
        str[i] = str[i + 1];
    }
    len--;
    str[len] = '\0';
}

void string::remove_first(char ch) {
    int first = find_first(ch);
    if (first != -1) {
        remove_char(first);
    }
}

void string::remove_last(char ch) {
    int last = find_last(ch);
    if (last != -1) {
        remove_char(last);
    }
}

void string::remove_all(char a) {
    int newLen = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] != a) {
            str[newLen++] = str[i];
        }
    }
    len = newLen;
    str[len] = '\0';
}

int* string::all_sub_string(const string& sub, int &count) const {
    int* temp = new int[len];
    count = 0;
    for (int i = 0; i <= len - sub.len; i++) {
        bool match = true;
        for (int j = 0; j < sub.len; j++) {
            if (str[i + j] != sub.str[j]) {
                match = false;
                break;
            }
        }
        if (match) {
            temp[count++] = i;
        }
    }
    return temp;
}

int string::find_first(char ch) const {
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            return i;
        }
    }
    return -1;
}

int string::find_last(char ch) const {
    for (int i = len - 1; i >= 0; i--) {
        if (str[i] == ch) {
            return i;
        }
    }
    return -1;
}

int* string::find_all(char ch, int &count) const {
    int* temp = new int[len];
    count = 0;
    for (int i = 0; i < len; i++) {
        if (str[i] == ch) {
            temp[count++] = i;
        }
    }
    return temp;
}

string string::regrow() {
    int newCap = cap * 2;
    char* newStr = new char[newCap];
    
    for (int i = 0; i < len; i++) {
        newStr[i] = str[i];
    }
    newStr[len] = '\0';
    
    delete[] str;
    str = newStr;
    cap = newCap;
    
    return *this;
}

int string::length() const {
    return len;
}

void string::clear() {
    len = 0;
    if (str != nullptr) {
        str[0] = '\0';
    }
}

string string::substr(int start, int length) const {
    if (start < 0 || start >= len) {
        throw std::out_of_range("Start index out of range");
    }
    
    if (length < 0 || (start + length) > len) {
        length = len - start;
    }
    
    string result;
    result.len = length;
    result.cap = length + 1;
    result.str = new char[result.cap];
    
    for (int i = 0; i < length; i++) {
        result.str[i] = str[start + i];
    }
    result.str[length] = '\0';
    
    return result;
}
