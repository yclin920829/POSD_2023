#pragma once

#include <list>
#include <string>
#include <iostream>
#include <sys/stat.h>

#include "node.h"
#include "iterator.h"
#include "dfs_iterator.h"

using namespace std;

class Folder: public Node {
private:
    list<Node *> _nodes;

    class FolderIterator : public Iterator {
    public:
        FolderIterator(Folder* composite):_host(composite) {
            // cout << "constructor num: " << _host->numberOfFiles() << endl;
            _filesNumber = _host->numberOfFiles();
        };
        ~FolderIterator() {}
        void first() {
            // cout << "original num: " << _filesNumber << endl; 
            // cout << "first num: " << _host->numberOfFiles() << endl;
            if (_host->numberOfFiles() != _filesNumber) {
                // cout << "throw exception" << endl;
                throw string ("folder has been changed.");
            }
            // cout << "do first" << endl;
            _current = _host->_nodes.begin();
        };
        Node * currentItem() const {
            return *_current;
        };
        void next() {
            // cout << "original num: " << _filesNumber << endl;
            // cout << "next num: " << _host->numberOfFiles() << endl;
            if (_host->numberOfFiles() != _filesNumber) {
                // cout << "throw exception" << endl;
                throw string ("folder has been changed.");
            }
            // cout << "do next" << endl;
            _current++;
           
        };
        bool isDone() const {
            return _current == _host->_nodes.end();
        };

    private:
        int _filesNumber;
        Folder* const _host;
        std::list<Node *>::iterator _current;
    };

protected:
    void removeChild(Node * target) override {
        _nodes.remove(target);
    }

public:
    Folder(string path): Node(path) {
        struct stat sb;
        stat(this->path().c_str(), &sb);
        if (!S_ISDIR(sb.st_mode)) {
            // cout << "Not a folder." << endl;
            throw string("Not a folder.");
        }
    }

    void add(Node * node) override {
        if (node->path() != this->path() + "/" + node->name()) {
            // cout << "Incorrect path of node: " << node -> path() << endl;
            throw string("Incorrect path of node: " + node -> path());
        }
        _nodes.push_back(node);
        node->parent(this);
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
        return new FolderIterator(this);
    }

    Iterator * dfsIterator() override {
        return new DfsIterator(this);
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
        // std::cout << "folder accept to visit" << std::endl;
        visitor->visitFolder(this);
    }
};
