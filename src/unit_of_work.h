#pragma once

#include <unordered_map>
#include <set>
#include <string>

class DomainObject;

class UnitOfWork {
public:
    static UnitOfWork * instance();

    void registerNew(DomainObject * domainObject);

    void registerClean(DomainObject * domainObject);

    void registerDirty(DomainObject * domainObject);

    void registerDeleted(DomainObject * domainObject);

    bool inNew(std::string id) const;

    bool inClean(std::string id) const;

    bool inDirty(std::string id) const;

    bool inDeleted(std::string id) const;

    void commit();

protected:
    UnitOfWork();
private:
    static UnitOfWork * _instance;
};