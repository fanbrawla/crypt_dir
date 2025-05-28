#include "Crypt.h" 
#include "Aes256.h" 
#include "Scanner.h"
#include <iostream> 
#include <cstdio>

using namespace std;

Crypt& Crypt::getInstance() { 
    static Crypt instance; 
    return instance; 
}

void Crypt::setPassword(const string& password) { 
    pass = password; 
}

void Crypt::encrypt(const std::string& path) {
    std::vector<std::string> files = Scanner::scan(path);
    for (const std::string& file : files) {
        createFile(file, "0");
    }
}

void Crypt::decrypt(const string& path) { 
    std::vector<std::string> files = Scanner::scan(path);
    for (const std::string& file : files) {
        createFile(file, "1");
    }
}

void Crypt::createFile(const string& path, string opt) { 
    bool success; 
    
    if (opt == "0") { 
        success = Aes256::encryptFile(path, pass);
    } 
    else if (opt == "1") { 
        success = Aes256::decryptFile(path, pass); 
    } 
}
