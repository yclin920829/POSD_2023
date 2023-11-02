#pragma once

#include <string>
#include <iostream>

#include "file.h"
#include "folder.h"

using std::string;

class FileSystemBuilder {
public:
    Folder * getRoot() const
    {
        std::cout << "getBuilderRoot" << std::endl;
        std::cout << "builderSuperPath: " << _path << std::endl;
        return _root;
    }

    void buildFile(string path) {
        std::cout << "buildFile: " << path << std::endl;
        File * file = new File(path);
        _path = getSuperPath(path);
        _nodes.push_back(file);
    }

    void buildFolder(string path) {
        std::cout << "buildFolder: " << path << std::endl;
        Folder * folder = new Folder(path);
        _path = getSuperPath(path);
        _nodes.push_back(folder);
    };

    void endFolder() {
        std::cout << "endFolder" << std::endl;
        _root = new Folder(_path);

        std::cout << "father: " << _root->path() << std::endl;
        for (auto node: _nodes) {
            std::cout << "node: " << node->path() << std::endl;
        }
        while (!_nodes.empty()) {
            std::cout << "child: " << _nodes.front()->name() << std::endl;
            _root->add(_nodes.front());
            _nodes.pop_front();
        }

    };

private:
    Folder * _root;
    string _path;
    std::list<Node *> _nodes;

    string getSuperPath(string path) {
        string superPath = path.substr(0, path.find_last_of("/"));
        // std::cout << "superPath: " << superPath << std::endl;
        return superPath;
    };

};
