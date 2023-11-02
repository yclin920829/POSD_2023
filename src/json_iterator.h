#pragma once

class Value;

#include <string>
#include <list>

#include "value.h"
#include "json_object.h"

using std::string;

class JsonIterator {
public:
    virtual void first() = 0;

    virtual std::string currentKey() const = 0;

    virtual Value * currentValue() const = 0;

    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

// class NullIterator : public JsonIterator {
// public:
//     void first() override {};

//     std::string currentKey() const override {};

//     Value * currentValue() const override {};

//     void next() override {};

//     bool isDone () const override {
//         return true;
//     }

// };

class JsonObjectIterator : public JsonIterator {
public:
    // JsonObjectIterator(JsonObject * jasonObject): _jsonObject(jasonObject)  {}
    JsonObjectIterator(JsonObject * jsonObject)  {
        _jsonObject = jsonObject;
    }

    void first() override {
        _currentKey = _jsonObject->_key.begin();
        _currentValue = _jsonObject->_value.begin();
    };

    std::string currentKey() const override {
        return * _currentKey;
    };

    Value * currentValue() const override {
        return * _currentValue;
    };

    void next() override {
        _currentKey++;
        _currentValue++;

    };

    bool isDone() const override {
         return _currentKey == _jsonObject->_key.end();
    };

private:
    JsonObject * _jsonObject;
    std::list<string>::iterator _currentKey;
    std::list<Value *>::iterator _currentValue;

};