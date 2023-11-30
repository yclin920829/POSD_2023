#pragma once

#include <unordered_map>
#include "domain_object.h"
#include "unit_of_work.h"
#include <iostream>

typedef int (*CallbackType)(void *, int argc, char **argv, char **col_names);

class AbstractMapper
{
public:
    virtual ~AbstractMapper()
    {
    }

    virtual std::string findByIdStmt(std::string id) const = 0;

    void setDB(std::string db_file)
    {
    }

    bool isLoaded(const std::string &id) const
    {
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
        
    }


    void load(DomainObject *domainObject)
    {
        
    }
private:
};