#if !defined(FOLDER)
#define FOLDER

#pragma once 
#include "./node.h"

#include <string>
#include <vector>
#include <typeinfo>


using namespace std;

class Folder: public Node {
public:
    Folder(string path):_path(path){
        _nodes = new vector<Node *>();

    };

    string name() const override{
        return _path.substr(_path.find_last_of("/") + 1);
    };

    string path() const override{
        return _path;
    };

    void add(Node * node) override{
        _nodes->push_back(node);
    };

    void remove(string path) override{
        auto it = remove_if(_nodes->begin(), _nodes->end(), [&](Node* node) {
            return node->path() == path;
        });
        _nodes->erase(it, _nodes->end());
    }

    Node * getChildByName(const char * name) const override{
        for (auto node: *_nodes){
            if (node->name() == name){
                return node;
            }
        }
        return nullptr;
    };

    Node * find(string path) override{
        for (auto node: *_nodes){
            if (node->path() == path){
                return node;
            }
        }
        return nullptr;
    };

    int numberOfFiles() const override{
        int count = 0;
        for (auto node: *_nodes){
            if (typeid(*node) == typeid(Folder)){
                count += node->numberOfFiles();
            }else{
                count += 1;
            }
        }
        return count;
    };

private: 
    string _path;
    vector<Node *>* _nodes;

};


#endif // FOLDER
