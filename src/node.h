#if !defined(NODE_H)
#define NODE_H

#include<string>
#include "./iterator.h"

using namespace std;

class Node {
public:

    virtual string name() const = 0;
    
    virtual string path() const = 0;
    
    virtual void add(Node * node) {};

    virtual void remove(string path) {};
    
    virtual Node * getChildByName(const char * name) const { return nullptr; };

    virtual Node * find(string path) { return nullptr; };

    virtual int numberOfFiles() const { return 0; };
    
    // virtual Iterator * createIterator() { return nullptr; };
    virtual Iterator * createIterator() = 0;
};


#endif // NODE_H

