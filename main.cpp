#include "Crypt.h"
#include <openssl/evp.h> 
#include <openssl/err.h> 
#include <iostream> 
#include <string>
#include <cstring>

using namespace std;

bool processOption(const string& option, const string& dir, const string& password) {
    Crypt& crypto = Crypt::getInstance();
    crypto.setPassword(password);

    if (option == "0") {
        crypto.encrypt(dir);
    } else if (option == "1") {
        crypto.decrypt(dir);
    } else {
        cerr << "Unknown option: " << option << endl;
        return false;
    }
    return true;
}

int main(int argc, char* argv[]) { 
    if (argc != 4) {
        cerr << "Usage: " << argv[0] << " 0(enc)|1(dec) /path/to/your/folder/ password" << endl; 
        return 1; 
    }

    string option = argv[1];
    string targetDir = argv[2];
    string password = argv[3];

    OpenSSL_add_all_algorithms();
    ERR_load_crypto_strings();

    bool success = processOption(option, targetDir, password);

    EVP_cleanup();
    ERR_free_strings();

    return success ? 0 : 1;
}