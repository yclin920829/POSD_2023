#pragma once

#include <iostream>

#include "file.h"
#include "node.h"

using namespace std;

class Link: public Node {
public:
    // TODO: implement it
    Link(string path, Node * target): Node(path), _target(target) {
        cout << "Link::Link()" << endl;
        cout << "path: " << path << endl;
        cout << "target path: " << target->path() << endl;
    }

    // TODO: implement it
    int numberOfFiles() const override {
        cout << "Link::numberOfFiles()" << endl;
        return _target->numberOfFiles();
    }

    // TODO: implement it
    Node * find(string path) override {
        cout << "Link::find()" << endl;
        return _target->find(path);
    }

    // TODO: implement it
    std::list<string> findByName(string name) override {
        cout << "Link::findByName()" << endl;
        return _target->findByName(name);
    }

    // TODO: implement it
    void add(Node * node) override {
        cout << "Link::add()" << endl;
        _target->add(node);
    }

    // TODO: implement it
    void remove(string path) override {
        cout << "Link::remove()" << endl;
        _target->remove(path);
    }

    // TODO: implement it
    Node * getChildByName(const char * name) const override {
        cout << "Link::getChildByName()" << endl;
        return _target->getChildByName(name);
    }

    // TODO: implement it
    Node * getTarget() {
        cout << "Link::getTarget()" << endl;
        return _target;
    }

    // TODO: implement it
    void accept(Visitor * guest) override {
        cout << "Link::accept()" << endl;
        _target->accept(guest);
    }

private:
    string _path;
    Node * _target;
};
