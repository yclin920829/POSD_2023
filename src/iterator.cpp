#include "iterator.h"
#include "folder.h"
#include "file.h"

#include <iostream>

FolderIterator::FolderIterator(Folder * compound): _folder(compound) {}

void FolderIterator::first() {
    _it = _folder->_nodes.begin();
    // cout << "first\n";
}

bool FolderIterator::isDone() const {
    return _it == _folder->_nodes.end();
    // cout << "isDone\n";
}

Node * FolderIterator::currentItem() const {
    return *_it;
    // cout << "currentItem\n";
}

void FolderIterator::next() {
    _it++;
    // cout << "next\n";
}