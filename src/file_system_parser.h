#pragma once

#include <string>

#include "folder.h"
#include "file_system_scanner.h"
#include "file_system_builder.h"

using std::string;

class FileSystemParser {
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder) {};

    Folder * getRoot() const {
        return new Folder("data/home");
    };

    void parse() {
        // FileSystemScanner * scanner = new FileSystemScanner();
        // scanner->setPath(_path);
        // while (!scanner->isDone()) {
        //     if (scanner->isFile()) {
        //         _builder->buildFile(scanner->currentNodeName());
        //     } else if (scanner->isFolder()) {
        //         _builder->buildFolder(scanner->currentNodeName());
        //     }
        //     scanner->nextNode();
        // }
    };

    void setPath(string path) {
        // _path = path;
    };

private:
    FileSystemBuilder * _builder;
    string _path;
};
