#pragma once

#include <string>

#include <sqlite3.h>


class Drawing;
class Scanner;
class Builder;
class Parser;


class DrawingMapper {
public:

    // ~DrawingMapper();
    
    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    static DrawingMapper* instance();

    void cleanCache();

// protected:
//     DrawingMapper();

//     static int callback(void* notUsed, int argc, char** argv, char** colNames);

//     std::list<Shape *> convertShapes(char * shape_string);

//     std::string addStmt(DomainObject * domainObject) const;
//     std::string findByIdStmt(std::string id) const;
//     std::string updateStmt(DomainObject * domainObject) const;
//     std::string deleteByIdStmt(std::string id) const;

// private:
//     static DrawingMapper* _instance;
//     Parser * _parser;
};