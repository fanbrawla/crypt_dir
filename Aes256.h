#ifndef AES256_H
#define AES256_H
#include <string>

using namespace std;

class Aes256 {
public:
    static bool encryptFile(const string& in, const string& pass);
    static bool decryptFile(const string& in, const string& pass);
};
#endif 