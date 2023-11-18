#pragma once

#include <string>

#include "visitor.h"
#include "json_object.h"
#include "string_value.h"

class BeautifyVisitor : public JsonVisitor {
public:
    void visitJsonObject(JsonObject * obj) override {
        JsonIterator * it = obj->createIterator();
        int count = 0;
        int size = obj->getSize();
        for(it->first(); !it->isDone(); it->next()) {
            count++;
            _result += (_space + "\""+ it->currentKey() + "\"");
            if(dynamic_cast<JsonObject *>(it->currentValue())){
                _result += ": {\n";
                _space += "    ";
                it->currentValue()->accept(this);
                _space.erase(_space.begin(), _space.begin() + 4);
                _result += (_space + "}");
            } else {
                _result += ": ";
                it->currentValue()->accept(this);
            }
            if (count != size) {
                _result += ",";
            }
            _result += "\n";
            
        }
    }

    void visitStringValue(StringValue * val) override {
        _result += (val->toString());
    }

    std::string getResult() const {
        return "{\n" + _result + "}";
    }

private:
    std::string _result;
    std::string _space = "    ";
};