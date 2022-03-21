#pragma once

#include <functional>

template <typename T>
struct strip_ref {
    using type = T;
};

template <typename T>
struct strip_ref<std::reference_wrapper<T>> {
using type = T&;
};
