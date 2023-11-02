#pragma once

#include <string>
#include <iostream>

#include "json_iterator.h"

using std::string;

class Value {
public:
    virtual string toString() {
        return "";
    }

    virtual JsonIterator * createIterator() {
        return new NullIterator();
    }
};