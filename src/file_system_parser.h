#pragma once

#include <string>
#include <list>

#include "folder.h"
#include "file_system_scanner.h"
#include "file_system_builder.h"

using std::string;

class FileSystemParser {
public:
    FileSystemParser(FileSystemBuilder * builder): _builder(builder) {};

    Folder * getRoot() const {
        cout << "getParserRoot" << endl;
        // return new Folder("data/home");
        return _builder->getRoot();
    };

    void parse() {
        scanner = new FileSystemScanner();
        for (scanner->setPath(_path); !scanner->isDone(); scanner->nextNode()){
            string path = _path + "/" + scanner->currentNodeName();
            _files.push_back(path);
            std::cout << "\n" << path << std::endl;
            if (scanner->isFile()){
                std::cout << "is a file." << std::endl;
                _builder->buildFile(path);
            }else if (scanner->isFolder()){
                std::cout << "is a folder." << std::endl;
                // _builder->buildFolder(path);

                std::cout << "-----------------------------------" << std::endl;

                FileSystemParser * parser = new FileSystemParser(_builder);
                parser->setPath(path);
                parser->parse();

                // _builder->endFolder();
                std::cout << "-----------------------------------" << std::endl;

            }
        }
        _builder->endFolder();

        // std::cout << "-----------------------------------" << std::endl;
        // std::cout << "super path: " << _path << std::endl;
        // _builder->buildFolder(_path);
        // std::cout << std::endl;
        // for (std::list<string>::iterator it = _files.begin(); it != _files.end(); ++it){
        //     std::cout << *it << std::endl;
        //     _builder->buildFile(*it);
        //     std::cout << std::endl;
        // }
        // _builder->endFolder();
        // std::cout << std::endl;
        // std::cout << "-----------------------------------" << std::endl;
    };

    void setPath(string path) {
        _path = path;
        _builder->buildFolder(_path);
    };

private:

    std::list<string> _files;

    FileSystemBuilder * _builder;
    FileSystemScanner * scanner;
    string _path;

    string getSuperPath(string path) {
        string superPath = path.substr(0, path.find_last_of("/"));
        // std::cout << "superPath: " << superPath << std::endl;
        return superPath;
    };

};
