#ifndef TESTS
#define TESTS

#include "dictionary.h"
#include <iostream>
#include <map>

// return codes tor tests:
// 1 - success
// 0 - fail

template<typename T>
void compare_with_expected(T value_expected, T value_returned){
    std::cout << ((value_expected == value_returned) ? "PASS\n" : "FAIL\n");
}

void run_tests(){
    dictionary<int, int> dic{};

    compare_with_expected(true, dic.empty());
    compare_with_expected((size_t) 0, dic.size());

    std::pair p1{1,1};
    dic.insert(p1);
    dic.insert( {2,2} );

    compare_with_expected(true, dic.contains(1));
    compare_with_expected(true, dic.contains(2));
    compare_with_expected(false, dic.contains(3));
    compare_with_expected(false, dic.empty());
    compare_with_expected((size_t) 1, dic.count(1));
    compare_with_expected((size_t) 0, dic.count(3));

    dic.insert( {3,3} );
    dictionary<int,int> compare{ {1,1}, {2,2}, {3,3} };

    compare_with_expected(dic, compare);
    dictionary<int, int> compare_cpy{compare};
    compare_with_expected(compare, compare_cpy);


};

template<typename iter>
void print_map(iter begin, iter end){
    while (begin != end){
        std::cout << "Key:" << begin->first << " Value:" << begin->second << "\n";
        ++begin;
    }
}

#endif