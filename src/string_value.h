#pragma once

#include "value.h"

class StringValue : public Value {
public:
    StringValue(string value):_value(value) {}

    string toString() {
        return "\"" + _value + "\"";
    }

private:
    string _value;
};