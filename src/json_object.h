#pragma once

#include <sstream>
#include <list>

#include "./value.h"

class JsonObject : public Value {
public:
    JsonObject(){};

    string toString() override {
        _result += "{\n";
        auto it = _key.begin();
        auto it2 = _value.begin();
        int count = 1;
        int size = _key.size();
        std:: cout << "size: " << size << "\n";
        for (; it != _key.end(); it++, it2++, count++) {

            std::cout << *it << " is find.\n";
            _result += "\"" + *it + "\"";
            _result += ":";
            std::cout << "it value is " << (*it2)->toString() << "\n";
            _result += (*it2)->toString();
            if (count != size){
                _result += ",";
            }
            _result += "\n";
           
        }
        _result += "}";

        return _result;
    }

    void set(string key, Value * value) {
        _key.push_back(key);
        _value.push_back(value);
    }

    Value * getValue(string key) {
        auto it = _key.begin();
        auto it2 = _value.begin();
        for (; it != _key.end(); it++, it2++) {
            if (key == (*it)){
                std::cout << *it << " is find.\n";
                std::cout << "it value is " << (*it2)->toString() << "\n";
                return (*it2); 
            }
            // it2++;
        }
        return _value.front();
    }

private:
    std::list<string> _key;
    std::list<Value *> _value;

    string _result;

};