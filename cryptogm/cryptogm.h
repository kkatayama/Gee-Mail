#ifndef CRYPTOGM_H
#define CRYPTOGM_H

std::string secure_hash(std::string secret, std::string salt, int stretch);
std::string* encrypt(std::string plaintext, std::string passphrase);
std::string decrypt(std::string ciphertext, std::string key, std::string iv);

#endif
