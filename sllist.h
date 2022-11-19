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
    sllist(): head(nullptr) {};
    sllist(std::initializer_list< std::pair<key,info> > list);
    // copy
    sllist(const sllist& list);
    // destructor
    ~sllist();

    struct Iter{
        node** _ptr;

        explicit Iter(node** ptr) : _ptr(ptr) {}
        Iter(const Iter& other): _ptr(other._ptr) {}

        /// Insert new node at the place of the old one
        /// deallocates the old one and sets new node in place while preserving order of list
        Iter& operator=(node* node_ptr)
        {
            node** next;
            if (*_ptr){
                next = (*_ptr)->_next;
                delete *_ptr; // deallocate current node
            } else { next = nullptr; } // nothing to deallocate if curr == null!
            node_ptr->_next = next;
            *_ptr = node_ptr;
            return *this;
        }

        /// moves to the next node if it's possible
        /// Note: this function already checks if the node is the last one (points to nullptr)
        /// Note: when debugging is done, body can be changed to just _ptr = `(*_ptr)->_next;` for better performance
        Iter& operator++()
        {
            if (*_ptr) { _ptr = (*_ptr)->_next; }
            return *this;
        }

        /// Uses internal prefix operator++
        /// \return value of the iterator before move
        Iter operator++(int)
        {
            Iter iterator = *this;
            ++*this;
            return iterator;
        }

        /// checks if pointers point to the same node
        /// \param other Iter: iterator we compare with
        /// \return bool, true if pointers point to the same node
        bool operator==(const Iter& other){ return (*_ptr) == (*other._ptr); }

        /// opposite to operator==
        /// \param other Iter: iterator we compare with
        /// \return bool, true if pointers don't point to the same node
        bool operator!=(const Iter& other){ return (*_ptr) != (*other._ptr); }

        /// Returns reference to the node Iter points to
        /// Caution: this results in the exposition of raw node type which is currently private
        /// \return node reference
        node& operator*(){ return **_ptr; }

        /// Returns pointer to the node Iter points to
        /// Caution: this results in the exposition of raw node type which is currently private
        /// \return node ptr
        node* operator->(){ return *_ptr; }

        /// In theory not a Typical operator member function but this will help with things later
        bool equal_values(Iter& other){ return *_ptr && *(other._ptr) && (*_ptr)->pair == (*(other._ptr))->pair; }

        /// inserts node under pointer after current element.
        /// WARNING: will cause segFault if node_ptr = nullptr!!
        void insert_after(node* node_ptr){
            node_ptr->_next = *_ptr;
            *_ptr = node_ptr;
        }
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

template<typename key, typename info>
size_t sllist<key, info>::size() const noexcept {
    size_t size = 0;
    for (auto node: *this) { size++; }
    return size;
}


#endif //LABS_SLLIST_H
