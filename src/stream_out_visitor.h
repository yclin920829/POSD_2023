#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class StreamOutVisitor : public Visitor {
public:
    void visitFile(File * file) override {

        // cout << "visitorStream had visited a file" << endl;

        _path = file->path();

        _result << "_____________________________________________\n";
        _result << _path << "\n";
        _result << "---------------------------------------------\n";

        ifstream inputFile (_path);
        string text = "";
        while (getline (inputFile, text)) {
            _result << text << "\n";
        }
        _result << "_____________________________________________\n";
    };

    void visitFolder(Folder * folder) override {
        // cout << "visitorStream had visited a folder" << endl;
        _path = folder->path();

        _it = folder->dfsIterator();
        for (_it->first(); !_it->isDone(); _it->next()) {
            // cout << "path: " << _it->currentItem()->path() << endl;
            _it->currentItem()->accept(this);
        }
    };

    string getResult() const {
        // std::cout << "result:\n" << _result.str() << std::endl;
        return _result.str();
        // return "";
    }

private:
    string _path;
    stringstream _result;
    Iterator * _it;
};