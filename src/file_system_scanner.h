#pragma once

#include <string>

using std::string;

class FileSystemScanner {
public:
    bool isFile() {
        return false;
    };

    bool isFolder() {
        return false;
    };

    bool isDone() {
        return false;
    };

    void setPath(string path) {};

    string currentNodeName() {
        return "";
    };

    void nextNode() {};
};
