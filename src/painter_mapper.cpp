#include "sqlite_painter_mapper.h"
#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"

PainterMapper* PainterMapper::instance() {
    return SQLitePainterMapper::instance();
};