#pragma once

#include "custom_tuple.h"

auto custom_tie = [](auto &...args) {
    return make_custom_tuple(std::ref(args)...);
};
