#pragma once

#include <string>

#include "value.h"

class StringValue : public Value {
public:

    StringValue(std::string value): _value(value) {};

    std::string toString() override {
        return "\"" + _value + "\"";
    }

private:
    std::string _value;
};