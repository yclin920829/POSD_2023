#pragma once

#include <string>
#include <iostream>

#include "file.h"
#include "folder.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const {
        return _currentFolder;
        // return new Folder("data/home");
    }

    void buildFile(string path) {
        // std::cout << "build a File: " << path << std::endl;
        File * file = new File(path);
        _currentFolder->add(file);
    }

    void buildFolder(string path) {
        // std::cout << "build a Folder: " << path << std::endl;
        Folder * folder = new Folder(path);

        if (_fatherFolders.empty()){
            // std::cout << "this is a root folder, their is no father " << std::endl;
        } else {
            // std::cout << "super dolder : " << _fatherFolders.back()->path() << std::endl;
        }

        if (_currentFolder == nullptr) {
            // std::cout << "currentFolder is NULL" << std::endl;
        } else {
            // std::cout << "currentFolder is not NULL" << std::endl;
            _fatherFolders.push_back(_currentFolder);
        }
        _currentFolder = folder;

        // std::cout << "currentFolder: " << _currentFolder->path() << std::endl;


    }

    void endFolder() {
        // std::cout << "\nendFolder" << std::endl;
        if (_fatherFolders.empty()){
            // std::cout << "this is a root folder, their is no father " << std::endl;
        } else {
            // std::cout << "super dolder : " << _fatherFolders.back()->path() << std::endl;
            Folder * super = _fatherFolders.back();
            // std::cout << "superFolder: " << super->path() << std::endl;

            _fatherFolders.pop_back();
            super->add(_currentFolder);
            _currentFolder = super;
        }
        

        // std::cout << "currentFolder: " << _currentFolder->path() << std::endl;

        

    };

private:

    Folder * _currentFolder = nullptr;
    std::list<Folder *> _fatherFolders;

    string getSuperPath(string path) {
        string superPath = path.substr(0, path.find_last_of("/"));
        // std::cout << "superPath: " << superPath << std::endl;
        return superPath;
    };
};
