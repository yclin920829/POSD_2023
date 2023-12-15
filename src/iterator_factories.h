#pragma once

#include "./folder.h"
#include "iterator_factory.h"

// TODO: not sure
class FolderIteratorFactory: public IteratorFactory {
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::FolderIterator(node, operationCount);
    }
};

// TODO: not sure
class OrderByNameIteratorFactory: public IteratorFactory {
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameIterator(node, operationCount);
    }
};

// TODO: not sure
class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }
};

// TODO: not sure
class OrderByKindIteratorFactory: public IteratorFactory {
    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByKindIterator(node, operationCount);
    }
};
