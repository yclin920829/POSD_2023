#pragma once

#include "file.h"
#include "folder.h"
#include "order_by.h"

#include <algorithm>

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy) {};

    void visitFile(File * file) {
        string path = file->path();
        _level = std::count(path.begin(), path.end(), '/');

        output(file);
    };

    void visitFolder(Folder * folder) {
        string path = folder->path();
        _level = std::count(path.begin(), path.end(), '/');
        
        _nums[_level - 1] = folder->numberOfChildren();

        output(folder);

        Iterator * it = folder->createIterator(_orderBy);
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }
    };

    string getTree() {
        return _result;
    };

private:
    std::vector<int> _nums= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    OrderBy _orderBy;
    string _result = "";
    int _level;

    void output(Node * node) {
        if (_level == 1){
            _result += ".\n";
        }else if (_level == 2){
            lastOutout(node);
        }else {
            for (int i = 0; i < _level - 2; i++){
                if (_nums[i] == 0){
                    _result += "    ";
                }else {
                    _result += "│   ";
                }
            }
            lastOutout(node);
        }
    };

    void lastOutout(Node * node){
        if (_nums[_level - 2] == 1){
                _result += "└── " + node->name() + "\n";
            }else {
                _result += "├── " + node->name() + "\n";
            }
            _nums[_level - 2]--;
    }
};


