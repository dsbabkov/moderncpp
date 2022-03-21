#pragma once

#include <utility>
#include "strip_ref.h"

template <typename T, typename ...Rest>
class custom_tuple: public custom_tuple<Rest...> {
public:
    explicit custom_tuple(const T &t, const Rest &... rest);

    template<typename U, typename ...Rest2>
    custom_tuple &operator=(const custom_tuple<U, Rest2...> &o);

    strip_ref_t<T> t_;
};

template <typename T>
class custom_tuple<T> {
public:
    explicit custom_tuple(const T &t);

    template<typename U>
    custom_tuple &operator=(const custom_tuple<U> &o);

    strip_ref_t<T> t_;
};

template<typename T>
custom_tuple<T>::custom_tuple(const T &t)
        : t_(t) {
}

template<typename T>
template<typename U>
custom_tuple<T> &custom_tuple<T>::operator=(const custom_tuple<U> &o) {
    t_ = o.t_;
    return *this;
}

template<typename T, typename... Rest>
custom_tuple<T, Rest...>::custom_tuple(const T &t, const Rest &... rest)
        : custom_tuple<Rest...>(rest...),
          t_(t) {

}

template<typename T, typename... Rest>
template<typename U, typename... Rest2>
custom_tuple<T, Rest...> &custom_tuple<T, Rest...>::operator=(const custom_tuple<U, Rest2...> &o) {
    t_ = o.t_;
    *static_cast<custom_tuple<Rest...>*>(this) = *static_cast<const custom_tuple<Rest2...>*>(&o);
    return *this;
}

template <typename ...Args>
custom_tuple<strip_ref_t<Args>...> make_custom_tuple(const Args &...args) {
    return custom_tuple<strip_ref_t<Args>...>(args...);
}
