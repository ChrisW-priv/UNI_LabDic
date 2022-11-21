#ifndef LABS_DICTIONARY_H
#define LABS_DICTIONARY_H

#include "sllist.h"
// Methods inspired by https://en.cppreference.com/w/cpp/container/map which is a much better version to what we will do


template<typename Key, typename Info>
class dictionary{
    sllist<Key, Info> container;
    using Iter=typename sllist<Key, Info>::Iter;
    using constIter=typename sllist<Key, Info>::constIter;

public:
    // constructor
    dictionary(): container() {};
    dictionary(std::initializer_list< std::pair<Key, Info> > list): container(list) {};
    explicit dictionary(sllist<Key, Info>& list) :container() { container.swap(list); }

    // copy
    dictionary(const dictionary& list): container(list.container) {};
    // destructor
    ~dictionary() { clear(); }

    /// checks if values under both iterators are the same
    bool equal_values(Iter i1, Iter i2){ return *(i1._ptr) && *(i2._ptr) && *i1._ptr == *i2._ptr; }

    Iter begin(){ return container.begin(); }
    constIter begin() const { return container.begin(); }
    constIter end() const { return container.end(); }

    [[nodiscard]] bool empty() const noexcept { return container.empty(); };
    [[nodiscard]] size_t size() const noexcept {return container.size(); };

    /// returns position of where node is (or SHOULD be)
    /// \param key Key value to compare against
    /// \return bool for if Key is in the position, false otherwise
    std::pair<Iter, bool> find(const Key& key) {return container.find(key); };
    Info& at(const Key& key) { return container.at(key); };
    Info& operator[](Key&& key) { return container[key]; };
    Info& operator[](const Key& key) { return container[key]; }

    void clear() noexcept { container.clear(); };

    std::pair<Iter, bool> insert(std::pair<Key, Info>&& pair) { return container.insert(pair); };
    std::pair<Iter, bool> insert(std::pair<Key, Info>& pair) { return container.insert(std::move(pair)); };

    std::pair<Iter, bool> insert_or_assign(Key&& key, Info&& info) { return container.insert_or_assign(key, info); };
    std::pair<Iter, bool> insert_or_assign(const Key& key, Info& info) { return container.insert_or_assign(key, info); };

    std::pair<Iter, bool> emplace(Key&& key, Info&& info) { return container.emplace(key, info); };
    std::pair<Iter, bool> emplace(const Key& key, Info& info) { return container.emplace(key, info); };

    Iter erase(Iter pos) { return container.erase(pos); };
    Iter erase(Iter first, const Iter& last) { return container.erase(first, last); };
    size_t erase(const Key& k) { return container.erase(k); };

    void swap(dictionary& other) noexcept { container.swap(other.container); };

    size_t count(const Key& key) const { return container.count(key); };
    bool contains(const Key& key) const { return container.contains(key); };

    bool operator==(const dictionary& other) const { return container == other.container; }
    bool operator!=(const dictionary& other) const { return container != other.container; }

    friend std::ostream& operator<<(std::ostream& stream, const dictionary<Key, Info>& dic){
        stream << dic.container;
        return stream;
    }
};


template<typename Key, typename Info>
dictionary<Key, Info> join(const dictionary<Key,Info>& first, const dictionary<Key,Info>& second){
    sllist<Key, Info> new_list;
    std::set_union(first.begin(), first.end(), second.begin(), second.end(), new_list.begin());
    return dictionary{new_list};
}


#endif //LABS_DICTIONARY_H
