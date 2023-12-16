#pragma once

#include <iostream>

#include "file.h"
#include "node.h"

using namespace std;

class Link: public Node {
public:
    // TODO: implement it
    Link(string path, Node * target): Node(path), _target(target) {}

    // TODO: implement it
    int numberOfFiles() const override {
        return _target->numberOfFiles();
    }

    // TODO: implement it
    Node * find(string path) override {
        return _target->find(path);
    }

    // TODO: implement it
    std::list<string> findByName(string name) override {
        return _target->findByName(name);
    }

    // TODO: implement it
    void add(Node * node) override {
        _target->add(node);
    }

    // TODO: implement it
    void remove(string path) override {
        _target->remove(path);
    }

    // TODO: implement it
    Node * getChildByName(const char * name) const override {
        return _target->getChildByName(name);
    }

    // TODO: implement it
    Node * getTarget() {
        return _target;
    }

    // TODO: implement it
    void accept(Visitor * visitor) override {
        visitor->visitLink(this);
    }

private:
    string _path;
    Node * _target;
};
