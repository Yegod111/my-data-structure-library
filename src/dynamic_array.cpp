#include "include/dyanmic_array.h"

#include <new>       // std::bad_alloc
#include <iostream>  // std::cerr
#include <stdexcept> // std::out_of_range()
#include <cstdlib>   // std::exit()

namespace mydsl {

// Constructs with a certain size.
template <class T>
dynamic_array<T>::dynamic_array(size_t size) {
    try {
        data_ = new T[size];
    } catch (const std::bad_alloc &e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    capacity_ = size;
    size_ = size;
}

// Constructs with a certain size and fills the certain value.
template <class T>
dynamic_array<T>::dynamic_array(size_t size, const T &value) {
    try {
        data_ = new T[size];
    } catch (const std::bad_alloc &e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    capacity_ = size;
    size_ = size;
    fill(value);
}

template <class T>
dynamic_array<T>::~dynamic_array() {
    delete[] data();
}

// Copy constructor.
template <class T>
dynamic_array<T>::dynamic_array(const dynamic_array<T> &other) {
    if (this == &other) {
        return;
    }
    clear();
    for (size_t i = 0; i < other.size(); ++i) {
        push_back(other.at(i));
    }
}

// Assignment operator.
template <class T>
dynamic_array<T> &dynamic_array<T>::operator = (const dynamic_array<T> &other) {
    dynamic_array(other);
    return *this;
}

// Returns the raw pointer to the array.
template <class T>
T *dynamic_array<T>::data() {
    return data_;
}

// Returns the constant raw pointer to the array.
template <class T>
const T *dynamic_array<T>::data() const {
    return static_cast<const T *>(data_);
}

// Returns the maximum number of elements the array can hold.
template <class T>
size_t dynamic_array<T>::capacity() const {
    return capacity_;
}

// Returns the number of elements in the array. 
template <class T>
size_t dynamic_array<T>::size() const {
    return size_;
}

// Returns true if array is empty.
template <class T>
bool dynamic_array<T>::empty() const {
    return size() == 0;
}

// Accesses element at index.
template <class T>
const T &dynamic_array<T>::at(size_t index) const {
    if (index >= size()) {
        throw std::out_of_range("dynamic_array index out of bounds!");
    }
    return *(data() + index);
}

// Accesses element at index.
template <class T>
T &dynamic_array<T>::at(size_t index) {
    if (index >= size()) {
        throw std::out_of_range("dynamic_array index out of bounds!");
    }
    return *(data() + index);
}

// Returns the first element.
template <class T>
const T &dynamic_array<T>::front() const {
    if (empty()) {
        throw std::out_of_range("dynamic_array is empty!");
    }
    return *data();
}

// Returns the first element.
template <class T>
T &dynamic_array<T>::front() {
    if (empty()) {
        throw std::out_of_range("dynamic_array is empty!");
    }
    return *data();
}

// Returns the last element.
template <class T>
const T &dynamic_array<T>::back() const {
    if (empty()) {
        throw std::out_of_range("dynamic_array is empty!");
    }
    return *(data() + size() - 1);
}

// Returns the last element.
template <class T>
T &dynamic_array<T>::back() {
    if (empty()) {
        throw std::out_of_range("dynamic_array is empty!");
    }
    return *(data() + size() - 1);
}

// Returns the index of the first element that equals value.
template <class T>
size_t dynamic_array<T>::find_first(const T &value) const {
    for (size_t i = 0; i < size(); ++i) {
        if (at(i) == value) {
            return i;
        }
    }
    return not_index;
}

// Returns the index of the last element that equals value.
template <class T>
size_t dynamic_array<T>::find_last(const T &value) const {
    for (size_t i = size() - 1; ~i; --i) {
        if (at(i) == value) {
            return i;
        }
    }
    return not_index;
}

// Updates the element at index.
template <class T>
void dynamic_array<T>::update_at(size_t index, const T &value) {
    at(index) = value;
}

// Fills the array with value.
template <class T>
void dynamic_array<T>::fill(const T &value) {
    for (size_t i = 0; i < size(); ++i) {
        at(i) = value;
    }
}

// Inserts an element at index.
template <class T>
void dynamic_array<T>::insert_at(size_t index, const T &value) {
    if (index > size()) {
        throw std::out_of_range("dynamic_array index out of bounds!");
    }
    push_back(value);
    for (size_t i = size() - 1; i > index; --i) {
        at(i) = at(i - 1);
    }
    at(index) = value;
}

// Inserts an element at the end of the array.
template <class T>
void dynamic_array<T>::push_back(const T &value) {
    if (full()) {
        reallocate(static_cast<size_t>(capacity() == 0 ? 1 : capacity() * 2));
    }
    *(data() + size_++) = value;
}

// Deletes the element at index.
template <class T>
void dynamic_array<T>::delete_at(size_t index) {
    if (index >= size()) {
        throw std::out_of_range("dynamic_array index out of bounds!");
    }
    for (size_t i = index; i + 1 < size(); ++i) {
        at(i) = at(i + 1);
    }
    --size_;
}

// Deletes all the elements that equal to value.
template <class T>
void dynamic_array<T>::delete_equal(const T &value) {
    size_t j = 0;
    for (size_t i = 0; i < size(); ++i) {
        if (at(i) != value) {
            at(j++) = at(i);
        }
    }
    size_ = j;
}

// Deletes the last element.
template <class T>
void dynamic_array<T>::pop_back() {
    if (empty()) {
        throw std::out_of_range("dynamic_array is empty!");
    }
    --size_;
}

// Sets the size zero.
template <class T>
void dynamic_array<T>::clear() {
    size_ = 0;
}

// Shrinks memory of the array to the number of elements in it. 
template <class T>
void dynamic_array<T>::shrink() {
    reallocate(size());
}

// Sets the array a certain size.
template <class T>
void dynamic_array<T>::resize(size_t size) {
    if (size > capacity()) {
        reallocate(size);
    }
    size_ = size;
}

// Returns true if the array is full.
template <class T>
bool dynamic_array<T>::full() const {
    return size() == capacity();
}

// Reallocate memory to the array with certain size.
template <class T>
void dynamic_array<T>::reallocate(size_t capacity) {
    if (capacity == capcity()) {
        return;
    }
    try  {
        T *new_data = new T[capacity];
        if (size() > capacity) {
            size_ = capacity;
        }
        for (size_t i = 0; i < size(); ++i) {
            *(new_data + i) = at(i);
        }
        delete[] data_;
    } catch (const std::bad_alloc &e) {
        std::cerr << "Memory allocation failed: " << e.what() << std::endl;
        std::exit(EXIT_FAILURE);
    }
    data_ = new_data;
    capacity_ = capacity;
}

// Accesses element.
template <class T>
T dynamic_array<T>::operator [] (size_t index) const {
    return *(data() + index);
}

// Accesses element.
template <class T>
T &dynamic_array<T>::operator [] (size_t index) {
    return *(data() + index);
}

}