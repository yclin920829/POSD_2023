#pragma once

#include <string>

#include <sqlite3.h>

class InMemoryDrawingMapper: public DrawingMapper {
public:

    SQLiteDrawingMapper* instance();
};