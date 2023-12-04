#pragma once

#include <string>
#include <sqlite3.h>

#include "abstract_mapper.h"

class DomainObject;
class Drawing;
class Scanner;
class Parser;
class Builder;

class DrawingMapper : public AbstractMapper {
public:
    Drawing *find(std::string id);

    // add
    //TODO
    void add(DomainObject *Drawing) {};

    // update
    //TODO
    void update(std::string id) {};

    // delete
    //TODO
    void del(std::string id) {};

    //TODO
    std::string updateStmt(DomainObject *domainObject) const override {
        return "";
    }

    std::string findByIdStmt(std::string id) const override;

    //TODO
    std::string addStmt(DomainObject *domainObject) const override {
        return "";
    }

    //TODO
    std::string deleteByIdStmt(std::string id) const override {
        return _errorMessage;
    }

    static DrawingMapper *instance();

protected:
    DrawingMapper();

    //TODO
    static int callback(void *notUsed, int argc, char **argv, char **colNames) {
        return 0;
    }

    std::list<Shape *> convertShapes(int argc, char **argv);

private:
    char *_errorMessage;
    static DrawingMapper *_instance;
    Builder *_builder;
    Scanner *_scanner;
    Parser *_parser;
};