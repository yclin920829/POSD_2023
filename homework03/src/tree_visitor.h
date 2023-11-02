#pragma once

#include "visitor.h"
#include "file.h"
#include "folder.h"
#include "order_by.h"

#include <iostream>

class TreeVisitor: public Visitor {
public:
    TreeVisitor(OrderBy orderBy): _orderBy(orderBy) {    };

    void visitFile(File * file) {
        // std::cout << "visit file\n" << std::endl;
    };

    void visitFolder(Folder * folder) {
        // std::cout << "visit folder\n" << std::endl;
        Iterator * it = folder->createIterator(_orderBy);
        for (it->first(); !it->isDone(); it->next()) {
            std::cout << it->currentItem()->name() << std::endl;

            it->currentItem()->accept(this);
        }
    };

    string getTree() {
        return "";
    };

private:
    OrderBy _orderBy;
};