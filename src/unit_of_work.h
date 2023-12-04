#pragma once

#include <unordered_map>
#include <set>
#include <string>

class DomainObject;

class UnitOfWork {
public:
    //TODO : class
    static UnitOfWork * instance();

    //TODO : class
    void registerNew(DomainObject * domainObject);

    //TODO : class
    void registerClean(DomainObject * domainObject);

    //TODO : class
    void registerDirty(DomainObject * domainObject);

    //TODO : class
    void registerDeleted(DomainObject * domainObject);

    //TODO : class
    bool inNew(std::string id) const;

    //TODO : class
    bool inClean(std::string id) const;

    //TODO : class
    bool inDirty(std::string id) const;

    //TODO : class
    bool inDeleted(std::string id) const;

    //TODO : class
    void commit();

protected:
    UnitOfWork();

private:
    std::unordered_map<std::string, DomainObject *> _new;
    std::unordered_map<std::string, DomainObject *> _dirty;
    std::unordered_map<std::string, DomainObject *> _clean;
    std::unordered_map<std::string, DomainObject *> _deleted;
    static UnitOfWork * _instance;
};