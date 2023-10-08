#if !defined(FOLDER)
#define FOLDER

#pragma once 
#include "./node.h"

#include <string>
#include <vector>


using namespace std;

class Folder: public Node {
public:
    Folder(string path):_path(path){};

    string name() const override{
        return _path.substr(_path.find_last_of("/") + 1);
    };

    string path() const override{
        return _path;
    };

private: 
    string _path;

};


#endif // FOLDER
