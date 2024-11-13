#include <ostream>
#include "List.h"
#include "Node.h"

template <typename T>
class ListLinked : public List<T> {

    private:
 
        Node<T>* first;
        int n;

    public:

    ListLinked(){
        first = nullptr;
        n = 0;
    }
    ~ListLinked(){
        Node<T>* current = first;
        while(current != nullptr){
            Node<T>* next = current->next;
            delete current;
            current = next;
        }
    }

    T operator[](int pos) {
        if(pos < 0 || pos >= n){
            throw std::out_of_range("Index out of bounds");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }

    friend std::ostream& operator<<(std::ostream &out, const ListLinked<T> &list){
        Node<T>* current = list.first;
        out << "[";
        while(current != nullptr){
            out << current->data;
            if(current->next != nullptr){
                out << ", ";
            }
            current = current->next;
        }
        out << "]";
        return out;
    }

    void insert(int pos, T element) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* new_node = new Node<T>(element);
        if (pos == 0) {
            new_node->next = first;
            first = new_node;
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            new_node->next = current->next;
            current->next = new_node;
        }
        ++n;
    }

    void append(T element) override {
        insert(n, element);
    }

    void prepend(T element) override {
        insert(0, element);
    }

    T remove(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* removed;
        if (pos == 0) {
            removed = first;
            first = first->next;
        } else {
            Node<T>* current = first;
            for (int i = 0; i < pos - 1; ++i) {
                current = current->next;
            }
            removed = current->next;
            current->next = removed->next;
        }
        T element = removed->data;
        delete removed;
        --n;
        return element;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Index out of range");
        }
        Node<T>* current = first;
        for (int i = 0; i < pos; ++i) {
            current = current->next;
        }
        return current->data;
    }
    
    int search(T element) override {
        Node<T>* current = first;
        for (int i = 0; i < n; ++i) {
            if (current->data == element) {
                return i;
            }
            current = current->next;
        }
        return -1;
    }
    
    bool empty() override {
        return n == 0;
    }

    int size() override {
        return n;
    }
};