#pragma once

#include <iostream>
#include <unordered_map>

#include "drawing.h"
#include "unit_of_work.h"
#include "domain_object.h"

typedef int (*CallbackType)(void *, int argc, char **argv, char **col_names);

class AbstractMapper {
public:
    virtual ~AbstractMapper() {}

    virtual std::string updateStmt(DomainObject *domainObject) const = 0;
    virtual std::string findByIdStmt(std::string id) const = 0;
    virtual std::string addStmt(DomainObject *domainObject) const = 0;
    virtual std::string deleteByIdStmt(std::string id) const = 0;

    void setDB(std::string db_file){
        sqlite3_open(db_file.c_str(), &_db);
    }

    bool isLoaded(const std::string &id) const {
        return _domainObjects.count(id);
    }

    void cleanCache() {
        _domainObjects.clear();
    }

protected:
    std::unordered_map<std::string, DomainObject *> _domainObjects;
    sqlite3 *_db;

    DomainObject *getDomainObject(std::string id){
        if (_domainObjects.count(id)) {
            return _domainObjects.at(id);
        }
        return nullptr;
    }

    //TODO : class 
    DomainObject * abstractFind(std::string id, CallbackType callback) {
        DomainObject * domainObject = getDomainObject(id);
        if(domainObject != nullptr) {
            return domainObject;
        }
        
        sqlite3_exec(_db, findByIdStmt(id).c_str(), callback, NULL, &_errorMessage);
        DomainObject * object = getDomainObject(id);
        if(object != nullptr) {
            UnitOfWork::instance()->registerClean(object);
        }
        return object;
   }

    //TODO : class
    void abstractAdd(DomainObject * domainObject) {
        sqlite3_exec(_db, addStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
    }

    //TODO : class
    void abstractUpdate(DomainObject *domainObject) {
        sqlite3_exec(_db, updateStmt(domainObject).c_str(), NULL, NULL, &_errorMessage);
    };

    //TODO : not sure
    void abstractDelete(std::string id) {
        sqlite3_exec(_db, deleteByIdStmt(id).c_str(), NULL, NULL, &_errorMessage);
    };

    //TODO : class
    void load(DomainObject *domainObject) {
        _domainObjects[domainObject->id()] = domainObject;
    };

private:
    char *_errorMessage;
};