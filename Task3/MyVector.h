#pragma once

#include <memory>

template <typename T, typename Allocator = std::allocator<T>>
class MyVector {
public:
    using iterator = T *;
    using const_iterator = const T *;

    MyVector() = default;

    void push_back(const T &value) {
        T *newData_ = allocator_.allocate(size_ + 1);
        for (size_t i = 0; i < size_; ++i) {
            std::construct_at(newData_ + i, std::move(data_[i]));
            std::destroy_at(newData_ + i);
        }
        std::construct_at(newData_ + size_);
        allocator_.deallocate(data_, size_);
        ++size_;
        data_ = newData_;
    }

private:
    T *data_ = nullptr;
    size_t size_ = 0;
    Allocator allocator_;
};