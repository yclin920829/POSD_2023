#pragma once

#include <string>
#include <iostream>

#include "visitor.h"
#include "json_object.h"
#include "string_value.h"

class BeautifyVisitor : public JsonVisitor {
public:
    void visitJsonObject(JsonObject * obj) override {
        JsonIterator * it = obj->createIterator();
        for(it->first(); !it->isDone(); it->next()) {
            if(dynamic_cast<JsonObject *>(it->currentValue())){
                // std::cout << "it is json object.\n";
                // std::cout << _space << it->currentKey() << ": {\n";
                _result += (_space + it->currentKey() + ": {\n");
                _space += "    ";
            } else {
                // std::cout << "it is string value\n";
                // std::cout << _space << it->currentKey() << ": ";
                _result += (_space + it->currentKey() + ": ");
            }
            it->currentValue()->accept(this);
            if(dynamic_cast<JsonObject *>(it->currentValue())){
                _space.erase(_space.begin(), _space.begin() + 4);
                // std::cout << _space  << "}\n";
                _result += (_space + "}\n");
            }
        }
    }

    void visitStringValue(StringValue * val) override {
        // std::cout << val->toString() << "\n";
        _result += (val->toString() + "\n");
    }

    std::string getResult() const {
        return "{\n" + _result + "}\n";
    }

private:
    std::string _result;
    std::string _space = "    ";
};