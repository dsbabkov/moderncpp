#include <map>
#include <iostream>
#include <memory>


template <typename T, size_t MaxObjectsAtATime>
struct MyAllocator {
    using value_type = T;
    MyAllocator() {
        std::cout << "Construct " << typeid(MyAllocator).name() << '\n';
    }
    ~MyAllocator() {
        std::cout << "Destruct " << typeid(MyAllocator).name() << '\n';
    }

    MyAllocator(const MyAllocator &o) {
        std::cout << "Copy construct " << typeid(MyAllocator).name() << '\n';
    }

    MyAllocator(MyAllocator &&o) noexcept {
        std::cout << "Move construct " << typeid(MyAllocator).name() << '\n';
    }

    template<typename U>
    MyAllocator(const MyAllocator<U, MaxObjectsAtATime> &o) {
        std::cout << "Copy construct " << typeid(MyAllocator).name() << " from " << typeid(o).name() << '\n';
    }

    template<typename U>
    MyAllocator(MyAllocator<U, MaxObjectsAtATime> &&o) {
        std::cout << "Move construct " << typeid(MyAllocator).name() << " from " << typeid(o).name() << '\n';
    }

    template <typename U>
    struct rebind {
        using other = MyAllocator<U, MaxObjectsAtATime>;
    };

    T *allocate(std::size_t n)  {
        if (n > MaxObjectsAtATime) {
            std::cerr << n << " object(s) requested to allocate. Max: " << MaxObjectsAtATime << '\n';
            throw std::bad_alloc();
        }
        T *result = static_cast<T *>(std::malloc(sizeof(T) * n));
        if (!result) {
            std::cerr << n << " object(s) requested to allocate. Unable to allocate\n";
            throw std::bad_alloc();
        }
        std::cout << "Allocate " << n << " element(s) of type " << typeid(T).name() << " at " << result << '\n';
        return result;
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "Deallocate " << n << " element(s) of type " << typeid(T).name() << " at " << p << '\n';
        std::free(p);
    }
};

int main() {
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 1>> m = {
            {1, 5},
            {2, 3},
            {3, 5},
    };
}