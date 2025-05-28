#ifndef SCANNER_H 
#define SCANNER_H
#include <string> 
#include <vector>

using namespace std;

class Scanner { 
public: 
    static vector<string> scan(const string& path); 
private: 
    static void recurse(const string& path, vector<string>& files); 
};

#endif // SCANNER_H