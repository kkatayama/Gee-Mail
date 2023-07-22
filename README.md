# Gee-Mail
A secure asynchronous (same-machine) message platform<br />
All passwords are hashed (sha256) + salted + stretched<br />
All messages are encrypted with AES-256-CFB_MODE and passphrase is hashed + salted + stretched<br />
<br /><br />
Test users<br />
```javascript
username: andy
password: #Andy1#

username: teddy
password: #Teddy1#

username: alp
password: #Alp1#
```

Test user passphrases for emails from 3 users<br />
```javascript
andy  | novocin
teddy | secret
alp   | alparslan
kevin | kevinzh
```

# ubuntu (cloud 9)
> ### Install Libraries
> sudo apt-get install libcrypto++-dev libcrypto++-doc libcrypto++-utils<br >
> git clone https://github.com/kkatayama/Gee-Mail.git<br />

# osx
> ### Install Libraries
> brew install boost<br />
> NO LONGER WORKS: brew install cryptopp<br />
> wget https://github.com/weidai11/cryptopp/archive/refs/tags/CRYPTOPP_8_8_0.tar.gz
> tar xvf cryptopp-CRYPTOPP_8_8_0.tar.gz
> cd cryptopp-CRYPTOPP_8_8_0
> make -j 8
> sudo make install
> cd ..
> git clone https://github.com/kkatayama/Gee-Mail.git<br />

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
: 1
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Login Page                                        |
+-------------------------------------------------------------------------------+
username: teddy
password:
success...
```

```cpp
+--------------------------------------------------------------+
| GeeMail Messaging Platform: Main Menu                        |
+--------------------------------------------------------------+
| Welcome teddy, you have 1 messages                           |
+--------------------------------------------------------------+
+-------------------------------------------------------------------------------------------------------+
|    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |
+-------------------------------------------------------------------------------------------------------+
| andy         | Sat Jul 22 01:41:40 2023 |           -              | not read | Hi Teddy              |
+-------------------------------------------------------------------------------------------------------+

Would you like to read or write a message?
[1] Read Message
[2] Write Message
[3] Delete Message
[4] Logout
: 1
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Reading a message                                 |
+-------------------------------------------------------------------------------+
+--------------------------------------------------------------------------------------------------------------+
| [ID] |    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |
+--------------------------------------------------------------------------------------------------------------+
  [ 1] | andy         | Sat Jul 22 01:41:40 2023 |           -              | not read | Hi Teddy              |
+--------------------------------------------------------------------------------------------------------------+

Which message would you like to read?
ID: 1

Enter the passphrase for this message
:
   From: andy
     To: teddy
  Title: Hi Teddy
Message: Test message for Teddy from Andy!

Press Enter to return to main menu...
```

```cpp
+--------------------------------------------------------------+
| GeeMail Messaging Platform: Main Menu                        |
+--------------------------------------------------------------+
| Welcome teddy, you have 1 messages                           |
+--------------------------------------------------------------+
+-------------------------------------------------------------------------------------------------------+
|    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |
+-------------------------------------------------------------------------------------------------------+
| andy         | Sat Jul 22 01:41:40 2023 | Sat Jul 22 01:42:13 2023 | read     | Hi Teddy              |
+-------------------------------------------------------------------------------------------------------+

Would you like to read or write a message?
[1] Read Message
[2] Write Message
[3] Delete Message
[4] Logout
: 2
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Writing a message                                 |
+-------------------------------------------------------------------------------+
|     Sender: teddy
Enter Recepient: andy
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Writing a message                                 |
+-------------------------------------------------------------------------------+
|     Sender: teddy
|  Recepient: andy
Enter a title for your message: Hello Andy!
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Writing a message                                 |
+-------------------------------------------------------------------------------+
|     Sender: teddy
|  Recepient: andy
|      title: Hello Andy!
Enter your message: This is a test message for Andy from Teddy!
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Writing a message                                 |
+-------------------------------------------------------------------------------+
|     Sender: teddy
|  Recepient: andy
|      title: Hello Andy!
|    message: This is a test message for Andy from Teddy!
Enter a passphrase: secret
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Writing a message                                 |
+-------------------------------------------------------------------------------+
|     Sender: teddy
|  Recepient: andy
|      title: Hello Andy!
|    message: This is a test message for Andy from Teddy!
| passphrase: secret
|  timestamp: Sat Jul 22 01:42:46 2023
took: 0.975831
Message successfully written.
Please remember your passphrase.

Press Enter to return to main menu...
```

```cpp
+--------------------------------------------------------------+
| GeeMail Messaging Platform: Main Menu                        |
+--------------------------------------------------------------+
| Welcome teddy, you have 1 messages                           |
+--------------------------------------------------------------+
+-------------------------------------------------------------------------------------------------------+
|    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |
+-------------------------------------------------------------------------------------------------------+
| andy         | Sat Jul 22 01:41:40 2023 | Sat Jul 22 01:42:13 2023 | read     | Hi Teddy              |
+-------------------------------------------------------------------------------------------------------+

Would you like to read or write a message?
[1] Read Message
[2] Write Message
[3] Delete Message
[4] Logout
: 4
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
: 1
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Login Page                                        |
+-------------------------------------------------------------------------------+
username: andy
password:
success...
```

```cpp
+--------------------------------------------------------------+
| GeeMail Messaging Platform: Main Menu                        |
+--------------------------------------------------------------+
| Welcome andy, you have 1 messages                            |
+--------------------------------------------------------------+
+-------------------------------------------------------------------------------------------------------+
|    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |
+-------------------------------------------------------------------------------------------------------+
| teddy        | Sat Jul 22 01:42:46 2023 |           -              | not read | Hello Andy!           |
+-------------------------------------------------------------------------------------------------------+

Would you like to read or write a message?
[1] Read Message
[2] Write Message
[3] Delete Message
[4] Logout
: 1
```

```cpp
+-------------------------------------------------------------------------------+
| GeeMail Messaging Platform: Reading a message                                 |
+-------------------------------------------------------------------------------+
+--------------------------------------------------------------------------------------------------------------+
| [ID] |    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |
+--------------------------------------------------------------------------------------------------------------+
  [ 1] | teddy        | Sat Jul 22 01:42:46 2023 |           -              | not read | Hello Andy!           |
+--------------------------------------------------------------------------------------------------------------+

Which message would you like to read?
ID: 1

Enter the passphrase for this message
:
   From: teddy
     To: andy
  Title: Hello Andy!
Message: This is a test message for Andy from Teddy!

Press Enter to return to main menu...
```

```cpp
+--------------------------------------------------------------+
| GeeMail Messaging Platform: Main Menu                        |
+--------------------------------------------------------------+
| Welcome andy, you have 1 messages                            |
+--------------------------------------------------------------+
+-------------------------------------------------------------------------------------------------------+
|    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |
+-------------------------------------------------------------------------------------------------------+
| teddy        | Sat Jul 22 01:42:46 2023 | Sat Jul 22 01:49:27 2023 | read     | Hello Andy!           |
+-------------------------------------------------------------------------------------------------------+

Would you like to read or write a message?
[1] Read Message
[2] Write Message
[3] Delete Message
[4] Logout
: 4
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
: 3
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
> returns datetime as a string with newline character removed

```c++
int getChoice()
```
> returns int only if user inputs an integer

## Login and Registraion
```c++
bool check_password(string pass)
```
> returns true if password is strong<br />
> returns false if password is weak

```c++
int userRegister(string username, string password)
```
> returns 0: successfully registered<br />
> returns 1: username is taken<br />
> returns 2: password is too weak<br />

```c++
bool userLogin(string username, string pass)
```
> returns true if login successful<br />
> returns false if login failed

## Read, Write, and Delete Messages
```c++
int countMessages(string receiver)
```
> returns number of messages for a given user

```c++
bool checkPassphrase(string messageid, string passphrase)
```
> returns true if passphrase matches<br />
> returns false if bad passphrase

```c++
vector <string> getSenders(string receiver)
```
> returns string array of unique senders

```c++
vector <string> getMessages(string sender, string receiver)
```
> returns string array of all messages from a given sender<br />
> each string in the array is tab-delimeted <br />
> string format: writetime + "\t" + readtime +"\t" + messageid + "\t" + title<br />

```c++
string getMessage(string messageid);
```
> returns plaintext string of a message given its id 

```c++
writeMessage(string username, string receiver, string title, string message, string writetime, string readtime, string passphrase);
```
> saves a message into the database

```c++
deleteMessage(string messageid)
```
> deletes a message given its id

## Backend Functions
```c++
string secure_hash(string secret, string salt, int stretch);
```
> returns sha256 string

```c++
string* encrypt(string plaintext, string passphrase);
```
> returns AES-256 encrypted string array [iv, key, ciphertext]

```c++
string decrypt(string ciphertext, string key, string iv);
```
> returns plaintext string

```c++
database db("<DATABASE_NAME>");
```
> connects to sqlite3 database

```c++
command cmd(db, "INSERT INTO users (username, password) VALUES (:username, :password)");
cmd.bind(":username", username, nocopy);
cmd.bind(":password", password, nocopy);
cmd.execute();
```
> executes db query with bind parameters

```c++
query qry(db, "SELECT password FROM users WHERE username = :user");
qry.bind(":user", username, nocopy);
for (auto v : qry) {
  string pw;
  v.getter() >> pw;
  cout << "\t" << pw << endl;  
}
```
> get data from db query
