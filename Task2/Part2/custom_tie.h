#pragma once

#include <tuple>
#include <functional>
#include "custom_tuple.h"

auto custom_tie = [](auto &...args) {
    return std::make_tuple(std::ref(args)...);
};
