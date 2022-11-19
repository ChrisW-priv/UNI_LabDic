#ifndef LABS_SLLIST_H
#define LABS_SLLIST_H

template<typename Key, typename Info>
class sllist{
    struct node {
        std::pair<Key, Info> pair;
        node* _next;

        bool operator==(const node& other) { return pair == other.pair; }
    };

    node* head;

public:
    // constructor
    sllist(): head(nullptr) {};
    sllist(std::initializer_list< std::pair<Key, Info> > list);
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

        /// Deallocates the node and links the nodes in the list
        /// Same as operator++ - can be optimised after debugs to just body of if and skip if statements
        void dealloc_node(){
            if (*_ptr) {
                auto next = (*_ptr)->_next;
                delete *_ptr;
                *_ptr = next;
            } else return;
        }
    };

    Iter begin(){ return Iter{head}; }
    Iter end(){ return Iter{nullptr}; }

    [[nodiscard]] bool empty() const noexcept{ return head == nullptr; };
    [[nodiscard]] size_t size() const noexcept;

    Info& at(const Key& k);
    const Info& at(const Key& k) const;
    Info& operator[](const Key& k);
    Info& operator[](Key&& k);

    void clear() noexcept;
    std::pair<Iter, bool> insert(std::pair<Key, Info>& pair);
    std::pair<Iter, bool> insert(std::pair<Key, Info>&& pair);
    std::pair<Iter, bool> insert_or_assign(const Key& k, Info& Info1);
    std::pair<Iter, bool> insert_or_assign(Key&& k, Info&& Info1);
    std::pair<Iter, bool> emplace(const Key& k, Info& Info1);
    std::pair<Iter, bool> emplace(Key&& k, Info&& Info1);
    Iter erase(const Iter pos);
    Iter erase(const Iter first, const Iter last);
    size_t erase(const Key& k);
    template<typename UnaryF>
    Iter erase_if(UnaryF unary_function);
    void swap(sllist& other) noexcept;
    // Note: extract nodes is VERY difficult to do right (to ensure encapsulation and to allow data handling)
    // proceed with caution and reed-up on what it really does!!
    node& extract(const Iter pos);
    node& extract(const Key& k);
    // should use extract as does the original method in c++ std::map
    void merge(sllist& other);
    void merge(sllist&& other);

    Iter find(const Key& k);
    const Iter find(const Key& k) const;
    size_t count(const Key& k) const;
    bool contains(const Key& k) const;

    bool operator==(const sllist& other) const;
};

template<typename Key, typename Info>
void sllist<Key, Info>::clear() noexcept {
    auto current = begin();
    while (current != end()){
        current.dealloc_node(); // changes value of current to next value after deletion, no ++curr needed!
    }
}

template<typename Key, typename Info>
bool sllist<Key, Info>::operator==(const sllist &other) const {
    auto current1 = begin();
    auto current2 = other.begin();
    while (current1 != end() && current2 != other.end()){
        auto eq = current1.equal_values(current2);
        if (!eq) return false;
        ++current1; ++current2;
    }
    // check if there are still values in any of the container eg.: "abc" == "abcd" should be false!
    if (current1 != end() || current2 != other.end()) return false;
    return true;
}

template<typename Key, typename Info>
size_t sllist<Key, Info>::size() const noexcept {
    size_t size = 0;
    for (auto node: *this) { size++; }
    return size;
}

template<typename Key, typename Info>
typename sllist<Key,Info>::Iter sllist<Key, Info>::find(const Key &key) {
    return std::find(begin(), end(), key);
}

template<typename Key, typename Info>
const typename sllist<Key,Info>::Iter sllist<Key, Info>::find(const Key &k) const {
    return find(k);
}

template<typename Key, typename Info>
size_t sllist<Key, Info>::count(const Key &k) const {
    auto found = find(k);
    return found != end(); // true or false converted to size_t
}

template<typename Key, typename Info>
bool sllist<Key, Info>::contains(const Key &k) const {
    auto found = find(k);
    return found != end();
}

template<typename Key, typename Info>
void sllist<Key, Info>::swap(sllist &other) noexcept {
    auto temp = this->head;
    this->head = other.head;
    other.head = temp;
}

template<typename Key, typename Info>
Info &sllist<Key, Info>::operator[](const Key &k) {
    auto position = find(k);
    if (position == end()){
        // init new node
        node* new_node = new node;
        new_node->pair.first = k;
        new_node->pair.second = Info{};
        position.insert_after(new_node);
        return new_node->pair.second; // return new info reference
    }
    return (*position).pair.second; // return reference to an existing value
}


#endif //LABS_SLLIST_H
