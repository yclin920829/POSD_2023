#pragma once

#include "file.h"
#include "node.h"

class Link: public Node {
public:
    // TODO: implement it
    Link(string path, Node * target): Node(path), _target(target) {}

    // TODO: implement it
    int numberOfFiles() const override {
        return 0;
    }

    // TODO: implement it
    Node * find(string path) override {
        return new File(path);
    }

    // TODO: implement it
    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        pathList.push_back("not done yet");
        return pathList;
    }

    // TODO: implement it
    void add(Node * node) override {}

    // TODO: implement it
    void remove(string patth) override {}

    // TODO: implement it
    Node * getChildByName(const char * name) const override {
        return new File(name);
    }

    // TODO: implement it
    Node * getTarget() {
        return new File("not done yet");
    }

    // TODO: implement it
    void accept(Visitor * guest) override {}

private:
    string _path;
    Node * _target;
};
