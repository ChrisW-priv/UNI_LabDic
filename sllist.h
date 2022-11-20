#ifndef LABS_SLLIST_H
#define LABS_SLLIST_H

#include <algorithm>

template<typename Key, typename Info>
class sllist{
    struct node {
        std::pair<Key, Info> pair;
        node* _next;

        node(): pair(), _next(nullptr) {}
        node(Key&& key, Info&& info): pair(key,info) {}
        node(const Key& key, const Info& info): pair(key,info) {}
        explicit node(std::pair<Key, Info>&& p): pair(p) {};
        explicit node(const std::pair<Key, Info>& p): pair(p) {};

        /// We want to order nodes by the values of keys
        bool operator==(const node& other) const { return pair.first == other.pair.first; }
        std::partial_ordering operator<=>(const node& other) const {
            if (pair.first < other.pair.first) return std::partial_ordering::less;
            if (pair.first == other.pair.first) return std::partial_ordering::equivalent;
            if (pair.first > other.pair.first) return std::partial_ordering::greater;
            else return std::partial_ordering::unordered;
        }
    };

    node* head;

    /// inserts node under pointer after iterator element.
    /// WARNING: will cause segFault if node_ptr = nullptr!!
    template<typename Iter>
    static void insert_after(Iter iterator, node* node_ptr){
        node_ptr->_next = *(iterator._ptr);
        *iterator._ptr = node_ptr;
    }

    static node* alloc_node(std::pair<Key, Info>&& pair){
        node* new_node = new node;
        new_node->pair = pair;
        return new_node;
    }

    static void dealloc_node(node** _ptr){
        if (*_ptr){
            auto next = (*_ptr)->_next;
            delete *_ptr; // deallocate current node
            *_ptr = next;
        }
    }

public:
    // constructor
    sllist(): head(nullptr) {};
    sllist(std::initializer_list< std::pair<Key, Info> >&& list);
    // copy
    sllist(const sllist& list);
    // destructor
    ~sllist() { clear(); }

    struct Iter : std::iterator<std::forward_iterator_tag, node, node, node>{
        node** _ptr;
        using iterator_category = std::forward_iterator_tag;

        explicit Iter(node* ptr) { *_ptr = ptr; }
        Iter(const Iter& other): _ptr(other._ptr) {}

        /// Insert new node at the place of the old one
        /// deallocates the old one and sets new node in place while preserving order of list
        Iter& operator=(node* node_ptr)
        {
            dealloc_node(_ptr);
            node_ptr->_next = *_ptr;
            *_ptr = node_ptr;
            return *this;
        }

        /// moves to the next node if it's possible
        /// Note: this function already checks if the node is the last one (points to nullptr)
        /// Note: when debugging is done, body can be changed to just _ptr = `(*_ptr)->_next;` for better performance
        Iter& operator++()
        {
            if (*_ptr) { *_ptr = (*_ptr)->_next; }
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
        bool operator==(const Iter& other){ return (*_ptr) == *(other._ptr); }

        /// opposite to operator==
        /// \param other Iter: iterator we compare with
        /// \return bool, true if pointers don't point to the same node
        bool operator!=(const Iter& other){ return (*_ptr) != *(other._ptr); }

        /// Returns reference to the pair under node it points to
        /// \return reference to pair under node
        /// WARNING: will segfault if iter == end()!!!
        node& operator*(){ return **_ptr; }

        /// Returns pointer to node under iter
        /// \return pointer to node under iter
        node* operator->(){ return *_ptr; }
    };

    Iter begin(){ return Iter{head}; }
    Iter begin() const { return Iter{head}; }
    Iter end(){ return Iter{nullptr}; }
    Iter end() const{ return Iter{nullptr}; }

    [[nodiscard]] bool empty() const noexcept { return head == nullptr; };
    [[nodiscard]] size_t size() const noexcept;

    /// returns position of where node is (or SHOULD be)
    /// \param key key value to compare against
    /// \return bool for if key is in the position, false otherwise
    std::pair<Iter, bool> find(const Key& key);
    /// returns position of where node is (or SHOULD be)
    /// \param key key value to compare against
    /// \return bool for if key is in the position, false otherwise
    std::pair<const Iter, bool> find(const Key& key) const { return find(key); };

    Info& at(const Key& key);
    Info& operator[](Key&& key);
    Info& operator[](const Key& key) { return (*this)[std::move(key)]; }

    void clear() noexcept;

    std::pair<Iter, bool> insert(std::pair<Key, Info>&& pair);
    std::pair<Iter, bool> insert(std::pair<Key, Info>& pair) { return insert(std::move(pair)); };

    std::pair<Iter, bool> insert_or_assign(Key&& key, Info&& info);
    std::pair<Iter, bool> insert_or_assign(const Key& key, Info& info) { return insert_or_assign(key, info); };

    std::pair<Iter, bool> emplace(Key&& key, Info&& info);
    std::pair<Iter, bool> emplace(const Key& key, Info& info) { return emplace(key, info); };

    Iter erase(Iter pos);
    Iter erase(Iter first, const Iter& last);
    size_t erase(const Key& k);

    void swap(sllist& other) noexcept;

    size_t count(const Key& key) const { return std::count(begin(), end(), node{key, Info{}}); };
    bool contains(const Key& key) const { return std::find(begin(), end(), node{key, Info{}}) != end(); };

    bool operator==(const sllist& other) const { return std::equal(begin(), end(), other.begin()); }
    bool operator!=(const sllist& other) const { return !std::equal(begin(), end(), other.begin()); }
};

template<typename Key, typename Info>
sllist<Key, Info>::sllist(std::initializer_list<std::pair<Key, Info>>&& list) {
    std::sort(list.begin(), list.end());
    auto curr = begin();
    for (auto pair: list) {
        auto new_node = alloc_node(pair);
        curr = insert_after(curr, new_node);
    }
}

template<typename Key, typename Info>
sllist<Key, Info>::sllist(const sllist &list) {
    auto curr = begin();
    for (auto node: list) {
        auto new_node = alloc_node(*node);
        curr = insert_after(curr, new_node);
    }
}

template<typename Key, typename Info>
size_t sllist<Key, Info>::size() const noexcept {
    size_t size = 0;
    for (auto node: *this) { size++; }
    return size;
}

template<typename Key, typename Info>
std::pair<typename sllist<Key,Info>::Iter, bool> sllist<Key, Info>::find(const Key &key) {
    node compare{ {key, {}} };
    auto curr = begin();
    for (; curr != end(); ++curr){
        if (*curr == compare) return {curr, true};
        if (*curr > compare)  return {curr, false}; // stop early - we here we know that this element should be here but is not
    }
    return {curr, false}; // curr = end() so element not found
}

template<typename Key, typename Info>
Info& sllist<Key, Info>::at(const Key &key) {
    auto [position, found] = find(key);
    if (!found) throw std::out_of_range("Element not in the container");
    return (*position).pair.second;
}

template<typename Key, typename Info>
Info &sllist<Key, Info>::operator[](Key&& key) {
    auto [position, found] = find(key);
    if (!found){
        auto new_node = alloc_node( {key, {}} );
        insert_after(position, new_node);
        return new_node->pair.second; // return new Info reference
    }
    return (*position).pair.second; // return reference to an existing value
}

template<typename Key, typename Info>
void sllist<Key, Info>::clear() noexcept {
    auto current = begin();
    while (current != end()){
        erase(current); // changes value of current to next value after deletion, no ++curr needed!
    }
}

template<typename Key, typename Info>
std::pair<typename sllist<Key,Info>::Iter, bool> sllist<Key, Info>::insert(std::pair<Key, Info> &&pair) {
    auto [position, found] = find(pair.first);
    if (found) return {position, false};
    auto new_node = alloc_node(pair);
    insert_after(position, new_node);
    return {new_node, true};
}

template<typename Key, typename Info>
std::pair<typename sllist<Key,Info>::Iter, bool> sllist<Key, Info>::insert_or_assign(Key &&key, Info&& info) {
    auto [position, found] = find(key);
    if (found) { (*position).pair.second = info; return {position, false}; }
    auto new_node = alloc_node({key, info});
    insert_after(position, new_node);
    return {new_node, true};
}

template<typename Key, typename Info>
std::pair<typename sllist<Key,Info>::Iter, bool> sllist<Key, Info>::emplace(Key &&key, Info &&info) {
    auto [position, found] = find(key);
    if (found) return std::make_pair(position, false);
    auto new_node = alloc_node({key, info});
    insert_after(position, new_node);
    return std::make_pair(Iter{new_node}, true);
}

template<typename Key, typename Info>
typename sllist<Key,Info>::Iter sllist<Key, Info>::erase(sllist::Iter pos) {
    dealloc_node( pos._ptr );
    return pos;
}

template<typename Key, typename Info>
typename sllist<Key,Info>::Iter sllist<Key, Info>::erase(sllist::Iter first, const sllist::Iter& last) {
    while (first != last) { erase(first); }
    return first;
}

template<typename Key, typename Info>
size_t sllist<Key, Info>::erase(const Key &key) {
    auto [position, found] = find(key);
    if (!found) return 0;
    erase(position);
    return 1;
}

template<typename Key, typename Info>
void sllist<Key, Info>::swap(sllist &other) noexcept {
    auto temp = this->head;
    this->head = other.head;
    other.head = temp;
}

template< class Key, class Info, class Pred >
size_t erase_if( sllist<Key, Info>& c, Pred pred ){
    size_t count = 0;
    for (auto curr = c.begin(); curr != c.end();){
        if (pred(*curr)) { ++count; c.erase(curr); }
        else ++curr;
    }
    return count;
};

#endif //LABS_SLLIST_H
