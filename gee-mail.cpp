#include <boost/algorithm/string.hpp>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include "cryptogm/sha256.h"
#include "cryptogm/cryptogm.h"

using namespace std;
using namespace boost;

int main (int argc, char* argv[]) {
  string *cipherdata = new string[3];
  string recovered;
  string test = sha256("0" + sha256("hundreds"));
  string ans = "A8677DF7AAC4E90428D7226C5D28971273A5DDDB2F0338C963ACC521A6232934";
  string test2 = secure_hash("hundreds","",1);

  cout << "test    : " << test << endl;
  cout << "ans     : " << ans << endl;
  cout << "test2   : " << test2 << endl;

  if (iequals(test, test2)) {
    cout << "hash matches" << endl;      
  }

  string plaintext = "this is a test message to see stuff";
  string passphrase = secure_hash("This is a test passphrase that is really really super long to see what happens if I go out of bounds", "┌∩┐(◣_◢)┌∩┐", 1000);

  cout << "pt: " << plaintext << endl;
  cipherdata = encrypt(plaintext, passphrase);
  string ct = cipherdata[2];
  string kt = cipherdata[1];
  string it = cipherdata[0];

  cout << "ct: " << ct << endl;
  cout << "kt: " << kt << endl;
  cout << "it: " << it << endl;
  recovered = decrypt(ct, kt, it);

  cout << "Decrypted Text: " << recovered << endl;
  return 0;
  
}
