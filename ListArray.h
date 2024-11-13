#include "List.h"
#include <stdexcept>
#include <iostream>
#include <ostream>

template <typename T>
class ListArray : public List<T> {
private:
    T* array;
    int max;
    int n;
    static const int MINSIZE = 2;

    void resize(int new_size) {
        T* new_array = new T[new_size];
        for (int i = 0; i < n; ++i) {
            new_array[i] = array[i];
        }
        delete[] array;
        array = new_array;
        max = new_size;
    }

public:
    ListArray() : max(MINSIZE), n(0) {
        array = new T[MINSIZE];
    }

    ~ListArray() {
        delete[] array;
    }

    void insert(int pos, T element) override {
        if (pos < 0 || pos > n) {
            throw std::out_of_range("Index out of bounds");
        }
        if (n == max) {
            resize(max * 2);
        }
        for (int i = n; i > pos; --i) {
            array[i] = array[i - 1];
        }
        array[pos] = element;
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
            throw std::out_of_range("Index out of bounds");
        }
        T removed_element = array[pos];
        for (int i = pos; i < n - 1; ++i) {
            array[i] = array[i + 1];
        }
        --n;
        return removed_element;
    }

    T get(int pos) override {
        if (pos < 0 || pos >= n) {
            throw std::out_of_range("Index out of bounds");
        }
        return array[pos];
    }

    int search(T element) override {
        for (int i = 0; i < n; ++i) {
            if (array[i] == element) {
                return i;
            }
        }
        return -1;
    }

    int size() override {
        return n;
    }

    bool empty() override {
        return n == 0;
    }

    T& operator[](int pos) {
        if(pos < 0 || pos >= n){
            throw std::out_of_range("Index out of bounds");
        }
        return array[pos];
    }

    friend std::ostream& operator<<(std::ostream& os, const ListArray<T>& list) {
        for (int i = 0; i < list.n; ++i) {
            os << list.array[i];
            if (i < list.n - 1) {
                os << ", ";
            }
        }
        return os;
    }
};