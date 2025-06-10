#include <iostream>
template <typename Key, typename Value> struct node {
  Key key;
  Value value;
  node *next;
  node(const Key &key, const Value &value)
      : key(key), value(value), next(nullptr) {}
};
template <typename Key, typename Value> 
class LinkedList {
  node<Key, Value> *head;

public:
  LinkedList() : head(nullptr) {}
  void insert(const Key &key, const Value &value) {
    node<Key, Value> *cur = new node<Key, Value>(key, value);
    cur->next = head;
    head = cur;
  }
  bool remove(const Key &key ) {
    node<Key, Value> *current = head;
    node<Key, Value> *previous = nullptr;
    while (current) {
      if (current->key == key) {
        if (previous) {
          previous->next = current->next;
        } else {
          head = current->next;
        }
        delete current;
        return true;
      }
      previous = current;
      current = current->next;
    }
    return false;
  }
  node<Key, Value>* find(const Key &key) {
    node<Key, Value> *current = head;
    while (current) {
        if (current->key == key)
          return current;

        current = current->next;
    }
    return nullptr;
  }
};
