#if !defined(DFS_ITERATOR_H)
#define DFS_ITERATOR_H

#include "iterator.h"
#include "file.h"
#include <iostream>
#include <typeinfo>
#include <queue>
#include <vector>

using namespace std;

class DfsIterator: public Iterator {
public:
    DfsIterator(Node* composite) {
        _node = composite;
        it = _node->createIterator();
    };

    void first() override {
        it->first();
    };

    Node * currentItem() const override {
        return it->currentItem();
    };

    void next() override{
        auto& r = *it->currentItem();
        if (typeid(r) != typeid(File)){
            Iterator * child = it->currentItem()->createIterator();
            _it_stack.push_back(it);
            child->first();
            it = child;
        }else
        {
            it->next();
        }        
        while (it->isDone()){
            if (_it_stack.empty())
                break;
            it = _it_stack.back();
            _it_stack.pop_back();
            it->next();
        }
    };
    
    bool isDone() const override{
        return it->isDone();
    };

private:
    Node * _node;
    Iterator * it;
    std::vector<Iterator *> _it_stack;
};

class BfsIterator: public Iterator {
public:
    BfsIterator(Node* composite){
        _node = composite;
        it = _node->createIterator();
    };

    void first() override {
        it->first();
    };

    Node * currentItem() const override {
        return it->currentItem();
    };

    void next() override{
        auto& r = *it->currentItem();
        if (typeid(r) != typeid(File)){
            Iterator * child = it->currentItem()->createIterator();
            child->first();
            _it_queue.push(child);
            it->next();
        }else
        {
            it->next();
        }        
        while (it->isDone()){
            if (_it_queue.empty())
                break;
            it = _it_queue.front();
            _it_queue.pop();
        }
    };
    
    bool isDone() const override{
        return it->isDone();
    };

private:
    Node * _node;
    Iterator * it;
    std::queue<Iterator *> _it_queue;
};

#endif // DFS_ITERATOR_H
