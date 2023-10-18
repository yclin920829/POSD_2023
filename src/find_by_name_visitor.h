#pragma once

#include <list>
#include <string>
#include <iostream>

#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name): _name(name) {};

    void visitFile(File * file) override {
        // std::cout << "visitor had visited a file" << std::endl;
        _paths = file->findByName(_name);
    };

    void visitFolder(Folder * folder) override {
        // std::cout << "visitor had has visited a folder" << std::endl;
        _paths = folder->findByName(_name);
    }

    std::list<string> getPaths() const {
        return _paths;
    };

private:
    string _name;
    std::list<string> _paths;
};