#pragma once

#include "node.h"

class Link: public Node {
public:

    // TODO: implement it
    int numberOfFiles() const override {}

    // TODO: implement it
    Node * find(string path) override {}

    // TODO: implement it
    std::list<string> findByName(string name) override {}

    // TODO: implement it
    void add(Node * node) override {}

    // TODO: implement it
    void remove(string patth) override {}

    // TODO: implement it
    Node * getChildByName(const char * name) const override {}

    // TODO: implement it
    Node * getTarget() {}

    // TODO: implement it
    void accept(Visitor * guest) override {}
};
