#include "Scanner.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <iostream> 

using namespace std;

#ifdef _WIN32
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

void Scanner::recurse(const string& path, vector<string>& files) {
    cout << path << endl;
    DIR* directory = opendir(path.c_str());
    if (!directory) return;

    struct dirent* entry;
    while ((entry = readdir(directory)) != nullptr) {
        string entryName = entry->d_name;

        if (entryName == "." || entryName == "..") continue;

        string fullEntryPath = path + PATH_SEPARATOR + entryName;

        struct stat entryStat;
        if (stat(fullEntryPath.c_str(), &entryStat) == -1) continue; // кривые файлы
        if (S_ISLNK(entryStat.st_mode)) continue; // симлинки 

        if (S_ISDIR(entryStat.st_mode)) {
            recurse(fullEntryPath, files);
        } else if (S_ISREG(entryStat.st_mode)) {
            files.push_back(fullEntryPath);
        }
    }

    closedir(directory);
}

vector<string> Scanner::scan(const string& rootPath) {
    vector<string> resultFiles;

    struct stat rootStat;
    if (stat(rootPath.c_str(), &rootStat) == -1) return resultFiles;

    if (S_ISREG(rootStat.st_mode)) {
        resultFiles.push_back(rootPath);
    } else if (S_ISDIR(rootStat.st_mode)) {
        recurse(rootPath, resultFiles);
    }

    return resultFiles;
}