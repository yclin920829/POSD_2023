#pragma once

#include <iostream>
#include "iterator.h"

class NullIterator : public Iterator {
public:
    NullIterator() {
        std::cout << "NullIterator::NullIterator()" << std::endl;
    }

    bool isDone () const override {
        return true;
    }
};
