#pragma once

#include <string>
#include <iostream>
#include <sys/stat.h>

#include "node.h"

class File: public Node {
public:
    File(string path): Node(path) {
        if ( "file" != type()) {
            // cout << "Not a directory." << endl;
            throw string("Not a file.");
        }
    }

    int numberOfFiles() const override {
        return 1;
    }

    Node * find(string path) override {
        if (this->path() == path) {
            return this;
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }
        return pathList;
    }

    void accept(Visitor * visitor) override {
        // std::cout << "file accept to visit" << std::endl;
        visitor->visitFile(this);
    }
};