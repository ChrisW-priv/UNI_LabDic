#ifndef TESTS
#define TESTS

#include "dictionary.h"
#include <iostream>
#include <map>

// return codes tor tests:
// 1 - success
// 0 - fail

template<typename T>
void compare_with_expected(T value_expected, T value_returned, const std::string& description="", std::ostream& stream = std::cout){
    stream << ((value_expected == value_returned) ? "PASS" : "FAIL");
    stream << (description.empty() ? description : ": " + description);
    stream << "\n";
}

void run_tests(){
    dictionary<int, int> dic{};

    compare_with_expected(true, dic.empty(), "test of empty method");
    compare_with_expected((size_t) 0, dic.size(), "test of size method");

    std::pair p1{1,1};  // test if compiles ok
    dic.insert(p1);
    dic.insert( {2,2} );// same

    compare_with_expected(true, dic.contains(1), "test of contains method");
    compare_with_expected(true, dic.contains(2), "test of contains method [2]");
    compare_with_expected(false, dic.contains(3), "test of contains method [3]");

    compare_with_expected(false, dic.empty(), "test of empty method [2]");
    compare_with_expected((size_t) 2, dic.size(), "test of size method [2]");

    compare_with_expected((size_t) 1, dic.count(1), "test of count method");
    compare_with_expected((size_t) 0, dic.count(3), "test of count method [2]");

    dic.insert( {3,3} );
    dictionary<int,int> compare{ {1,1}, {2,2}, {3,3} };

    compare_with_expected(dic, compare, "copy of init list constructor");
    dictionary<int, int> compare_cpy{compare};
    compare_with_expected(compare, compare_cpy, "test of copy constructor");

    dic.erase(3);
    dictionary<int,int> comp2{ {1,1}, {2,2} };
    compare_with_expected(dic, comp2, "test of erase method");

    dictionary<int,int> comp3{comp2};
    comp2.insert( {3,3} );
    comp2.swap(comp3);
    compare_with_expected(comp2, dic, "test of swap method");
    compare_with_expected(comp3, compare, "test of swap method");

    std::cout<< "\n============================================\n";
    std::cout<< "HERE WE START TESTING OF JOIN!!\n";
    std::cout<< "============================================\n";

    dictionary<int,int> base{ {1,1}, {3,1} };
    dictionary<int,int> dic_to_join{ {0,2}, {2,2}, {3,2}, {5,2}, {4,2} };
    std::cout << base;
    std::cout << dic_to_join;

    auto dic_result = join(base, dic_to_join);
    std::cout << dic_result;
    dictionary<int,int> expected{ { 0,2 }, { 1,1 }, { 2,2 }, { 3,1 }, { 4,2 }, { 5,2 } };
    std::cout << '\n';
    compare_with_expected(expected, dic_result, "test of join function on two dictionaries");
};

template<typename iter>
void print_map(iter begin, iter end){
    while (begin != end){
        std::cout << "Key:" << begin->first << " Value:" << begin->second << "\n";
        ++begin;
    }
}

#endif