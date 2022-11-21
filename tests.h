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

    dic.erase(3);
    dictionary<int,int> comp2{ {1,1}, {2,2} };
    compare_with_expected(dic, comp2);

    dictionary<int,int> comp3{comp2};
    comp2.insert( {3,3} );
    comp2.swap(comp3);
    compare_with_expected(comp2, dic);
    compare_with_expected(comp3, compare);

    std::cout<< "============================================\n";
    std::cout<< "HERE WE START TESTING OF JOIN!!\n";
    std::cout<< "============================================\n";

    dictionary<int,int> dic_to_join{ {3,4}, {5,6}, {4,5} };
    std::cout << dic;
    std::cout << dic_to_join;

    auto dic_result = join(dic, dic_to_join);
    std::cout << dic_result;
};

template<typename iter>
void print_map(iter begin, iter end){
    while (begin != end){
        std::cout << "Key:" << begin->first << " Value:" << begin->second << "\n";
        ++begin;
    }
}

#endif