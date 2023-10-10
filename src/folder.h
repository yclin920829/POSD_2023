#if !defined(FOLDER)
#define FOLDER

#pragma once 
#include "./node.h"
#include "./file.h"
#include "./iterator.h"
#include "./null_iterator.h"

#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <iostream>

using namespace std;

class Folder: public Node {
    friend class FolderIterator;
public:
    Folder(string path):_path(path){};

    string name() const override{
        return _path.substr(_path.find_last_of("/") + 1);
    };

    string path() const override{
        return _path;
    };

    void add(Node * node) override{
        if (typeid(*node) == typeid(File)){
            string folder = _path.substr(0, _path.find_last_of("/"));
            if (folder != node->path().substr(0, node->path().find_last_of("/"))){
                throw string("error");
            }
        }
        _nodes.push_back(node);
    };

    void remove(string path) override{
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it){
            if ((*it)->path() == path){
                _nodes.erase(it);
                break;
            }
        }
    }

    Node * getChildByName(const char * name) const override{
        for (auto node: _nodes){
            if (node->name() == name){
                // cout << "found" << endl;
                return node;
            }
        }
        return nullptr;
    };

    Node * find(string path) override{
        for (auto node: _nodes){
            if (node->path() == path){
                return node;
            }else if (typeid(*node) == typeid(Folder)){
                Node * result = node->find(path);
                if (result != nullptr){
                    return result;
                }
            }
        }
        return nullptr;
    };

    int numberOfFiles() const override{
        int count = 0;
        for (auto node: _nodes){
            if (typeid(*node) == typeid(Folder)){
                count += node->numberOfFiles();
            }else{
                count += 1;
            }
        }
        return count;
    };

    Iterator * createIterator() override{
        if (typeid(*this) == typeid(Folder)){
            return new FolderIterator(this);
        }else
        {
            return new NullIterator();
        }
    };

    private: 
        string _path;
        vector<Node *> _nodes;

};


#endif // FOLDER
