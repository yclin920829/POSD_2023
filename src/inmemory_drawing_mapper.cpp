#include <vector>

#include "sqlite_drawing_mapper.h"
#include "inmemory_drawing_mapper.h"
#include "domain_object.h"

void InMemoryDrawingMapper::add(DomainObject * drawing) {
    drawings.push_back(drawing);
};

Drawing* InMemoryDrawingMapper::find(std::string id) {
    for(int i=0; i < drawings.size(); i++) {
        DomainObject * drawing = drawings[i];
        if (drawing->id() == id){
            return dynamic_cast<Drawing *>(drawing);
        }
    }
};

void InMemoryDrawingMapper::update(std::string id) {};

void InMemoryDrawingMapper::del(std::string id) {};

InMemoryDrawingMapper* InMemoryDrawingMapper::instance() {
   
}

void InMemoryDrawingMapper::cleanCache() {} ;
