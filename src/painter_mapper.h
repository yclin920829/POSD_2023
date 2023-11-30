#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"


class PainterMapper: public AbstractMapper {
public:
    Painter* find(std::string id);
    
    void add(DomainObject * Painter);

    void update(std::string id);

    void del(std::string id);

    static PainterMapper* instance();

protected:
    PainterMapper();

    static int callback(void* notUsed, int argc, char** argv, char** colNames);
    
private:
    char* _errorMessage;
    static PainterMapper* _instance;
};