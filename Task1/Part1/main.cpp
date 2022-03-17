#include <iostream>

#ifndef BUILD_NUMBER
    #error No build number set
#endif

int main() {
    std::cout << "build " << BUILD_NUMBER << "\n"
                 "Hello, World!\n";
    return 0;
}
