#pragma once

#include <utility>
#include "strip_ref.h"

template <typename T, typename ...Rest>
class custom_tupple: public custom_tupple<Rest...> {
public:
    explicit custom_tupple(const T &t, const Rest &... rest);

    template<typename U, typename ...Rest2>
    custom_tupple &operator=(const custom_tupple<U, Rest2...> &o) {
        t_ = o.t_;
        *static_cast<custom_tupple<Rest...>*>(this) = *static_cast<const custom_tupple<Rest2...>*>(&o);
        return *this;
    }

    strip_ref_t<T> t_;
};

template <typename T>
class custom_tupple<T> {
public:
    explicit custom_tupple(const T &t);

    template<typename U>
    custom_tupple &operator=(const custom_tupple<U> &o) {
        t_ = o.t_;
        return *this;
    }

    strip_ref_t<T> t_;
};

template<typename T>
custom_tupple<T>::custom_tupple(const T &t)
        : t_(t) {
}

template<typename T, typename... Rest>
custom_tupple<T, Rest...>::custom_tupple(const T &t, const Rest &... rest)
        : custom_tupple<Rest...>(rest...),
          t_(t) {

}

template <typename ...Args>
custom_tupple<Args...> make_custom_tuple(const Args &...args) {
    return custom_tupple<Args...>(args...);
}
