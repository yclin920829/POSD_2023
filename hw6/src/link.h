#pragma once

#include <iostream>

#include "file.h"
#include "node.h"

using namespace std;

class Link: public Node {
public:
    Link(string path, Node * target): Node(path), _target(target) {}

    int numberOfFiles() const override {
        return _target->numberOfFiles();
    }

    Node * find(string path) override {
        return _target->find(path);
    }

    std::list<string> findByName(string name) override {
        return _target->findByName(name);
    }

    void add(Node * node) override {
        _target->add(node);
    }

    void remove(string path) override {
        _target->remove(path);
    }

    Node * getChildByName(const char * name) const override {
        return _target->getChildByName(name);
    }

    Node * getTarget() {
        return _target;
    }

    void accept(Visitor * visitor) override {
        visitor->visitLink(this);
    }

private:
    string _path;
    Node * _target;
};
