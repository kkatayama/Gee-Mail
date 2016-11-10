#include <iostream>
#include "aes.h"
#include "hex.h"
#include "modes.h"
#include "osrng.h"
#include "sha256.h"
#include "filters.h"
#include "cryptogm.h"

using namespace std;
using namespace CryptoPP;

string secure_hash(string secret, string salt, int  stretch) {
  int i = 0;
  string hash = "0";
  string psalt = sha256(secret + salt);

  // cout << "psalt  : " << psalt << endl;
  for (i = 0; i < stretch; i++) {
    hash = sha256(hash + psalt);
  }
  return hash;
}

string* encrypt(string plaintext, string passphrase) {
  AutoSeededRandomPool prng;
  string *cdata = new string[3];
  string cipher;
  string encoded;
  string recovered;

  /*********************************/
  /* AES KEY AND IV INITIALIZATION */
  /*********************************/
  byte key[ AES::MAX_KEYLENGTH ];
  //  prng.GenerateBlock(key, sizeof(key));
  memcpy(key, passphrase.c_str(), AES::MAX_KEYLENGTH);

  byte iv[ AES::BLOCKSIZE ];
  prng.GenerateBlock(iv, sizeof(iv));

  // Pretty print key
  encoded.clear();
  StringSource(key, sizeof(key), true, new HexEncoder(new StringSink(encoded)));
  // cout << "key: " << encoded << endl;
  string key_str = encoded;
  // cout << "key raw: " << sizeof(key) << endl;

  // Pretty print iv
  encoded.clear();
  StringSource(iv, sizeof(iv), true, new HexEncoder(new StringSink(encoded)));
  // cout << "iv: " << encoded << endl;
  string iv_str = encoded;

  /*********************************/
  /*    AES CFB-MODE ENCRYPTION    */
  /*********************************/
  try {
    // cout << "plain text: " << plaintext << endl;

    CFB_Mode< AES >::Encryption e;
    e.SetKeyWithIV(key, sizeof(key), iv);
    StringSource(plaintext, true, new StreamTransformationFilter(e, new StringSink(cipher)));
      
  } catch(const Exception& e) {
    cerr << e.what() << endl;
    exit(1);
  }
  encoded.clear();
  StringSource(cipher, true, new HexEncoder(new StringSink(encoded)));
  // cout << "cipher text: " << encoded << endl;
  string ciphertext = encoded;

  // cout << "ct: " << ciphertext << endl;
  cdata[0] = iv_str;
  cdata[1] = key_str;
  cdata[2] = ciphertext;
  return cdata;
}

string decrypt(string ciphertext, string key_str, string iv_str) {
  byte iv[ AES::BLOCKSIZE ] = {};
  // this decoder would transform our std::string into raw hex:
  HexDecoder decoder;
  decoder.Put((byte*)iv_str.data(), iv_str.size());
  decoder.MessageEnd();
  decoder.Get(iv, sizeof(iv));

  /*********************************/
  /*  CONVERT BYTE DATA TO STRING  */
  /*********************************/
  string cipher_raw;
  {
    HexDecoder decoder;
    decoder.Put((byte*)ciphertext.data(), ciphertext.size());
    decoder.MessageEnd();

    long long size = decoder.MaxRetrievable();
    cipher_raw.resize(size);
    decoder.Get((byte*)cipher_raw.data(), cipher_raw.size());
  }

  byte key[ AES::MAX_KEYLENGTH] ;
  {
    HexDecoder decoder;
    decoder.Put((byte*)key_str.data(), key_str.size());
    decoder.MessageEnd();
    decoder.Get(key, sizeof(key));
  }
  // cout << "key raw: " << sizeof(key) << endl;
  /*********************************/
  /*    AES CFB-MODE DECRYPTION    */
  /*********************************/
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
