#pragma once

#include<string>

#include "visitor.h"
#include "iterator.h"
#include "null_iterator.h"
#include "iterator_factory.h"

using namespace std;

class Node {
private:
    string _path;
    Node * _parent;
protected:

    Node(string path): _path(path) {}

public:
    virtual ~Node() {}

    Node * parent() {
        return _parent;
    }

    void parent(Node * parent) {
        _parent = parent;
    }
    
    virtual void removeChild(Node * target) {
        throw string("This node does not support removing sub node");
    }

    string name() const {
        size_t slash = _path.rfind("/");
        return _path.substr(slash+1);
    }
    
    string path() const {
        return _path;
    }
    
    virtual void add(Node * node) {
        throw string("This node does not support adding sub node");
    }

    virtual Node * getChildByName(const char * name) const {
        return nullptr;
    }

    virtual int numberOfFiles() const = 0;

    virtual Iterator * createIterator() {
        return new NullIterator();
    }

    virtual Iterator * createIterator(IteratorFactory * factory) {
        return new NullIterator();
    }

    virtual Node * find(string path) = 0;

    virtual std::list<string> findByName(string name) = 0;

    virtual void remove(string path) {
        throw string("This node does not support deleting sub node");
    }

    virtual void accept(Visitor * visitor) = 0;

    // TODO: not sure if this is correct
    void rename(string name) {
        string oldName = this->name();
        updateNodePath(oldName, name);
        updateChildrenPath(oldName, name);
    }

    // TODO: not sure if this is correct
    void updateNodePath(string oldName, string newName) {
        _path.replace(_path.find(oldName), oldName.length(), newName);
    }

    // TODO: not sure if this is correct
    virtual void updateChildrenPath(string oldName, string newName){

    }

    
};
