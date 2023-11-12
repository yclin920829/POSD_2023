#pragma once

#include <list>
#include <dirent.h>
#include <sys/stat.h>

class FileSystemScanner {
public:
    FileSystemScanner() {};

    bool isFile() {
        const string currentPath = _path + "/" + currentNodeName();
        const char* c = currentPath.c_str(); 
        if(lstat(c, &fileInfo) == 0){
            if (S_ISREG(fileInfo.st_mode)) {
                return true;
            }
        }
        return false;
    };

    bool isFolder() {
        const string currentPath = _path + "/" + currentNodeName();
        const char* c = currentPath.c_str(); 
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode)) {
                return true;
            }
        }
        return false;
    };

    bool isDone() {
        return it == _pathList.end();
    };

    void setPath(string path) {
        _path = path;
        const char *folder_path = _path.c_str();

        DIR *dir = opendir(folder_path);
        if (dir) {
            struct dirent *entry;
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_name[0] == '.') {
                    continue;
                }   
                _pathList.push_back(entry->d_name);
            }
            closedir(dir);
        } else {
            perror("Unable to open folder");
        }
        it = _pathList.begin();
    };

    string currentNodeName() {
        return *it;
    };

    void nextNode() {
        it++;
    };

private:
    struct stat fileInfo;
    string _path;
    std::list<string> _pathList;
    std::list<string>::iterator it;
};
