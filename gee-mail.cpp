#include "sha256/sha256.h"
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
//#include <boost/algorithm/string.hpp>

using namespace std;

string secure_hash(string secret, string salt, int  stretch) {
  int i = 0;
  string hash;// = "0";
  string psalt = sha256(secret+salt);

  cout << "psalt  : " << psalt << endl;
  for (i = 0; i < stretch; i++) {
    hash = sha256(hash+psalt);
  }
  return hash;
}

int main () {

  string test = sha256("hundreds");
  string ans = "A8677DF7AAC4E90428D7226C5D28971273A5DDDB2F0338C963ACC521A6232934";
  string test2 = secure_hash("hundreds","",1);
  
  cout << "hundreds: " << test << endl;
  cout << "ans     : " << ans << endl;
  cout << "test2   : " << test2 << endl;
  return 0;
}
