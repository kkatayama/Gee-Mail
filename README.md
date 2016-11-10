# Gee-Mail
A secure asynchronous (same-machine) message platform


#ubuntu (cloud 9)
>###Install Libraries
>sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils<br >

>###Compile
>g++ -std=c++11 -I/usr/include/cryptopp \*.cpp cryptogm/\*.cpp GeeMail/\*.cpp GraphicEngine/\*.cpp -lcryptopp -lsqlite3 -o gee-mail

#osx
>###Install Libraries
>brew install boost

>brew install cryptopp

>###Complie
>g++ -std=c++11 -I/usr/local/include/cryptopp \*.cpp cryptogm/\*.cpp GeeMail/\*.cpp GraphicEngine/\*.cpp -lcryptopp -lsqlite3 -o gee-mail

#docs
>https://github.com/iwongu/sqlite3pp<br />
>https://cryptopp.com/wiki/Advanced_Encryption_Standard

#GeeMail API

##Helper Functions
```c++
string getTime()
```
>returns datetime as a string with newline character removed

```c++
int getChoice()
```
>returns int only if user inputs an integer

<br />
##Login and Registraion
```c++
bool check_password(string pass)
```
>returns true if password is strong
>returns false if password is weak

```c++
int userRegister(string username, string password)
```
>returns 0: successfully registered<br />
>returns 1: username is taken<br />
>returns 2: password is too weak<br />

```c++
bool userLogin(string username, string pass)
```
>returns true if login successful
>returns false if login failed

<br />
##Read, Write, and Delete Messages
```c++
int countMessages(string receiver)
```
>returns number of messages for a given user

```c++
bool checkPassphrase(string messageid, string passphrase)
```
>returns true if passphrase matches
>returns false if bad passphrase

```c++
vector <string> getSenders(string receiver)
```
>returns string array of unique senders

```c++
vector <string> getMessages(string sender, string receiver)
```
>returns string array of all messages from a given sender

```c++
string getMessage(string messageid);
```
>returns string of a message given its id

```c++
writeMessage(string username, string receiver, string title, string message, string writetime, string readtime, string passphrase);
```
>saves a message into the database

```c++
deleteMessage(string messageid)
```
>deletes a message given its id

<br />
##Backend Functions
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
