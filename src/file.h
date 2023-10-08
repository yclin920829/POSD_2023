#if !defined(FILE_H)
#define FILE_H

#pragma once 
#include "./node.h"

using namespace std;

class File: public Node {
private:
    string _path;

public:
    File(string path):_path(path){};

    string name() const override{
        // cout << "File name: " << _path.substr(_path.find_last_of("/") + 1) << endl;
        return _path.substr(_path.find_last_of("/") + 1);
    };

    string path() const override{
        return _path;
    };
    
};

#endif // FILE_H
