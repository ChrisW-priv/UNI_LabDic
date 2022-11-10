#ifndef LABS_DICTIONARY_H
#define LABS_DICTIONARY_H

#include "sllist.h"
// Methods inspired by https://en.cppreference.com/w/cpp/container/map which is a much better version to what we will do


template<typename key, typename info>
class dictionary{
    sllist<key, info> container;

public:
    bool empty(){ return container.empty(); };
    int size(){ return container.size(); };

    info& at(const key& key1){ return container.at(key1); };
    const info& at(const key& key1) const {return container.at(key1); };
    info& operator[](const key& key1){ return container[key1]; };
    const info& operator[](const key& key1) const { return container[key1]; };

    bool clear(){ return container.clear(); };
    bool insert(const key& key1, const info& info1){ return container.insert(key1, info1); };
    bool insert_or_assign(const key& key1, const info& info1){ return container.insert_or_assign(key1, info1); };
    bool emplace(key& key1, info& info1){ return container.emplace(key1, info1); };
    bool emplace(const key&& key1, info&& info1){};
    bool try_emplace(const key& key1, const info& info1){ return container.try_emplace(key1, info1); };
    bool try_emplace(const key&& key1, const info&& info1){ return container.try_emplace(key1, info1); };

    bool swap(dictionary other){ return container.swap(other.container); };
    bool merge(dictionary other){ return container.merge(other.container); };

    bool contains(const key& key1) const{ return container.contains(key1); };
    bool find(const key& key1){ return container.find(key1); };
    bool find(const key& key1) const { return container.find(key1); };
    int count(const key& key1) const { return container.count(key1); };

    bool operator==(dictionary other) const { return container == other.container; };
};


#endif //LABS_DICTIONARY_H
