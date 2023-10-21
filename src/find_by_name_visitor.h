#pragma once

#include <list>
#include <string>

#include "file.h"
#include "folder.h"
#include "visitor.h"

class FindByNameVisitor : public Visitor {
public:
    FindByNameVisitor(string name): _name(name) {};

    void visitFile(File * file) override {
        _paths = file->findByName(_name);
    };

    void visitFolder(Folder * folder) override {
        _paths = folder->findByName(_name);
    }

    std::list<string> getPaths() const {
        return _paths;
    };

private:
    string _name;
    std::list<string> _paths;
};