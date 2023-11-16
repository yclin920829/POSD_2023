#pragma once

#include <string>

#include "value.h"

class StringValue : public Value {
public:

    StringValue(std::string value): _value(value) {};

    std::string toString() override {
        return "\"" + _value + "\"";
    }

    void accept(JsonVisitor * visitor) override {
        visitor->visitStringValue(this);
    }

private:
    std::string _value;
};