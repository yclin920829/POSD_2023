#include "drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"

DrawingMapper* DrawingMapper::_instance = nullptr;

DrawingMapper* DrawingMapper::instance() = 0;

Drawing* DrawingMapper::find(std::string id) = 0;

// add
void DrawingMapper::add(DomainObject * drawing) = 0;

// update
void DrawingMapper::update(std::string id) = 0;

// delete
void DrawingMapper::del(std::string id) = 0;

std::string DrawingMapper::updateStmt(DomainObject * domainObject) const = 0;

std::string DrawingMapper::findByIdStmt(std::string id) const = 0;

std::string DrawingMapper::addStmt(DomainObject * domainObject) const = 0;

std::string DrawingMapper::deleteByIdStmt(std::string id) const = 0;

DrawingMapper* DrawingMapper::instance() = 0;

// DrawingMapper::DrawingMapper() = 0;

int DrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) = 0;

std::list<Shape *> DrawingMapper::convertShapes(char * shape_string) = 0;

void DrawingMapper::cleanCache() = 0;