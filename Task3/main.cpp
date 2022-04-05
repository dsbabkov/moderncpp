#include "MyAllocator.h"
#include <map>

int main() {
    std::map<int, int, std::less<int>, MyAllocator<std::pair<const int, int>, 11>> m = {
            {1, 5},
            {2, 3},
            {3, 5},
    };
}