/** 
 * @file my_data_structure_library/include/dynamic_array.h
 *  This is the header for declaration of class dynamic_array.
 */

#ifndef MY_DATA_STRUCTURE_LIBRARY_INCLUDE_DYNAMIC_ARRAY_H_
#define MY_DATA_STRUCTURE_LIBRARY_INCLUDE_DYNAMIC_ARRAY_H_

#include <stddef.h> // size_t;

namespace mydsl {

/**
 * dynamic_array is a class that implements the data structure dynamic array,
 * a variable length array. So it may reallocate its memory
 * when the number of elements exceeds the current capacity
 */
template <class T>
class dynamic_array {
public:
    // The value that is not index of array,
    // which is used in function find_first and find_last.
    constexpr size_t not_index = static_cast<size_t>(-1);

private:
    T *data_ = nullptr;    // pointer holding array's memory
    size_t capacity_ = 0;  // the maximum number of elements the array can hold
    size_t size_ = 0;      // the number of elements in the array

public:
    dynamic_array() = default;
    dynamic_array(size_t size);
    dyanmic_array(size_t size, const T &value);
    ~dynamic_array();
    dynamic_array(const dynamic_array &other);
    dynamic_array &operator = (const dynamic_array &other);

public:
    T *data();
    const T *data() const;
    size_t capacity() const;
    size_t size() const;
    bool empty() const;
    const T &at(size_t index) const;
    T &at(size_t index);
    const T &front() const;
    T &front();
    const T &back() const;
    T &back();
    size_t find_first(const T& value) const;
    size_t find_last(const T& value) const;
    void update_at(size_t index, const T &value);
    void fill(const T &value);
    void insert_at(size_t index, const T &value);
    void push_back(const T &value);
    void delete_at(size_t index);
    void delete_equal(const T &value);
    void pop_back();
    void clear();
    void shrink();
    void resize(size_t size);

private:
    bool full() const;
    void reallocate(size_t capacity);

public:
    T operator [] (size_t index) const;
    T &operator [] (size_t index);
};

} // namespace mydsl

#endif // MY_DATA_STRUCTURE_LIBRARY_INCLUDE_DYNAMIC_ARRAY_H_