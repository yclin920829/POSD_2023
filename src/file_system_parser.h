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
        cout << "getParserRoot" << endl;
        return new Folder(_path);
        // return _builder->getRoot();
    };

    void parse() {
        scanner = new FileSystemScanner();
        for (scanner->setPath(_path); !scanner->isDone(); scanner->nextNode()){
            string path = _path + "/" + scanner->currentNodeName();
            std::cout << "\n" << path << std::endl;
            if (scanner->isFile()){
                std::cout << "is a file." << std::endl;
                // _builder->buildFile(path);

            }else if (scanner->isFolder()){
                std::cout << "is a folder." << std::endl;
                // _builder->buildFolder(path);

                std::cout << "-----------------------------------" << std::endl;

                FileSystemParser * parser = new FileSystemParser(_builder);
                parser->setPath(path);
                parser->parse();

                std::cout << "-----------------------------------" << std::endl;
                // _builder->endFolder();

            }
        }
        // _builder->endFolder();
    };

    void setPath(string path) {
        _path = path;
    };

private:
    FileSystemBuilder * _builder;
    FileSystemScanner * scanner;
    string _path;
};
