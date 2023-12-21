#pragma once

#include <string>

#include <sqlite3.h>


class Drawing;
class Scanner;
class Builder;
class Parser;
class DomainObject;


class DrawingMapper {
public:

    virtual void add(DomainObject * Drawing) = 0;

    virtual Drawing* find(std::string id) = 0;

    virtual void update(std::string id) = 0;

    virtual void del(std::string id) = 0;

    static DrawingMapper* instance();

    virtual void cleanCache() = 0;
};