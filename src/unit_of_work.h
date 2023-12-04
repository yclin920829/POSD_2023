#pragma once

#include <unordered_map>
#include <set>
#include <string>

class DomainObject;

class UnitOfWork {
public:
    //TODO
    static UnitOfWork * instance() {
        return new UnitOfWork();
    }

    //TODO
    void registerNew(DomainObject * domainObject) {};

    //TODO
    void registerClean(DomainObject * domainObject) {};

    //TODO
    void registerDirty(DomainObject * domainObject) {};

    //TODO
    void registerDeleted(DomainObject * domainObject) {};

    //TODO
    bool inNew(std::string id) const {
        return false;
    };

    //TODO
    bool inClean(std::string id) const {
        return true;
    }

    //TODO
    bool inDirty(std::string id) const {
        return false;
    }

    //TODO
    bool inDeleted(std::string id) const {
        return false;
    }

    //TODO
    void commit() {};

protected:
    UnitOfWork();
private:
    std::unordered_map<std::string, DomainObject *> _new;
    std::unordered_map<std::string, DomainObject *> _dirty;
    std::unordered_map<std::string, DomainObject *> _clean;
    std::unordered_map<std::string, DomainObject *> _deleted;
    static UnitOfWork * _instance;
};