#if !defined(ITERATOR_H)
#define ITERATOR_H

#pragma once 

#include<list>
#include<vector>

#pragma once 

class Node;
class Folder;

class Iterator {
public:
    virtual ~Iterator() = default;
    virtual void first() = 0;
    virtual Node * currentItem() const = 0;
    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class FolderIterator : public Iterator {
public:
    FolderIterator(Folder* composite);
    void first() override;
    Node * currentItem() const override;
    void next() override;
    bool isDone() const override;

private:
    Folder * _folder;
    std::vector<Node *>::iterator _it;
};


#endif // ITERATOR_H
