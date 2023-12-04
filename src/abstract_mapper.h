#pragma once

#include <unordered_map>
#include "domain_object.h"
#include "unit_of_work.h"
#include <iostream>
#include "drawing.h"

typedef int (*CallbackType)(void *, int argc, char **argv, char **col_names);

class AbstractMapper
{
public:
    virtual ~AbstractMapper() {}

    virtual std::string updateStmt(DomainObject *domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string addStmt(DomainObject *domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;

    void setDB(std::string db_file)
    {
        sqlite3_open(db_file.c_str(), &_db);
    }

    bool isLoaded(const std::string &id) const
    {
        return _domainObjects.count(id);
    }

    void cleanCache()
    {
        _domainObjects.clear();
    }

protected:
    std::unordered_map<std::string, DomainObject *> _domainObjects;
    sqlite3 *_db;

    DomainObject *getDomainObject(std::string id)
    {
        if (_domainObjects.count(id))
        {
            return _domainObjects.at(id);
        }
        return nullptr;
    }

    //TODO
    DomainObject * abstractFind(std::string id, CallbackType callback) {
        return nullptr;
    }

    //TODO
    void abstractAdd(DomainObject *domainObject) {};

    //TODO
    void abstractUpdate(DomainObject *domainObject) {};

    //TODO
    void abstractDelete(std::string id) {};

    //TODO
    void load(DomainObject *domainObject) {};

private:
};