#pragma once

#include "file.h"
#include "folder.h"
#include "visitor.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/stat.h>

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

        _it = folder->createIterator();
        for (_it->first(); !_it->isDone(); _it->next()) {
            // _result << _it->currentItem()->path() << "\n";
            struct stat sb;
            stat(_it->currentItem()->path().c_str(), &sb);
            if (S_ISREG(sb.st_mode)) {
                _it->currentItem()->accept(this);
                _result << "\n";
            }else{
                StreamOutVisitor * streamOutVisitor = new StreamOutVisitor();
                _it->currentItem()->accept(streamOutVisitor);
                _result << streamOutVisitor->getResult();
                // _it->currentItem()->accept(this);
            }
        }
        
    };     

    string getResult() const {
        return _result.str();
    }

private:
    string _path;
    stringstream _result;
    Iterator * _it;
};