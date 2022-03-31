#include <map>
#include <iostream>

template <typename T>
struct MyAllocator {
    using value_type = T;

    template <typename U>
    struct rebind {
        using other = MyAllocator<U>;
    };

    T *allocate(std::size_t n) noexcept {
        T *result = static_cast<T *>(std::malloc(sizeof(T) * n));
        std::cout << "Allocate " << n << " element(s) of type " << typeid(T).name() << " at " << result << '\n';
        return result;
    }

    void deallocate(T* p, std::size_t n) noexcept {
        std::cout << "Deallocate " << n << " element(s) of type " << typeid(T).name() << " at " << p << '\n';
        std::free(p);
    }
};

int main() {
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>>> m;
    m.emplace(1, 1);
}