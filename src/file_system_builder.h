#pragma once

#include "file.h"
#include "folder.h"

class FileSystemBuilder {
public:
    Folder * getRoot() const {
        return _currentFolder;
    }

    void buildFile(string path) {
        _currentFolder->add(new File(path));
    }

    void buildFolder(string path) {
        if (_currentFolder != nullptr) {
            _superFolders.push_back(_currentFolder);
        }
        _currentFolder = new Folder(path);
    }

    void endFolder() {
        if (!_superFolders.empty()) {
            _superFolders.back()->add(_currentFolder);
            _currentFolder = _superFolders.back();
            _superFolders.pop_back();
        }
    }

private:
    Folder * _currentFolder = nullptr;
    std::list<Folder *> _superFolders;
};
