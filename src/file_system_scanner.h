#pragma once

#include <string>
#include <dirent.h>

using std::string;

class FileSystemScanner {
public:
    FileSystemScanner() {

    };

    bool isFile() {
        const string currentPath = _path + "/" + currentNodeName();
        const char* c = currentPath.c_str(); 
        // std::cout << "path:" << c << "\n"; 
        if(lstat(c, &fileInfo) == 0){
            if (S_ISREG(fileInfo.st_mode)) {
                // std::cout << "File: " << _path << std::endl;
                return true;
            }
        }
        return false;
    };

    bool isFolder() {
        const string currentPath = _path + "/" + currentNodeName();
        const char* c = currentPath.c_str(); 
        // std::cout << "path:" << c << "\n"; 
        if(lstat(c, &fileInfo) == 0){
            if(S_ISDIR(fileInfo.st_mode)) {
                // std::cout << "Folder: " << _path << std::endl;
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


        // 開啟資料夾
        DIR *dir = opendir(folder_path);
        if (dir) {
            struct dirent *entry;
            // 遍歷資料夾中的條目
            while ((entry = readdir(dir)) != NULL) {
                if (entry->d_name[0] == '.') {
                    continue;
                }   
                // string path = string(folder_path) + "/" + entry->d_name;
                // printf("Entry: %s\n", entry->d_name);
                // printf("Path: %s\n", path.c_str());
                _pathList.push_back(entry->d_name);
            }

            // 關閉資料夾
            closedir(dir);
        } else {
            perror("無法開啟資料夾");
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
