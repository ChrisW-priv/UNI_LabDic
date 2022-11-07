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
public:
    ///methods to make out container useful ...///
};

#endif //LABS_SLLIST_H
