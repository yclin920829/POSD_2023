#include "painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;

Painter* PainterMapper::find(std::string id) {
}

// add
void PainterMapper::add(DomainObject * painter) {

}

// update
void PainterMapper::update(std::string id) {
}

// delete
void PainterMapper::del(std::string id) {
}

PainterMapper* PainterMapper::instance() {
}

PainterMapper::PainterMapper() {
}

int PainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
}