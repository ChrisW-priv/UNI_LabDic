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
    std::cout << ((value_expected == value_returned) ? "PASS" : "FAIL");
}

void run_tests(){
    dictionary<int, int> dic{};

    bool ret1 = dic.empty();
    compare_with_expected(true, ret1);

    size_t ret2 = dic.size();
    compare_with_expected((size_t) 0, ret2);

    std::pair p1{1,1};
    std::pair p2{2,2};
    dic.insert(p1);
    dic.insert(p2);
    compare_with_expected(true, dic.contains(1));
};

template<typename iter>
void print_map(iter begin, iter end){
    while (begin != end){
        std::cout << "Key:" << begin->first << " Value:" << begin->second << "\n";
        ++begin;
    }
}

void test_normal(){
    std::map<int,int> map{};
    map.emplace(1,1);
    print_map(map.begin(), map.end());
}

#endif