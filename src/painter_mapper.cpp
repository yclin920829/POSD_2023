#include "painter_mapper.h"

#include <string>
#include <iostream>
#include <sqlite3.h>

#include "painter.h"
#include "abstract_mapper.h"

PainterMapper* PainterMapper::_instance = nullptr;

PainterMapper::PainterMapper() {}

Painter* PainterMapper::find(std::string id) {
    return static_cast<Painter*>(abstractFind(id, PainterMapper::callback));
}

void PainterMapper::add(DomainObject * domainObject) {
    abstractAdd(domainObject);
    load(domainObject);
}

void PainterMapper::update(std::string id) {
    abstractUpdate(getDomainObject(id));
    load(getDomainObject(id));
}

//TODO : not sure
void PainterMapper::del(std::string id) {
    if(!UnitOfWork::instance()->inDeleted(id)){
        if(!isLoaded(id)) {
            // std::cout << "it is not in _domainObjects" << std::endl;
            DomainObject * object = new DomainObject(id);
            // std::cout << "painter mappeer: " << object->id() << std::endl;
            UnitOfWork::instance()->registerDeleted(object);
            return;
        }
    }
    abstractDelete(id);
    UnitOfWork::instance()->registerDeleted(getDomainObject(id));
    _domainObjects.erase(id);
    // if(UnitOfWork::instance()->inDeleted(id)) {
    //     abstractDelete(id);
    //     _domainObjects.erase(id);
    // }else {
    //     if(isLoaded(id)) {
    //         UnitOfWork::instance()->registerDeleted(getDomainObject(id));
    //     }else {
    //         // std::cout << "it is not in _domainObjects" << std::endl;
    //         DomainObject * object = new DomainObject(id);
    //         // std::cout << "painter mappeer: " << object->id() << std::endl;
    //         UnitOfWork::instance()->registerDeleted(object);
    //     }
    // }
}

PainterMapper* PainterMapper::instance() {
    if (_instance == nullptr) {
        _instance = new PainterMapper();
    }
    return _instance;
}

std::string PainterMapper::findByIdStmt(std::string id) const {
    std::string stmt = "SELECT * FROM painter WHERE ID='" + id + "'";
    return stmt;
}

std::string PainterMapper::addStmt(DomainObject * domainObject) const {
    Painter* painter = static_cast<Painter*>(domainObject);
    std::string stmt = "INSERT INTO painter(ID, Name) values ('" + painter->id() + "', '" + painter->name() + "')";
    return stmt;
}

//TODO : not sure
std::string PainterMapper::deleteByIdStmt(std::string id) const {
    std::string stmt = "DELETE FROM painter WHERE ID='" + id + "'";
    return stmt;
}

std::string PainterMapper::updateStmt(DomainObject* domainObject) const {
    Painter* painter = static_cast<Painter*>(domainObject);
    std::string stmt = "UPDATE painter SET Name='" + painter->name() + "' WHERE ID='" + painter->id() + "'";
    return stmt;
}

int PainterMapper::callback(void* notUsed, int argc, char** argv, char** colNames) {
    // std::cout << "painter mapper callback" << std::endl;
    Painter* painter = new Painter(argv[0], argv[1]);
    PainterMapper::instance()->load(painter);
    UnitOfWork::instance()->commit();
    return 0;
}