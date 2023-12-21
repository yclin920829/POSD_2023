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
#include "sqlite_drawing_mapper.h"

DrawingMapper* DrawingMapper::instance() {
    return SQLiteDrawingMapper::instance();
};
