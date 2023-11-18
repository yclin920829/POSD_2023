#pragma once

#include <map>
#include <string>
#include <iostream>

#include "value.h"

class JsonObject : public Value {
public:

    JsonObject() {};

    std::string toString() override {
        _result = "{\n";
        int size = _jsonMap.size();
        std::map<std::string, Value *>::iterator it = _jsonMap.begin();
        for (int count = 0; count < size; it++, count++)
        {
            _result += ("\"" + it->first + "\":" + it->second->toString());
            if (count != (size - 1)){
                _result += ",";
            }
            _result += "\n";
        }
        return _result + "}";
    }

    void set(std::string key, Value * value) {
        if (_jsonMap.find(key) == _jsonMap.end()) {
            _jsonMap.insert( std::pair<std::string,Value *>(key, value) );
        } else {
            _jsonMap[key] = value;
        }
    }

    Value * getValue(std::string value) {
        if (_jsonMap[value] == NULL) {
            throw "key not found";
        }
        return _jsonMap[value];
    }

    JsonIterator * createIterator() override {
        return new JsonObjectIterator(this);
    }

    void accept(JsonVisitor * visitor) override {
        visitor->visitJsonObject(this);
    }

    class JsonObjectIterator : public JsonIterator {
    public:
        JsonObjectIterator(JsonObject * jsonObject) : _jsonObject(jsonObject)  {}

        void first() override {
            _current = _jsonObject->_jsonMap.begin();
        };

        std::string currentKey() const override {
            return _current->first;
        };

        Value * currentValue() const override {
            return _current->second;
        };

        void next() override {
            _current++;
        };

        bool isDone() const override {
            return _current == _jsonObject->_jsonMap.end();
        }

    private:
        JsonObject * const _jsonObject;
        std::map<std::string, Value *>::iterator _current;
    };

private:
    std::string _result;
};

