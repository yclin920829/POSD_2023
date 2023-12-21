#include "sqlit_drawing_mapper.h"

#include <sqlite3.h>
#include <string>
#include <map>
#include "drawing.h"
#include "triangle.h"
#include "parser.h"
#include "scanner.h"
#include "builder.h"
#include "domain_object.h"

DrawingMapper* SQLiteDrawingMapper::_instance = nullptr;

virtual Drawing* SQLiteDrawingMapper::find(std::string id) = 0

// add
virtual void SQLiteDrawingMapper::add(DomainObject * drawing) = 0;

// update
virtual void SQLiteDrawingMapper::update(std::string id) = 0;

// delete
virtual void SQLiteDrawingMapper::del(std::string id) = 0;

virtual std::string SQLiteDrawingMapper::updateStmt(DomainObject * domainObject) const = 0;

virtual std::string SQLiteDrawingMapper::findByIdStmt(std::string id) const = 0;

virtual std::string SQLiteDrawingMapper::addStmt(DomainObject * domainObject) const = 0;

virtual std::string SQLiteDrawingMapper::deleteByIdStmt(std::string id) = 0;

virtual DrawingMapper* SQLiteDrawingMapper::instance() = 0;

virtual SQLiteDrawingMapper::DrawingMapper(): SQLiteAbstractMapper("resource/drawing.db") = 0;

virtual int SQLiteDrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) = 0;

virtual std::list<Shape *> SQLiteDrawingMapper::convertShapes(char * shape_string) = 0;

virtual void SQLiteDrawingMapper::cleanCache() = 0;