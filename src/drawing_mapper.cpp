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

Drawing* DrawingMapper::find(std::string id) {
    return static_cast<Drawing *>(abstractFind(id, DrawingMapper::callback));
}

// add
void DrawingMapper::add(DomainObject * drawing) {
    abstractAdd(drawing);
}

// update
void DrawingMapper::update(std::string id) {   
}

// delete
void DrawingMapper::del(std::string id) {
}

std::string DrawingMapper::updateStmt(DomainObject * domainObject) const {
}

std::string DrawingMapper::findByIdStmt(std::string id) const {
    return "SELECT * FROM drawing WHERE ID = '" + id + "'";
}

std::string DrawingMapper::addStmt(DomainObject * domainObject) const {
}

std::string DrawingMapper::deleteByIdStmt(std::string id) const {
}


DrawingMapper* DrawingMapper::instance() {
}

DrawingMapper::DrawingMapper() {
    _builder = new Builder();
    _scanner = new Scanner();
    _parser = new Parser(_scanner, _builder);
}

int DrawingMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
}

std::list<Shape *> DrawingMapper::convertShapes(int argc, char** argv) {
}