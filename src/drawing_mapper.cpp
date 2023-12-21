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

virtual Drawing* DrawingMapper::find(std::string id) = 0;

// add
virtual void DrawingMapper::add(DomainObject * drawing) = 0;

// update
virtual void DrawingMapper::update(std::string id) = 0;

// delete
virtual void DrawingMapper::del(std::string id) = 0;

virtual DrawingMapper* DrawingMapper::instance() = 0;

virtual void DrawingMapper::cleanCache() = 0;