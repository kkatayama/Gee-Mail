# Gee-Mail
A secure asynchronous (same-machine) message platform


#ubuntu (cloud 9)
>###Install Libraries
>sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils

>###Compile
>g++ -std=c++11 -I/usr/include/cryptopp \*.cpp cryptogm/\*.cpp -lcryptopp -lsqlite3 -o gee-mail

#osx
>###Install Libraries
>brew install boost

>brew install cryptopp

>###Complie
>g++ -std=c++11 -I/usr/local/include/cryptopp \*.cpp cryptogm/\*.cpp -lcryptopp -lsqlite3 -o gee-mail

#docs
>https://github.com/iwongu/sqlite3pp<br />
>https://cryptopp.com/wiki/Advanced_Encryption_Standard

#useful functions
```c++
string secure_hash(string secret, string salt, int stretch);
```
>returns sha256 string

<br />
```c++
string* encrypt(string plaintext, string passphrase);
```
>returns AES-256 encrypted string array [iv, key, ciphertext]

<br />
```c++
string decrypt(string ciphertext, string key, string iv);
```
>returns plaintext string

<br />
```c++
database db("<DATABASE_NAME>");
```
>connects to sqlite3 database

<br />
```c++
command cmd(db, "INSERT INTO users (username, password) VALUES (:username, :password)");
cmd.bind(":username", username, nocopy);
cmd.bind(":password", password, nocopy);
cmd.execute();
```
>executes db query with bind parameters

<br />
```c++
query qry(db, "SELECT password FROM users WHERE username = :user");
qry.bind(":user", username, nocopy);
for (auto v : qry) {
  string pw;
  v.getter() >> pw;
  cout << "\t" << pw << endl;  
}
```
>get data from db query
