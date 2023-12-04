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
    //TODO : class
    void add(DomainObject * Drawing);

    // update
    //TODO : class
    void update(std::string id);

    // delete
    //TODO : class
    void del(std::string id);

    //TODO : class
    std::string updateStmt(DomainObject *domainObject) const override;

    std::string findByIdStmt(std::string id) const override;

    //TODO : class
    std::string addStmt(DomainObject *domainObject) const override;

    //TODO : class
    std::string deleteByIdStmt(std::string id) const override;

    static DrawingMapper *instance();

protected:
    DrawingMapper();

    //TODO : class
    static int callback(void *notUsed, int argc, char **argv, char **colNames);

    std::list<Shape *> convertShapes(int argc, char **argv);

private:
    char *_errorMessage;
    static DrawingMapper *_instance;
    Builder *_builder;
    Scanner *_scanner;
    Parser *_parser;
};