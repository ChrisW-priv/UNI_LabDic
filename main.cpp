#include <iostream>
#include "tests.h"


int main() {
    std::cout << "TEST OF dictionary<int,int>:\n";
    test_intint();

    std::cout << "TEST OF dictionary<std::string,int>:\n";
    test_stringint();
}
