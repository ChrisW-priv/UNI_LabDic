#ifndef LABS_SLLIST_H
#define LABS_SLLIST_H

template<typename key, typename info>
class sllist{
    struct node{
        key _key;
        info _info;
        node* _next;
    };

    node* head;

    struct Iter{
        node* _ptr;
        explicit Iter(node* ptr) : _ptr(ptr){}

        Iter& operator=(node* node_ptr)
        {
            this->_ptr = node_ptr;
            return *this;
        }

        Iter& operator++()
        {
            if (_ptr) _ptr = _ptr->_next;
            return *this;
        }

        Iter& operator++(int)
        {
            Iter iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator==(const Iter& other){ return _ptr == other._ptr; }
        bool operator!=(const Iter& other){ return _ptr != other._ptr; }

        node& operator*(){ return *_ptr; }
        node* operator->(){ return _ptr; }
    };

public:
    Iter begin(){ return Iter{head}; }
    Iter end(){ return Iter{nullptr}; }

    bool empty(){ return head == nullptr; };
    int size(){ return 0; };

    info& at(const key& key1){};
    const info& at(const key& key1) const{};
    info& operator[](const key& key1){};
    const info& operator[](const key& key1) const{};

    bool clear(){};
    bool insert(const key& key1, const info& info1){};
    bool insert_or_assign(const key& key1, const info& info1){};
    bool emplace(const key& key1, info& info1){};
    bool try_emplace(const key& key1, const info& info1){};

    bool swap(sllist other){};
    bool merge(sllist other){};

    bool contains(const key& key1){};
    bool contains(const key& key1) const{};
    bool find(const key& key1){};
    bool find(const key& key1) const {};
    bool count(const key& key1){};
    bool count(const key& key1) const {};

    bool operator==(sllist other){};
    bool operator==(sllist other) const{};

};

#endif //LABS_SLLIST_H
