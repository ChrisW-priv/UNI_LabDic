#include "dictionary.h"

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

}