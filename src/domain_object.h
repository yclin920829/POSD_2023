#pragma once

#include <string>

class DomainObject {
public:
    DomainObject(std::string id): _id(id) {}

    std::string id() const {
        return _id;
    }

    std::string type() const {
        return typeid(*this).name();
    }

    virtual ~DomainObject() {}
    
protected:
    std::string _id;
};