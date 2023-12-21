#pragma once

#include <string>
#include <vector>

#include <sqlite3.h>


class Drawing;
class Scanner;
class Builder;
class Parser;
// class DomainObject;

#include "domain_object.h"


class InMemoryDrawingMapper: public DrawingMapper {
public:

    void add(DomainObject * drawing) override ;

    Drawing* find(std::string id) override ;

    void update(std::string id) override ;

    void del(std::string id) override ;

    static InMemoryDrawingMapper* instance();

    void cleanCache() override ;

private:
    std::vector<DomainObject * > drawings;
};