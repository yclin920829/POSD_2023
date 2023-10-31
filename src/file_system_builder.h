#pragma once

#include <string>

#include "folder.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const
    {
        return nullptr;
    }

    void buildFile(string path) {}

    void buildFolder(string path) {};

    void endFolder() {};
};
