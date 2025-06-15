template <typename Key, typename Value> 
/*
*@brief A linked list node which keep on pointing to the next value until nullptr
* */
struct node {
    Key key;
    Value value;
    node *next;
    node(const Key &key, const Value &value)
        : key(key), value(value), next(nullptr) {}
};

template <typename Key, typename Value> 
/*
*
* @class LinkedList
* @brief A basic implementation of a linked list soley made for hashmap but does include a copyconstructor and a overloaded operator 
*
*/
class LinkedList {
    node<Key, Value> *head;
public:
    LinkedList() : head(nullptr) {}
    /*
    *
    * @brief copy constructor of a linked list
    *
    *
    */
    LinkedList(const LinkedList& other) : head(nullptr) {
        node<Key, Value>* current = other.head;
        node<Key, Value>* tail = nullptr;
        
        while (current) {
            node<Key, Value>* newNode = new node<Key, Value>(current->key, current->value);
            if (!head) {
                head = newNode;
                tail = newNode;
            } else {
                tail->next = newNode;
                tail = newNode;
            }
            current = current->next;
        }
    }
    
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            clear();
            node<Key, Value>* current = other.head;
            node<Key, Value>* tail = nullptr;
            
            while (current) {
                node<Key, Value>* newNode = new node<Key, Value>(current->key, current->value);
                if (!head) {
                    head = newNode;
                    tail = newNode;
                } else {
                    tail->next = newNode;
                    tail = newNode;
                }
                current = current->next;
            }
        }
        return *this;
    }
    /*
    *
    *@brief pushes a newnode inside the linked list
    */
    void insert(const Key &key, const Value &value) {
        node<Key, Value> *cur = new node<Key, Value>(key, value);
        cur->next = head;
        head = cur;
    }
    /*
    *
    *@brief finds the key that needs to be removed then makes the previous node next value attached to the deleted key next value
    *
    */
    
    bool remove(const Key &key) {
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
    /*
    *
    * @brief finds the key inside a node also the gets the value by passing by reference
    *
    *
    */
    
    bool find(const Key &key, Value& result) const {
        node<Key, Value> *current = head;
        while (current) {
            if (current->key == key) {
                result = current->value;
                return true;
            }
            current = current->next;
        }
        return false;
    }


    const Value* find_ptr(const Key &key) const {
        node<Key, Value> *current = head;
        while (current) {
            if (current->key == key) {
                return &(current->value);
            }
            current = current->next;
        }
        return nullptr;
    }
    
    void clear() {
        while (head) {
            node<Key, Value>* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    ~LinkedList() {
        clear();
    }
};
