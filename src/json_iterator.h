#pragma once

class Value;

class JsonIterator {
public:
    virtual void first() = 0;

    virtual std::string currentKey() const = 0;

    virtual Value * currentValue() const = 0;

    virtual void next() = 0;
    virtual bool isDone() const = 0;
};

class NullIterator : public JsonIterator {
    void first() override {};

    std::string currentKey() const override {
        throw "can't invoke NullIterator::currentKey()";
    };

    Value * currentValue() const override {
        throw "can't invoke NullIterator::currentValue()";
    };

    void next() override {};

    bool isDone() const override {
        return true;
    }
};