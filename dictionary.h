#ifndef LABS_DICTIONARY_H
#define LABS_DICTIONARY_H

#include "sllist.h"
// Methods inspired by https://en.cppreference.com/w/cpp/container/map which is a much better version to what we will do


template<typename key, typename info>
class dictionary{
    sllist<key, info> store;

public:
    bool empty(){};
    int size() {};

    info& at(const key& key1){};
    const info& at(const key& key1) const{};
    info& operator[](const key& key1){};
    const info& operator[](const key& key1) const{};

    bool clear(){};
    bool insert(const key& key1, const info& info1){};
    bool insert_or_assign(const key& key1, const info& info1){};
    bool emplace(const key& key1, info& info1){};
    bool try_emplace(const key& key1, const info& info1){};

    bool swap(dictionary other){};
    bool merge(dictionary other){};

    bool contains(const key& key1){};
    bool contains(const key& key1) const{};
    bool find(const key& key1){};
    bool find(const key& key1) const {};
    bool count(const key& key1){};
    bool count(const key& key1) const {};

    bool operator==(dictionary other){};
    bool operator==(dictionary other) const{};
};


#endif //LABS_DICTIONARY_H
