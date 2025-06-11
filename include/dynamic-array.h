#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H
#include <stdexcept>
#include <utility>

template <typename T> 
class Dynamic_array {
    T *arr;
    int len;
    int cap;
    
    void double_capacity() {
        int new_cap = (cap == 0) ? 1 : cap * 2;
        T *new_arr = new T[new_cap];
        for (int i = 0; i < len; i++) {
            new_arr[i] = arr[i];
        }
        delete[] arr;
        arr = new_arr;
        cap = new_cap;
    }
    
public:
    Dynamic_array() : arr(nullptr), len(0), cap(0) {}
    
    Dynamic_array(int count, T value) {
        len = count;
        cap = count;
        if (cap > 0) {
            arr = new T[cap];
            for (int i = 0; i < len; i++) {
                arr[i] = value;
            }
        } else {
            arr = nullptr;
        }
    }
    
    Dynamic_array(int count) {
        len = count;
        cap = count;
        if (cap > 0) {
            arr = new T[cap];
        } else {
            arr = nullptr;
        }
    }
    
    Dynamic_array(const Dynamic_array<T> &other) {
        len = other.len;
        cap = other.cap;
        if (cap > 0) {
            arr = new T[cap];
            for (int i = 0; i < len; i++) {
                arr[i] = other.arr[i];
            }
        } else {
            arr = nullptr;
        }
    }
    
    ~Dynamic_array() { 
        delete[] arr; 
    }
    
   
    Dynamic_array<T> &operator=(const Dynamic_array<T> &other) {
        if (this != &other) {
            delete[] arr;
            len = other.len;
            cap = other.cap;
            if (cap > 0) {
                arr = new T[cap];
                for (int i = 0; i < len; i++) {
                    arr[i] = other.arr[i];
                }
            } else {
                arr = nullptr;
            }
        }
        return *this;
    }
    
  
    T &operator[](int index) { return arr[index]; }
    const T &operator[](int index) const { return arr[index]; }
    
    T &at(int index) {
        if (index < 0 || index >= len) {
            throw std::out_of_range("Dynamic_array::at(): index out of range");
        }
        return arr[index];
    }
    
    const T &at(int index) const {
        if (index < 0 || index >= len) {
            throw std::out_of_range("Dynamic_array::at(): index out of range");
        }
        return arr[index];
    }
    
    T &front() {
        if (len == 0) {
            throw std::out_of_range("Dynamic_array::front(): empty array");
        }
        return arr[0];
    }
    
    const T &front() const {
        if (len == 0) {
            throw std::out_of_range("Dynamic_array::front(): empty array");
        }
        return arr[0];
    }
    
    T &back() {
        if (len == 0) {
            throw std::out_of_range("Dynamic_array::back(): empty array");
        }
        return arr[len - 1];
    }
    
    const T &back() const {
        if (len == 0) {
            throw std::out_of_range("Dynamic_array::back(): empty array");
        }
        return arr[len - 1];
    }
    

    bool operator==(const Dynamic_array<T> &other) const {
        if (len != other.len) return false;
        for (int i = 0; i < len; i++) {
            if (arr[i] != other.arr[i]) return false;
        }
        return true;
    }
    
    bool operator!=(const Dynamic_array<T> &other) const {
        return !(*this == other);
    }
    

    void push(T value) {
        if (len + 1 > cap) {
            double_capacity();
        }
        arr[len++] = value;
    }
    
    void pop() {
        if (len > 0) {
            --len;
        }
    }
    
    void insert_at(int index, T value) {
        if (index < 0 || index > len) {
            throw std::out_of_range("Dynamic_array::insert_at(): index out of range");
        }
        if (len + 1 > cap) {
            double_capacity();
        }
        for (int i = len; i > index; --i) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        ++len;
    }
    
    void delete_at(int index) {
        if (index < 0 || index >= len) {
            throw std::out_of_range("Dynamic_array::delete_at(): index out of range");
        }
        for (int i = index; i < len - 1; i++) {
            arr[i] = arr[i + 1];
        }
        --len;
    }
    
    void reserve(int new_capacity) {
        if (new_capacity > cap) {
            T *new_arr = new T[new_capacity];
            for (int i = 0; i < len; i++) {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
            cap = new_capacity;
        }
    }
    
    void clear() {
        delete[] arr;
        arr = nullptr;
        len = 0;
        cap = 0;
    }
    
    void swap(Dynamic_array<T> &other) {
        std::swap(arr, other.arr);
        std::swap(len, other.len);
        std::swap(cap, other.cap);
    }
    

    void shrink_to_fit() {
        if (len == 0) {
            delete[] arr;
            arr = nullptr;
            cap = 0;
        } else if (len < cap) {
            T *temp = new T[len];
            for (int i = 0; i < len; i++) {
                temp[i] = arr[i];
            }
            delete[] arr;
            arr = temp;
            cap = len;
        }
    }
    
    void reverse() {
        for (int i = 0; i < len / 2; i++) {
            std::swap(arr[i], arr[len - 1 - i]);
        }
    }
    

    bool empty() const { return len == 0; }
    int size() const { return len; }
    

    int find(const T &value) const {
        for (int i = 0; i < len; i++) {
            if (arr[i] == value) return i;
        }
        return -1;
    }
    

    Dynamic_array<T> operator+(const Dynamic_array<T> &other) const {
        Dynamic_array temp;
        temp.len = this->len + other.len;
        temp.cap = temp.len;
        if (temp.cap > 0) {
            temp.arr = new T[temp.cap];
            for (int i = 0; i < len; i++) {
                temp.arr[i] = arr[i];
            }
            for (int i = 0; i < other.len; i++) {
                temp.arr[len + i] = other.arr[i];
            }
        }
        return temp;
    }
    
    Dynamic_array<T> &operator+=(const Dynamic_array<T> &other) {
        if (other.len > 0) {
            T *new_arr = new T[len + other.len];
            for (int i = 0; i < len; i++) {
                new_arr[i] = arr[i];
            }
            for (int i = 0; i < other.len; i++) {
                new_arr[len + i] = other.arr[i];
            }
            delete[] arr;
            arr = new_arr;
            len += other.len;
            cap = len;
        }
        return *this;
    }
};

#endif // DYNAMIC_ARRAY_H

