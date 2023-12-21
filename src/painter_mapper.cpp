#include "sqlite_painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"

Painter* PainterMapper::find(std::string id) = 0;

// add
void PainterMapper::add(DomainObject * painter) = 0;

// update
void PainterMapper::update(std::string id) = 0;

// delete
void PainterMapper::del(std::string id) = 0;

PainterMapper* PainterMapper::instance()  = 0;

void PainterMapper::cleanCache() = 0;