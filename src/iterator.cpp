#include "iterator.h"
#include "folder.h"
#include "file.h"

#include <iostream>

FolderIterator::FolderIterator(Folder * compound): _folder(compound) {}

void FolderIterator::first() {
    _it = _folder->_nodes.begin();
}

bool FolderIterator::isDone() const {
    return _it == _folder->_nodes.end();
}

Node * FolderIterator::currentItem() const {
    return *_it;
}

void FolderIterator::next() {
    _it++;
}