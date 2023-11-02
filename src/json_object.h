#pragma once

#include <sstream>
#include <list>

#include "./value.h"

class JsonObject : public Value {
public:
    JsonObject(){};

    string toString() override {
        _result += "{\n";
        auto it_key = _key.begin();
        auto it_value = _value.begin();
        int count = 1;
        int size = _key.size();
        std:: cout << "size: " << size << "\n";
        for (; it_key != _key.end(); it_key++, it_value++, count++) {

            std::cout << "key: " << *it_key << "\n";
            _result += "\"" + *it_key + "\"";
            _result += ":";
            string temp = (*it_value)->toString();
            std::cout << "value: " << temp << "\n";
            _result += temp;
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
        auto it_key = _key.begin();
        auto it_value = _value.begin();
        for (; it_key != _key.end(); it_key++, it_value++) {
            if (key == (*it_key)){
                // std::cout << *it_key << " is find.\n";
                // std::cout << "it_key value is " << (*it_value)->toString() << "\n";
                return (*it_value); 
            }
            // it_value++;
        }
        return _value.front();
    }

private:
    std::list<string> _key;
    std::list<Value *> _value;

    string _result;

};