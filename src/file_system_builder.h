#pragma once

#include <string>

#include "file.h"
#include "folder.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const
    {
        return new Folder("data/home");
    }

    void buildFile(string path) {
        // File * file = new File(path);
        // _root->add(file);
        
    }

    void buildFolder(string path) {
        // Folder * folder = new Folder(path);
        // _root->add(folder);
    };

    void endFolder() {
        // _root = _root->parent();
    };

private:
    Folder * _root;
};
