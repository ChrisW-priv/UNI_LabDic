#ifndef TESTS
#define TESTS

#include "dictionary.h"
#include <iostream>
#include <map>

// return codes tor tests:
// 1 - success
// 0 - fail

template<typename T>
bool compare_with_expected(T value_expected, T value_returned){
    return value_expected == value_returned;
}

bool test_1(){
    dictionary<int, int> dic{};
    bool ret = dic.empty();

    return compare_with_expected(true, ret);
};


bool test_2(){
    dictionary<int, int> dic{};
    int ret = dic.size();

    return compare_with_expected(0, ret);
};


bool test_3(){
    dictionary<int, int> dic{};
    dic.emplace(1, 1);
    dic.emplace(1, 2);

    return compare_with_expected(true, dic.contains(1));
}

template<typename iter>
void print_map(iter begin, iter end){
    while (begin != end){
        std::cout << "Key:" << begin->first << " Value:" << begin->second << "\n";
        ++begin;
    }
}

void test_normal(){
    std::map<int,int> dic;
    dic.emplace(1,1);
    dic.try_emplace(1, 1);

    print_map(dic.begin(), dic.end());
}

#endif