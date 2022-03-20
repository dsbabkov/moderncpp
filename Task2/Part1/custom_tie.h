#pragma once
#include <tuple>
#include <functional>

auto custom_tie = [](auto &...args) {
    return std::make_tuple(std::ref(args)...);
};
