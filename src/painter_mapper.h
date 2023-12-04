#pragma once

#include <string>
#include <sqlite3.h>

#include "abstract_mapper.h"

class Painter;

class PainterMapper: public AbstractMapper {
public:
    //TODO
    Painter* find(std::string id) {
        return nullptr;
    };
    
    //TODO
    void add(DomainObject * Painter) {};

    //TODO
    void update(std::string id) {};

    //TODO
    void del(std::string id) {};

    //TODO
    std::string updateStmt(DomainObject * domainObject) const override {
        return "";
    }

    //TODO
    std::string findByIdStmt(std::string id) const override {
        return "";
    };

    //TODO
    std::string addStmt(DomainObject * domainObject) const override {
        return "";
    };

    //TODO
    std::string deleteByIdStmt(std::string id) const override {
        return _errorMessage;
    };

    //TODO
    static PainterMapper* instance() {
        return new PainterMapper();
    }

protected:
    PainterMapper();

    //TODO
    static int callback(void* notUsed, int argc, char** argv, char** colNames) {
        return 0;
    };
    
private:
    char* _errorMessage;
    static PainterMapper* _instance;
};