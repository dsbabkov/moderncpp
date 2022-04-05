#pragma once

#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class MyVector {
public:
    using iterator = T *;
    using const_iterator = const T *;

    MyVector() = default;

    void push_back(const T &value);
    size_t size() const;
    iterator begin();
    iterator end();

private:
    T *data_ = nullptr;
    size_t size_ = 0;
    Allocator allocator_;
};

template<typename T, typename Allocator>
void MyVector<T, Allocator>::push_back(const T &value) {
    T *newData_ = allocator_.allocate(size_ + 1);
    for (size_t i = 0; i < size_; ++i) {
        new(newData_ + i) T(std::move(data_[i]));
    }
    new(newData_ + size_) T(value);

    for (size_t i = 0; i < size_; ++i) {
        newData_[i].~T();
    }
    allocator_.deallocate(data_, size_);
    ++size_;
    data_ = newData_;
}

template<typename T, typename Allocator>
size_t MyVector<T, Allocator>::size() const {
    return size_;
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::iterator MyVector<T, Allocator>::begin() {
    return data_;
}

template<typename T, typename Allocator>
typename MyVector<T, Allocator>::iterator MyVector<T, Allocator>::end() {
    return data_ + size_;
}
