#if !defined(FILE_H)
#define FILE_H

#pragma once 
#include "./node.h"
#include "./null_iterator.h"

using namespace std;

class File: public Node {
private:
    string _path;

public:
    File(string path):_path(path){};

    string name() const override{
        return _path.substr(_path.find_last_of("/") + 1);
    };

    string path() const override{
        return _path;
    };

    Iterator * createIterator() override{
        return new NullIterator();
    };

};

#endif // FILE_H
