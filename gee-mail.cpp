#include <boost/algorithm/string.hpp>
#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include "aes.h"
#include "hex.h"
#include "modes.h"
#include "osrng.h"
#include "filters.h"
#include "cryptlib.h"
#include "sha256/sha256.h"

using namespace std;
using namespace boost;
using namespace CryptoPP;

string secure_hash(string secret, string salt, int  stretch) {
  int i = 0;
  string hash = "0";
  string psalt = sha256(secret + salt);

  cout << "psalt  : " << psalt << endl;
  for (i = 0; i < stretch; i++) {
    hash = sha256(hash + psalt);
      
  }
  return hash;
  
}

string decrypt(string ct, string kt, string it) {
  byte iv[AES::BLOCKSIZE] = {};
  // this decoder would transform our std::string into raw hex:
  HexDecoder decoder;
  decoder.Put((byte*)it.data(), it.size());
  decoder.MessageEnd();
  decoder.Get(iv, sizeof(iv));

  string cipher_raw;
  {
    HexDecoder decoder;
    decoder.Put((byte*)ct.data(), ct.size());
    decoder.MessageEnd();

    long long size = decoder.MaxRetrievable();
    cipher_raw.resize(size);
    decoder.Get((byte*)cipher_raw.data(), cipher_raw.size());
  }

  byte key[CryptoPP::AES::DEFAULT_KEYLENGTH];
  {
    HexDecoder decoder;
    decoder.Put((byte*)kt.data(), kt.size());
    decoder.MessageEnd();
    decoder.Get(key, sizeof(key));   
  }

  string decrypted_text;
  try {
    CFB_Mode< AES >::Decryption d;
    d.SetKeyWithIV(key, sizeof(key), iv);

    StringSource ss(cipher_raw, true, new StreamTransformationFilter(d, new StringSink(decrypted_text)));
      
  }
  catch( Exception& e ) {
    std::cerr << e.what() << std::endl;
    exit(1);
  }

  return decrypted_text;
}

int main (int argc, char* argv[]) {
  AutoSeededRandomPool prng;

  string test = sha256("0" + sha256("hundreds"));
  string ans = "A8677DF7AAC4E90428D7226C5D28971273A5DDDB2F0338C963ACC521A6232934";
  string test2 = secure_hash("hundreds","",1);

  cout << "test    : " << test << endl;
  cout << "ans     : " << ans << endl;
  cout << "test2   : " << test2 << endl;

  if (iequals(test, test2)) {
    cout << "hash matches" << endl;
      
  }

  string plaintext = "this is a test";
  string cipher;
  string encoded;
  string recovered;

  /*********************************/
  /* AES KEY AND IV INITIALIZATION */
  /*********************************/
  byte key[ AES::DEFAULT_KEYLENGTH ];
  prng.GenerateBlock(key, sizeof(key));

  byte iv[ AES::BLOCKSIZE ];
  prng.GenerateBlock(iv, sizeof(iv));

  // Pretty print key
  encoded.clear();
  StringSource(key, sizeof(key), true, new HexEncoder(new StringSink(encoded)));
  cout << "key: " << encoded << endl;
  string kt = encoded;

  // Pretty print iv
  encoded.clear();
  StringSource(iv, sizeof(iv), true, new HexEncoder(new StringSink(encoded)));
  cout << "iv: " << encoded << endl;
  string it = encoded;

  /*********************************/
  /*    AES CFB-MODE ENCRYPTION    */
  /*********************************/
  try {
    cout << "plain text: " << plaintext << endl;

    CFB_Mode< AES >::Encryption e;
    e.SetKeyWithIV(key, sizeof(key), iv);
    StringSource(plaintext, true, new StreamTransformationFilter(e, new StringSink(cipher)));
  } catch(const Exception& e) {
    cerr << e.what() << endl;
    exit(1);      
  }

  encoded.clear();
  StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
  cout << "cipher text: " << encoded << endl;
  string ct = encoded;
  
  /*********************************/
  /*    AES CFB-MODE DECRYPTION    */
  /*********************************/
  recovered = decrypt(ct, kt, it);

  cout << "Decrypted Text: " << recovered << endl;
  return 0;
  
}
