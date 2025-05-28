#include "Aes256.h"
#include <openssl/aes.h>
#include <openssl/sha.h>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

static bool transformFile(const string& path, const string& pass, string encryptMode) {
    ifstream fin(path, ios::binary);
    if (!fin) return false;

    vector<unsigned char> buffer((istreambuf_iterator<char>(fin)), {});
    fin.close();

    if (encryptMode == "0") {
        int pad = AES_BLOCK_SIZE - (buffer.size() % AES_BLOCK_SIZE);
        buffer.insert(buffer.end(), pad, pad);
    } else {
        if (buffer.size() % AES_BLOCK_SIZE != 0) return false;
    }

    unsigned char key[32];
    SHA256(reinterpret_cast<const unsigned char*>(pass.data()), pass.size(), key);

    AES_KEY aesKey;
    if (encryptMode == "0") {
        if (AES_set_encrypt_key(key, 256, &aesKey) != 0) return false;
    } else {
        if (AES_set_decrypt_key(key, 256, &aesKey) != 0) return false;
    }

    unsigned char iv[AES_BLOCK_SIZE] = {0};
    vector<unsigned char> out(buffer.size());

    AES_cbc_encrypt(
        buffer.data(),
        out.data(),
        buffer.size(),
        &aesKey,
        iv,
        encryptMode == "0" ? AES_ENCRYPT : AES_DECRYPT
    );

    if (encryptMode == "1") {
        int pad = out.back();
        if (pad <= 0 || pad > AES_BLOCK_SIZE) return false;
        out.resize(out.size() - pad);
    }

    ofstream fout(path, ios::binary | ios::trunc);
    if (!fout) return false;
    fout.write(reinterpret_cast<char*>(out.data()), out.size());
    return true;
}

bool Aes256::encryptFile(const string& path, const string& pass) {
    return transformFile(path, pass, "0");
}

bool Aes256::decryptFile(const string& path, const string& pass) {
    return transformFile(path, pass, "1");
}
