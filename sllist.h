#ifndef LABS_SLLIST_H
#define LABS_SLLIST_H

template<typename key, typename info>
class sllist{
    struct node {
        std::pair<key, info> pair;
        node* _next;
    };

    node* head;

public:
    // constructor
    sllist();
    sllist(std::initializer_list< std::pair<key,info> > list);
    // copy
    sllist(const sllist& list);
    // destructor
    ~sllist();

    struct Iter{
        node* _ptrCurrent;
        node* _ptrPrev;

        explicit Iter(node* ptr) : _ptrCurrent(ptr) {}
        Iter(const Iter& other): _ptrCurrent(other._ptrCurrent), _ptrPrev(other._ptrPrev) {}

        /// In theory not a Typical operator member function but this will help with things later
        bool equal_values(Iter& other){ return _ptrCurrent && other._ptrCurrent && _ptrCurrent->pair == other._ptrCurrent->pair; }

        Iter& operator=(node* node_ptr)
        {
            _ptrCurrent = node_ptr;
            _ptrPrev = nullptr;
            return *this;
        }

        Iter& operator++()
        {
            if (_ptrCurrent) { _ptrPrev = _ptrCurrent; _ptrCurrent = _ptrCurrent->_next; }
            return *this;
        }

        Iter operator++(int)
        {
            Iter iterator = *this;
            ++*this;
            return iterator;
        }

        bool operator==(const Iter& other){ return _ptrCurrent == other._ptrCurrent; }
        bool operator!=(const Iter& other){ return _ptrCurrent != other._ptrCurrent; }

        node& operator*(){ return *_ptrCurrent; }
        node* operator->(){ return _ptrCurrent; }
    };

    Iter begin(){ return Iter{head}; }
    Iter end(){ return Iter{nullptr}; }

    [[nodiscard]] bool empty() const noexcept{ return head == nullptr; };
    [[nodiscard]] size_t size() const noexcept;

    info& at(const key& k);
    const info& at(const key& k) const;
    info& operator[](const key& k);
    info& operator[](key&& k);

    void clear() noexcept;
    std::pair<Iter, bool> insert(std::pair<key, info>& pair);
    std::pair<Iter, bool> insert(std::pair<key, info>&& pair);
    std::pair<Iter, bool> insert_or_assign(const key& k, info& info1);
    std::pair<Iter, bool> insert_or_assign(key&& k, info&& info1);
    std::pair<Iter, bool> emplace(const key& k, info& info1);
    std::pair<Iter, bool> emplace(key&& k, info&& info1);
    Iter erase(const Iter pos);
    Iter erase(const Iter first, const Iter last);

    size_t erase(const key& k);
    template<typename UnaryF>
    Iter erase_if(UnaryF unary_function);
    void swap(sllist& other) noexcept;
    // Note: extract nodes is VERY difficult to do right (to ensure encapsulation and to allow data handling)
    // proceed with caution and reed-up on what it really does!!
    node& extract(const Iter pos);
    node& extract(const key& k);
    // should use extract as does the original method in c++ std::map
    void merge(sllist& other);
    void merge(sllist&& other);

    Iter find(const key& k);
    const Iter find(const key& k) const;
    size_t count(const key& k) const;
    bool contains(const key& k) const;

    bool operator==(const sllist& other) const;
    bool operator<=>(const sllist& other) const;
};

template<typename key, typename info>
void sllist<key, info>::clear() noexcept {
    auto current = this->begin();
    while (current != this->end()){
        delete current._ptrCurrent;
        current._ptrCurrent = nullptr;
        ++current;
    }
}

template<typename key, typename info>
bool sllist<key, info>::operator==(const sllist &other) const {
    auto current1 = this->begin();
    auto current2 = other.begin();
    while (current1 != this->end() && current2 != other.end()){
        auto eq = current1.equal_values(current2);
        if (!eq) return false;
        ++current1; ++current2;
    }
    // check if there are still values in any of the container eg.: "abc" == "abcd" should be false!
    if (current1 != this->end() || current2 != other.end()) return false;
    return true;
}


#endif //LABS_SLLIST_H
