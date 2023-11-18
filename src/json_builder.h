#pragma once

#include <list>
#include <string>

#include "json_object.h"
#include "string_value.h"

class JsonBuilder {
public:
    void buildValue(std::string key, std::string value) {
        _cueentobject->set(key, new StringValue(value));
    }

    void buildObject(std::string key){
        if(_cueentobject != nullptr){
            _superObjects.push_back(std::make_pair(key,_cueentobject));
        }
        _cueentobject = new JsonObject();
    }

    void endObject(){
        if(!_superObjects.empty()){
            std::pair<std::string,JsonObject *> superObject = _superObjects.back();
            superObject.second->set(superObject.first, _cueentobject);
            _cueentobject = superObject.second;
            _superObjects.pop_back();
        }
    }

    JsonObject * getJsonObject(){
        return _cueentobject;
    };

private:
    JsonObject * _cueentobject = nullptr;
    std::list<std::pair<std::string,JsonObject *>> _superObjects;
};
