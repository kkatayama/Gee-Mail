# Gee-Mail
A secure asynchronous (same-machine) message platform<br />
All passwords are hashed (sha256) + salted + stretched<br />
All messages are encrypted with AES-256-CFB_MODE and passphrase is hashed + salted + stretched<br />
<br /><br />
Test user<br />
```javascript
username: andy
password: #novo#ninja#
```

Test user passphrases for emails from 3 users<br />
```javascript
teddy | secret
alp   | alparslan
kevin | kevinzh
```


# ubuntu (cloud 9)
>###Install Libraries
>sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils<br >
>git clone https://github.com/kkatayama/Gee-Mail.git<br />

# osx
>###Install Libraries
>brew install boost<br />
>brew install cryptopp<br />
>git clone https://github.com/kkatayama/Gee-Mail.git<br />

# compile and run
```cpp
$ make

$ ./gee-mail

```

```cpp
*********************************************************************************
* CPEG-676 Secure Systems: Project 4: Gee-Mail                                  *
*********************************** Authors *************************************
* Alparslan Sari                                                                *
* Kaoru (Teddy) Katayama                                                        *
* Pengcheng (Kevin) Zhou                                                        *
*********************************************************************************
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Welcome Page                                      |
+-------------------------------------------------------------------------------+
Would you like to login or register a new user?
[1] Login
[2] Register
[3] Quit
```

# GeeMail API

## Sqlite Database Tables
```bash
users: |username|password|attempts|
messages: |messageid|sender|receiver|title|message|writetime|readtime|passphrase|
```

## Helper Functions
```c++
string getTime()
```
>returns datetime as a string with newline character removed

```c++
int getChoice()
```
>returns int only if user inputs an integer

## Login and Registraion
```c++
bool check_password(string pass)
```
>returns true if password is strong<br />
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
>returns true if login successful<br />
>returns false if login failed

## Read, Write, and Delete Messages
```c++
int countMessages(string receiver)
```
>returns number of messages for a given user

```c++
bool checkPassphrase(string messageid, string passphrase)
```
>returns true if passphrase matches<br />
>returns false if bad passphrase

```c++
vector <string> getSenders(string receiver)
```
>returns string array of unique senders

```c++
vector <string> getMessages(string sender, string receiver)
```
>returns string array of all messages from a given sender<br />
>each string in the array is tab-delimeted <br />
> string format: writetime + "\t" + readtime +"\t" + messageid + "\t" + title<br />

```c++
string getMessage(string messageid);
```
>returns plaintext string of a message given its id 

```c++
writeMessage(string username, string receiver, string title, string message, string writetime, string readtime, string passphrase);
```
>saves a message into the database

```c++
deleteMessage(string messageid)
```
>deletes a message given its id

## Backend Functions
```c++
string secure_hash(string secret, string salt, int stretch);
```
>returns sha256 string

```c++
string* encrypt(string plaintext, string passphrase);
```
>returns AES-256 encrypted string array [iv, key, ciphertext]

```c++
string decrypt(string ciphertext, string key, string iv);
```
>returns plaintext string

```c++
database db("<DATABASE_NAME>");
```
>connects to sqlite3 database

```c++
command cmd(db, "INSERT INTO users (username, password) VALUES (:username, :password)");
cmd.bind(":username", username, nocopy);
cmd.bind(":password", password, nocopy);
cmd.execute();
```
>executes db query with bind parameters

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
