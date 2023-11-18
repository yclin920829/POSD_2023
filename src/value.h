#pragma once

#include <string>

#include "visitor.h"
#include "json_iterator.h"

class Value {
public:
    virtual std::string toString() = 0;

    virtual JsonIterator * createIterator() {
        return new NullIterator();
    }

    virtual void accept(JsonVisitor * visitor) = 0;

    int getSize() const {
        return _jsonMap.size();
    }

protected:
    std::map<std::string, Value *> _jsonMap;
};