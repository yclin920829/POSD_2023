#pragma once 

#include <list>
#include <queue>
#include <string>
#include <iostream>
#include <sys/stat.h>

#include "node.h"
#include "order_by.h"
#include "iterator.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;
    int _operationCount = 0;

protected:
    void removeChild(Node * target) override {
        _nodes.remove(target);
        _operationCount++;
    }

public:
    Folder(string path): Node(path) {
        struct stat fileInfo;
        const char *c = path.c_str();
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode))
                return;
        }
        throw "No Folder exists";
    }

    void add(Node * node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
        _operationCount++;
    }

    Node * getChildByName(const char * name) const override {
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            if ((*it)->name() == name) {
                return *it;
            }
        }

        return nullptr;
    }

    int numberOfFiles() const override {
        int num = 0;
        if (_nodes.size() == 0) {
            return 0;
        }
        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            num += (*it)->numberOfFiles();
        }
        return num;
    }

    Iterator * createIterator() override {
        return new FolderIterator(this, _operationCount);
    }

    Iterator * createIterator(OrderBy orderby) override {
        if (orderby == OrderBy::Normal) {
            // std::cout << "Normal in createIterator" << std::endl;
            return new FolderIterator(this, _operationCount);
        } else if (orderby == OrderBy::Name) {
            // std::cout << "Name in createIterator" << std::endl;
            return new OrderByNameIterator(this, _operationCount);
        } else if (orderby == OrderBy::NameWithFolderFirst) {
            // std::cout << "NameWithFolderFirst in createIterator" << std::endl;
            return new OrderByNameWithFolderFirstIterator(this, _operationCount);
        } else if (orderby == OrderBy::Kind) {
            // std::cout << "Kind in createIterator" << std::endl;
            return new OrderByKindIterator(this, _operationCount);
        } 
        return new NullIterator();
    }

    Node * find(string path) override {
        if (this->path() == path) {
            return this;
        }

        size_t index = path.find(this->path());

        if (string::npos == index) {
            return nullptr;
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            Node * result = (*it)->find(path);
            if (result) {
                return result;
            }
        }
        return nullptr;
    }

    std::list<string> findByName(string name) override {
        std::list<string> pathList;
        if (this->name() == name) {
            pathList.push_back(this->path());
        }

        for (auto it = _nodes.begin(); it != _nodes.end(); ++it) {
            std::list<string> paths = (*it)->findByName(name);
            for (auto i = paths.begin(); i != paths.end(); i++)
            {
                pathList.push_back(*i);  
            }
        }

        return pathList;
    }

    void remove(string path) override {
        Node * target = find(path);
        if (target) {
            target->parent()->removeChild(target);
        }
    }

    void accept(Visitor * visitor) override {
        visitor->visitFolder(this);
    }

    int numberOfChildren() const {
        return _nodes.size();
    }

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {}

        ~FolderIterator() {}

        void first() {
            checkAvailable();
            _current = _host->_nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _host->_nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameIterator: public Iterator {
    public:
        OrderByNameIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            // std::cout << "OrderByNameIterator" << std::endl;
            Iterator * it = _host->createIterator();
            for (it->first(); !it->isDone(); it->next()) {
                _nodes.push_back(it->currentItem());
            }
            _nodes.sort([](Node * a, Node * b) {
                return a->name() < b->name();
            });
        }

         ~OrderByNameIterator() {}

        void first() {
            checkAvailable();
            _current = _nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        std::list<Node *> _nodes;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByNameWithFolderFirstIterator: public Iterator {
    public:
        OrderByNameWithFolderFirstIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            // std::cout << "OrderByNameWithFolderFirstIterator" << std::endl;
            Iterator * it = _host->createIterator();
            for (it->first(); !it->isDone(); it->next()) {
                struct stat fileInfo;
                string path = it->currentItem()->path(); 
                const char* c = path.c_str(); 
                // std::cout << "path:" << c << "\n"; 
                if(lstat(c, &fileInfo) == 0){
                    if(S_ISDIR(fileInfo.st_mode)) {
                        // std::cout << "Folder: " << it->currentItem()->name() << std::endl;
                        _folders.push_back(it->currentItem());
                    }else if (S_ISREG(fileInfo.st_mode)) {
                        // std::cout << "File: " << it->currentItem()->name() << std::endl;
                        files.push_back(it->currentItem());
                    }
                }
            }
            _folders.sort([](Node * a, Node * b) {
                return a->name() < b->name();
            });

            files.sort([](Node * a, Node * b) {
                return a->name() < b->name();
            });

            for (auto it = _folders.begin(); it != _folders.end(); ++it) {
                _nodes.push_back(*it);
            }

            for (auto it = files.begin(); it != files.end(); ++it) {
                _nodes.push_back(*it);
            }
        }

         ~OrderByNameWithFolderFirstIterator() {}

        void first() {
            checkAvailable();
            _current = _nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        std::list<Node *> _folders;
        std::list<Node *> files;
        std::list<Node *> _nodes;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };

    class OrderByKindIterator: public Iterator {
    public:
        OrderByKindIterator(Folder* composite, int operationCount) : _host(composite), _operationCount(operationCount)  {
            // std::cout << "OrderByNameWithFolderFirstIterator" << std::endl;
            Iterator * it = _host->createIterator();
            for (it->first(); !it->isDone(); it->next()) {
                struct stat fileInfo;
                string path = it->currentItem()->path(); 
                const char* c = path.c_str(); 
                // std::cout << "path:" << c << "\n"; 
                if(lstat(c, &fileInfo) == 0){
                    if(S_ISDIR(fileInfo.st_mode)) {
                        string type = "folder";
                        string name = it->currentItem()->name();
                        string newName = type + "." + name;
                        // std::cout << "type: " << type << std::endl;
                        // std::cout << "name: " << name<< std::endl;
                        // std::cout << "new name: " << newName << std::endl;

                        _names.push_back(newName);

                    }else if (S_ISREG(fileInfo.st_mode)) {
                        if (it->currentItem()->name().find(".") != std::string::npos) {
                            string type = it->currentItem()->name().substr(it->currentItem()->name().find(".") + 1);
                            string name = it->currentItem()->name().substr(0, it->currentItem()->name().find("."));
                            string newName = type + "." + name;
                            // std::cout << "type: " << type << std::endl;
                            // std::cout << "name: " << name << std::endl;
                            // std::cout << "new name: " << newName << std::endl;

                            _names.push_back(newName);


                        }else {
                            string type = "file";
                            string name = it->currentItem()->name();
                            string newName = type + "." + name;
                            // std::cout << "type: " << type << std::endl;
                            // std::cout << "name: " << name<< std::endl;
                            // std::cout << "new name: " << newName << std::endl;

                            _names.push_back(newName);

                        }
                    }
                }
                // std::cout << std::endl;
            }

            _names.sort();

            // for (auto it = _names.begin(); it != _names.end(); ++it) {
            //     std::cout << *it << std::endl;
            // }

            // std::cout << std::endl;

            for (auto it = _names.begin(); it != _names.end(); ++it) {
                string type = it->substr(0, it->find("."));
                string name = it->substr(it->find(".") + 1);

                if (type != "file" && type != "folder") {
                    name = name + "." + type;
                }

                // std::list<string> path = _host->findByName(name);
                Node *  node = _host->getChildByName(name.c_str());

                // std::cout << "type: " << type << std::endl;
                // std::cout << "name: " << name << std::endl;
                // std::cout << "path: " << node->path() << std::endl;

                _nodes.push_back(node);

                // std::cout << std::endl;
            }

        }

        ~OrderByKindIterator() {}

        void first() {
            checkAvailable();
            _current = _nodes.begin();
        }

        Node * currentItem() const {
            return *_current;
        }

        void next() {
            checkAvailable();
            _current++;
        }

        bool isDone() const {
            return _current == _nodes.end();
        }

    private:
        Folder* const _host;
        std::list<Node *>::iterator _current;
        std::list<string> _kinds;
        std::list<Node *> _nodes;
        std::list<string> _names;
        int _operationCount;

        void checkAvailable() const {
            if(_host->_operationCount != _operationCount) {
                throw "Iterator Not Avaliable";
            }
        }
    };
};
