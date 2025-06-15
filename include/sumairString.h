#ifndef SUMAIRSTRING_H
#define SUMAIRSTRING_H
#include <iostream>
#include<string>
class string {
    int len{};
    int cap{};
    char *str{};
public:
    string();
    string(const char* s,int n);
    string(const string &s);
    string(const char* s );
    string(int n);
    friend std::istream& getline(std::istream& in, string& s);

    //operator overload
    friend std::ostream& operator<<(std::ostream& os, const string& s);
    friend std::istream& operator>>(std::istream& in, string& s);
    string operator+(const string& s) const;
    string& operator+=(const string& s);
    string& operator=(const string& s);
    string& operator=(const std::string& s);
    bool operator==(const string& s) const;
    bool operator==(const char* s) const;
    const char operator[](int i) const;
    char & operator[](int i );
    //utility functions
    static string itos(int n);
    string insert_char(int n, char s);
    string insert_string(int n, const string& sub);
    string & replace_first(char s);
    int get_size(const char* s ) const;
    void to_upper() ;
    void to_lower();
    string& trim();
    int stoi() const;
    bool isempty();
    const char* isdata() const;
    void display() const;
    string lower() const;  // Returns a lowercased copy of the string
    ~string();
    [[nodiscard]] bool is_equal(const string& m ) const;
    [[nodiscard]] bool is_less(const string& m) const;
    string substr(int start, int length) const;

    [[nodiscard]] bool is_greater(const string& m) const;
    [[nodiscard]] string concat(const string& s) const;
    string *split(char s,int &count) const ;
    string* split(const string& s, int &count) const;
    void remove_char(int n );
    void remove_first(char s);
    void remove_last(char s);
    void remove_all(char a);
    int* all_sub_string(const string& s,int & count) const;
    [[nodiscard]] int find_first(char s) const;
    [[nodiscard]] int find_last(char s) const ;
    int* find_all(char s,int &count) const;
    string regrow();
    [[nodiscard]] int length()  const;
    void clear();
};

#endif //SUMAIRSTRING_H

