#include <map>
#include <iostream>
#include <memory>
#include <bitset>

template <typename T, size_t ObjectsCapacity>
struct MyAllocator {
    using value_type = T;
    MyAllocator() {
        std::cout << "Construct " << typeid(MyAllocator).name() << '\n';
    }
    ~MyAllocator() {
        std::cout << "Destruct " << typeid(MyAllocator).name() << '\n';
        // FIXME: report
        std::free(data_);
    }

    MyAllocator(const MyAllocator &o) {
        std::cout << "Copy construct " << typeid(MyAllocator).name() << '\n';
    }

    MyAllocator(MyAllocator &&o) noexcept {
        std::cout << "Move construct " << typeid(MyAllocator).name() << '\n';
    }

    template<typename U>
    MyAllocator(const MyAllocator<U, ObjectsCapacity> &o) {
        std::cout << "Copy construct " << typeid(MyAllocator).name() << " from " << typeid(o).name() << '\n';
    }

    template<typename U>
    MyAllocator(MyAllocator<U, ObjectsCapacity> &&o) {
        std::cout << "Move construct " << typeid(MyAllocator).name() << " from " << typeid(o).name() << '\n';
    }

    template <typename U>
    struct rebind {
        using other = MyAllocator<U, ObjectsCapacity>;
    };

    T *allocate(std::size_t n)  {
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
            // FIXME: report
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

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "Deallocate " << n << " element(s) of type " << typeid(T).name() << " at " << p << '\n';
        const auto offset = p - static_cast<T *>(data_);
        for (size_t i = 0; i < n; ++i) {
            free_.set(offset + i);
        }
    }

    void *data_ = nullptr;
    std::bitset<ObjectsCapacity> free_;
};

int main() {
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 11>> m = {
            {1, 5},
            {2, 3},
            {3, 5},
    };
}