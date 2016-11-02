#include <boost/algorithm/string.hpp>
// #include <sqlite3.h> 
#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include "cryptogm/sha256.h"
#include "cryptogm/cryptogm.h"
#include "sqlite3pp/sqlite3pp.h"

using namespace std;
using namespace boost;
using namespace sqlite3pp;

int main (int argc, char* argv[]) {
  string *cipherdata = new string[3];
  string recovered;

   cout << "Content-type:text/html\r\n\r\n";
   cout << "<html>\n";
   cout << "<head>\n";
   cout << "<title>Hello World - First CGI Program</title>\n";
   cout << "</head>\n";
   cout << "<body>\n";

  // TEST SHA-256
  string test = sha256("0" + sha256("hundreds"));
  string ans = "A8677DF7AAC4E90428D7226C5D28971273A5DDDB2F0338C963ACC521A6232934";
  string test2 = secure_hash("hundreds","",1);
  
  cout << "test    : " << test << endl;
  cout << "ans     : " << ans << endl;
  cout << "test2   : " << test2 << endl;

  if (iequals(test, test2)) {
    cout << "hash matches" << endl;      
  }

  // TEST AES-256 
  string plaintext = "this is a test message to see stuff";
  string passphrase = secure_hash("This is a test passphrase", "┌∩┐(◣_◢)┌∩┐", 1000);

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


  // SQLite3 INSERT TEST
  database db("auth.db");

  string username = "testUser";
  string password = "123456789";
  command cmd(db, "INSERT INTO users (username, password) VALUES (:username, :password)");
  cmd.bind(":username", username, nocopy);
  cmd.bind(":password", password, nocopy);
  cmd.execute();

  // SQLite3 SELECT TEST
  query qry(db, "SELECT password FROM users WHERE username = :user");
  qry.bind(":user", username, nocopy);
  for (auto v : qry) {
    string pw;
    v.getter() >> pw;
    cout << "\t" << pw << endl;
    
  }
  
   cout << "<h2>Hello World! This is my first CGI program</h2>\n";
   cout << "</body>\n";
   cout << "</html>\n";
  
  return 0;  
}
