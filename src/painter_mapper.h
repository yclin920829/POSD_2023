#pragma once

#include <string>
#include <sqlite3.h>

#include "abstract_mapper.h"

class Painter;

class PainterMapper: public AbstractMapper {
public:
    //TODO : class
    Painter* find(std::string id);
    
    //TODO : class
    void add(DomainObject * Painter);

    //TODO : class
    void update(std::string id);

    //TODO : del
    void del(std::string id) {};

    //TODO : class
    std::string updateStmt(DomainObject * domainObject) const override;

    //TODO : class
    std::string findByIdStmt(std::string id) const override;

    //TODO : class
    std::string addStmt(DomainObject * domainObject) const override;

    //TODO : deleteByIdStmt
    std::string deleteByIdStmt(std::string id) const override {
        return _errorMessage;
    };

    //TODO : class
    static PainterMapper* instance();

protected:
    PainterMapper();

    //TODO : class
    static int callback(void* notUsed, int argc, char** argv, char** colNames);
    
private:
    char* _errorMessage;
    static PainterMapper* _instance;
};