#pragma once

#include "file_system_scanner.h"
#include "file_system_builder.h"

class FileSystemParser {
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder) {};

    Folder * getRoot() const {
        return _builder->getRoot();
    };

    void parse() {
        _builder->buildFolder(_path);
        scanner = new FileSystemScanner();
        for (scanner->setPath(_path); !scanner->isDone(); scanner->nextNode()){
            string path = _path + "/" + scanner->currentNodeName();
            if (scanner->isFile()){
                _builder->buildFile(path);
            }else if (scanner->isFolder()){
                FileSystemParser * parser = new FileSystemParser(_builder);
                parser->setPath(path);
                parser->parse();
            }
        }
        _builder->endFolder();
    };

    void setPath(string path){
        _path = path;
    };

private:
    string _path;
    FileSystemBuilder * _builder;
    FileSystemScanner * scanner;
};