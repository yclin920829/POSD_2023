#pragma once

#include <string>
#include <iostream>
#include <sqlite3.h>

class Painter;

class PainterMapper {
public:
    
    void add(DomainObject * Painter);

    Painter* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    static PainterMapper* instance();

    void cleanCache();

};