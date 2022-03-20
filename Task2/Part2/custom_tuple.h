#pragma once

#include <utility>


template <typename T, typename ...Rest>
class custom_tupple: custom_tupple<Rest...> {

};

