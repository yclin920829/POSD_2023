#include "unit_of_work.h"
#include "drawing_mapper.h"
#include "painter_mapper.h"
#include "domain_object.h"
#include <list>
#include <iostream>

UnitOfWork * UnitOfWork::_instance = nullptr;

UnitOfWork* UnitOfWork::instance() {
    if(_instance == nullptr) {
        _instance = new UnitOfWork();
    }
    return _instance;
}

void UnitOfWork::registerNew(DomainObject * domainObject) {
    _new[domainObject->id()] = domainObject;
}

void UnitOfWork::registerClean(DomainObject * domainObject) {
    _clean[domainObject->id()] = domainObject;
}

void UnitOfWork::registerDirty(DomainObject * domainObject) {
    _dirty[domainObject->id()] = domainObject;
    _clean.erase(domainObject->id());
}

// TODO : not sure
void UnitOfWork::registerDeleted(DomainObject * domainObject) {
    _deleted[domainObject->id()] = domainObject;
    _new.erase(domainObject->id());
};

bool UnitOfWork::inNew(std::string id) const {
    return _new.count(id);
}

bool UnitOfWork::inClean(std::string id) const {
    return _clean.count(id);
}

bool UnitOfWork::inDirty(std::string id) const {
    return _dirty.count(id);
}

// TODO : not sure
bool UnitOfWork::inDeleted(std::string id) const {
    return _deleted.count(id);
}

void UnitOfWork::commit() {
    for(auto dirty : _dirty) {
        DrawingMapper::instance()->update(dirty.first);
        registerClean(dirty.second);
    }
    _dirty.clear();
    for(auto newObj : _new) {
        PainterMapper::instance()->add(newObj.second);
        registerClean(newObj.second);
    }
    _new.clear();
}

UnitOfWork::UnitOfWork() {}