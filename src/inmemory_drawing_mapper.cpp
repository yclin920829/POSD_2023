#include "sqlite_drawing_mapper.h"
#include "inmemory_drawing_mapper.h"

SQLiteDrawingMapper* InMemoryDrawingMapper::instance() {
    if(_instance == nullptr) {
        _instance = new SQLiteDrawingMapper();
    }
    return _instance;
}
