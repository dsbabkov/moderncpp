#pragma once

#include <iostream>
#include <memory>
#include <bitset>

template <typename T, size_t ObjectsCapacity>
class MyAllocator {
public:
    using value_type = T;
    MyAllocator();
    MyAllocator(const MyAllocator &o);
    MyAllocator(MyAllocator &&o) noexcept;
    template<typename U>
    MyAllocator(const MyAllocator<U, ObjectsCapacity> &o);
    template<typename U>
    MyAllocator(MyAllocator<U, ObjectsCapacity> &&o);
    ~MyAllocator();

    void report();

    template <typename U>
    struct rebind {
        using other = MyAllocator<U, ObjectsCapacity>;
    };

    T *allocate(std::size_t n);

    void deallocate(T* p, std::size_t n) noexcept;

private:
    void *data_ = nullptr;
    std::bitset<ObjectsCapacity> free_;
};

template<typename T, size_t ObjectsCapacity>
MyAllocator<T, ObjectsCapacity>::MyAllocator() {
    std::cout << "Construct " << typeid(MyAllocator).name() << '\n';
}

template<typename T, size_t ObjectsCapacity>
MyAllocator<T, ObjectsCapacity>::~MyAllocator() {
    std::cout << "Destruct " << typeid(MyAllocator).name() << '\n';
    report();
    std::free(data_);
}

template<typename T, size_t ObjectsCapacity>
MyAllocator<T, ObjectsCapacity>::MyAllocator(const MyAllocator &o) {
    std::cout << "Copy construct " << typeid(MyAllocator).name() << '\n';
}

template<typename T, size_t ObjectsCapacity>
MyAllocator<T, ObjectsCapacity>::MyAllocator(MyAllocator &&o) noexcept {
    std::cout << "Move construct " << typeid(MyAllocator).name() << '\n';
}

template<typename T, size_t ObjectsCapacity>
template<typename U>
MyAllocator<T, ObjectsCapacity>::MyAllocator(const MyAllocator<U, ObjectsCapacity> &o) {
    std::cout << "Copy construct " << typeid(MyAllocator).name() << " from " << typeid(o).name() << '\n';
}

template<typename T, size_t ObjectsCapacity>
template<typename U>
MyAllocator<T, ObjectsCapacity>::MyAllocator(MyAllocator<U, ObjectsCapacity> &&o) {
    std::cout << "Move construct " << typeid(MyAllocator).name() << " from " << typeid(o).name() << '\n';
}

template<typename T, size_t ObjectsCapacity>
T *MyAllocator<T, ObjectsCapacity>::allocate(std::size_t n) {
    const auto all_of = [this] (size_t begin, size_t end) {
        while (begin != end) {
            if (!free_[begin]) {
                return false;
            }
            ++begin;
        }
        return true;
    };

    const auto occupy = [this] (size_t begin, size_t end) {
        while (begin != end) {
            free_.set(begin++, false);
        }
    };

    for (size_t i = 0; i < ObjectsCapacity - n + 1; ++i) {
        if (all_of(i, i + n)) {
            occupy(i, i + n);
            auto *result = static_cast<T*>(data_) + i;
            std::cout << "Allocate " << n << " element(s) of type " << typeid(T).name() << " at " << result << '\n';
            return result;
        }
    }

    if (data_) {
        std::cerr << "Unable to perform allocation of " << n << " element(s) of "
                  << typeid(T).name() << " type\n";
        report();
        throw std::bad_alloc();
    }

    data_ = std::malloc(sizeof(T) * ObjectsCapacity);
    if (!data_) {
        std::cerr << "System could not malloc " << (sizeof(T) * ObjectsCapacity) << " bytes\n";
        throw std::bad_alloc();
    }
    free_.set();
    return allocate(n);
}

template<typename T, size_t ObjectsCapacity>
void MyAllocator<T, ObjectsCapacity>::deallocate(T *p, std::size_t n) noexcept {
    std::cout << "Deallocate " << n << " element(s) of type " << typeid(T).name() << " at " << p << '\n';
    const auto offset = p - static_cast<T *>(data_);
    for (size_t i = 0; i < n; ++i) {
        free_.set(offset + i);
    }
}

template<typename T, size_t ObjectsCapacity>
void MyAllocator<T, ObjectsCapacity>::report() {
    if (!data_) {
        std::cout << "Nothing was allocated" << std::endl;
        return;
    }

    std::cout << ObjectsCapacity - free_.count() << " cells occupied, " << free_.count() << " are free\n";
    for (size_t i = 0; i < ObjectsCapacity; ++i) {
        std::cout << (i % 10);
    }
    std::cout << '\n';
    for (size_t i = 0; i < ObjectsCapacity; ++i) {
        std::cout << (free_[i] ? ' ' : '^');
    }
    std::cout << std::endl;
}
