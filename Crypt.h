#ifndef CRYPT_H 
#define CRYPT_H

#include <string>

using namespace std;

class Crypt { 
public: 
    static Crypt& getInstance(); 
    void setPassword(const string& pass); 
    void encrypt(const string& path); 
    void decrypt(const string& path); 
private: 
    Crypt() = default; 
    Crypt(const Crypt&) = delete; 
    Crypt& operator=(const Crypt&) = delete; 
    void createFile(const string& filePath, string encrypt); 
    
    string pass; 
};

#endif // CRYPT_H