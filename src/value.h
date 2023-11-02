#pragma once

#include <string>
#include <iostream>

using std::string;

class Value {
public:
    virtual string toString() {
        return "";
    }
};