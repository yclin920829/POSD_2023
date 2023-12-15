#pragma once

#include <iostream>

#include "file.h"
#include "node.h"

using namespace std;

class Link: public Node {
public:
    // TODO: implement it
    Link(string path, Node * target): Node(path), _target(target) {
        cout << "Link path: " << path << endl;
        cout << "Target: " << target->path() << endl;
    }

    // TODO: implement it
    int numberOfFiles() const override {
        cout << "Link::numberOfFiles()" << endl;
        return 0;
    }

    // TODO: implement it
    Node * find(string path) override {
        cout << "Link::find()" << endl;
        cout << "Path: " << path << endl;
        return new File(path);
    }

    // TODO: implement it
    std::list<string> findByName(string name) override {
        cout << "Link::findByName()" << endl;
        std::list<string> pathList;
        pathList.push_back(name);
        return pathList;
    }

    // TODO: implement it
    void add(Node * node) override {
        cout << "Link::add()" << endl;
        cout << "Node: " << node->path() << endl;
    }

    // TODO: implement it
    void remove(string patth) override {
        cout << "Link::remove()" << endl;
        cout << "Path: " << patth << endl;
    }

    // TODO: implement it
    Node * getChildByName(const char * name) const override {
        cout << "Link::getChildByName()" << endl;
        return new File(name);
    }

    // TODO: implement it
    Node * getTarget() {
        cout << "Link::getTarget()" << endl;
        return new File("not done yet");
    }

    // TODO: implement it
    void accept(Visitor * guest) override {
        cout << "Link::accept()" << endl;
    }

private:
    string _path;
    Node * _target;
};
