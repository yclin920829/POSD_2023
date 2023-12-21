#pragma once

#include <string>

#include <sqlite3.h>


class Drawing;
class Scanner;
class Builder;
class Parser;


class DrawingMapper {
public:

    void add(DomainObject * Drawing);

    Drawing* find(std::string id);

    void update(std::string id);

    void del(std::string id);

    static DrawingMapper* instance();

    void cleanCache();
};