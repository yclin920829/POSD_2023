#pragma once

#include <string>

#include <sqlite3.h>

// #include "drawing.h"
#include "drawing.h"
#include "abstract_mapper.h"
#include "painter_mapper.h"
#include "scanner.h"
#include "builder.h"
#include "parser.h"

class DrawingMapper: public AbstractMapper {
public:
    Drawing* find(std::string id);

    void add(DomainObject * Drawing);

    void update(std::string id);

    void del(std::string id);

    std::string findByIdStmt(std::string id) const;

    static DrawingMapper* instance();

protected:
    DrawingMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);

    std::list<Shape *> convertShapes(int argc, char** argv);
    
private:
    char* _errorMessage;
    static DrawingMapper* _instance;
    Builder * _builder;
    Scanner * _scanner;
    Parser * _parser;
};