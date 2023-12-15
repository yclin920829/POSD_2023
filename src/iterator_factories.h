#pragma once

#include "./folder.h"
#include "iterator_factory.h"

// TODO: not sure
class FolderIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        return new FolderIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::FolderIterator(node, operationCount);
    }
};

// TODO: not sure
class OrderByNameIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        return new OrderByNameIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameIterator(node, operationCount);
    }
};

// TODO: not sure
class OrderByNameWithFolderFirstIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        return new OrderByNameWithFolderFirstIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByNameWithFolderFirstIterator(node, operationCount);
    }
};

// TODO: not sure
class OrderByKindIteratorFactory: public IteratorFactory {
public:
    static IteratorFactory * instance() {
        return new OrderByKindIteratorFactory();
    }

    Iterator * create(Folder * node, int operationCount) override {
        return new Folder::OrderByKindIterator(node, operationCount);
    }
};
