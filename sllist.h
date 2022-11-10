#ifndef LABS_SLLIST_H
#define LABS_SLLIST_H

template<typename key, typename info>
class sllist{
    struct node {
        std::pair<key, info> pair;
        node* _next;
    };

    node* head;

    struct Iter{
        node* _ptr;
        explicit Iter(node* ptr) : _ptr(ptr){}

        bool equal_values(Iter& other){ return _ptr && other._ptr && _ptr->pair == other._ptr->pair; }

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

    bool same_values(Iter begin1, Iter end1, Iter begin2);

public:
    Iter begin(){ return Iter{head}; }
    Iter end(){ return Iter{nullptr}; }

    bool empty(){ return head == nullptr; };
    int size(){ return 0; };

    info& at(const key& key1){};
    const info& at(const key& key1) const{};
    info& operator[](const key& key1){};
    const info& operator[](const key& key1) const{};

    bool clear();
    bool insert(const key& key1, const info& info1);
    bool insert_or_assign(const key& key1, const info& info1);
    bool emplace(const key& key1, info& info1);
    bool emplace(const key&& key1, info&& info1);
    bool try_emplace(const key& key1, const info& info1);
    bool try_emplace(const key&& key1, info&& info1);

    bool swap(sllist other);
    bool merge(sllist other);

    bool contains(const key& key1) const;
    bool find(const key& key1);
    bool find(const key& key1) const;
    int count(const key& key1) const;

    bool operator==(const sllist& other) const { return this->size() == other.size() && same_values(this->begin(),
                                                                                                  this->end(),
                                                                                                  other.begin());
    };
};

template<typename key, typename info>
bool sllist<key, info>::clear() {
    auto current = this->begin();
    while (current != this->end()){
        delete current._ptr;
        ++current;
    }
    return true;
}

template<typename key, typename info>
bool sllist<key, info>::same_values(sllist::Iter begin1, sllist::Iter end1, sllist::Iter begin2) {
    while (begin1 != end1){
        if (!begin1.equal_values(begin2)) return false;
        ++begin1; ++begin2;
    }
    return true;
}

#endif //LABS_SLLIST_H
