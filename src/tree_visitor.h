#pragma once

#include "visitor.h"
#include "file.h"
#include "folder.h"
#include "order_by.h"

#include <iostream>
#include <string>
#include <algorithm>

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy) {};

    

    void visitFile(File * file) {
        // std::cout << "visit file" << std::endl;
        std::string path = file->path();
        // std::cout << "file path: " << path << std::endl;
        // std::cout << "file name: " << file->name() << std::endl;
        int occurrences = std::count(path.begin(), path.end(), '/');
        // std::cout << "occurrences: " << occurrences << std::endl;

        // std::cout << "current level: " << currentLevel << std::endl;
        // std::cout << "now nums: " << _nums[currentLevel] << std::endl;
        // std::cout << std::endl;

        // stringstream ss;
        // ss << currentLevel;
        // _result += ss.str();

        if (occurrences == 1){
            _result += ".\n";
        }else if (occurrences == 2){
            if (_nums[occurrences - 2] == 1){
                _result += "└── " + file->name() + "\n";
            }else {
                _result += "├── " + file->name() + "\n";
            }
            _nums[occurrences - 2]--;
        }else {
            // for (int i = 0; i < occurrences - 2; i++){
            //     if (_nums[i] == 1){
            //         _result += "    ";
            //     }else {
            //         _result += "│   ";
            //     }
            // }
            for (int i = 0; i < occurrences - 2; i++){
                if (_nums[i] == 0){
                    _result += "    ";
                }else {
                    _result += "│   ";
                }
            }
            // _result += "├── " + file->name() + "\n";
            if (_nums[occurrences - 2] == 1){
                _result += "└── " + file->name() + "\n";
            }else {
                _result += "├── " + file->name() + "\n";
            }
            _nums[occurrences - 2]--;
        }
        

    };

    void visitFolder(Folder * folder) {
        // std::cout << "visit folder" << std::endl;
        string path = folder->path();
        // std::cout << "folder path: " << path << std::endl;
        // std::cout << "folder name: " << folder->name() << std::endl;
        int occurrences = std::count(path.begin(), path.end(), '/');
        // std::cout << "occurrences: " << occurrences << std::endl;
        // std::cout << "number of children: " << folder->numberOfChildren() << std::endl;
        

        _nums[occurrences - 1] = folder->numberOfChildren();

        // std::cout << "current level: " << currentLevel << std::endl;
        // std::cout << "now nums: " << _nums[currentLevel] << std::endl;
        // std::cout << std::endl;

        // stringstream ss;
        // ss << currentLevel;
        // _result += ss.str();

        if (occurrences == 1){
            _result += ".\n";
        }else if (occurrences == 2){
            if (_nums[occurrences - 2] == 1){
                _result += "└── " + folder->name() + "\n";
            }else {
                _result += "├── " + folder->name() + "\n";
            }
            _nums[occurrences - 2]--;
        }else {
            for (int i = 0; i < occurrences - 2; i++){
                if (_nums[i] == 1){
                    _result += "    ";
                }else {
                    _result += "│   ";
                }
            }
            // _result += "├── " + folder->name() + "\n";
            if (_nums[occurrences - 2] == 1){
                _result += "└── " + folder->name() + "\n";
            }else {
                _result += "├── " + folder->name() + "\n";
            }
            _nums[occurrences - 2]--;
        }


        // std::cout << std::endl;
        Iterator * it = folder->createIterator(_orderBy);
        for (it->first(); !it->isDone(); it->next()) {
            it->currentItem()->accept(this);
        }


    };

    string getTree() {
        // for (int i = 0; i < _nums.size(); i++){
        //     std::cout << "nums: " << _nums[i] << std::endl;
        // }
        return _result;
    };

private:
    std::vector<int> _nums= {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    // int currentLevel = -1;
    OrderBy _orderBy;
    string _result = "";
};


