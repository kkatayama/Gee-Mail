#include <boost/algorithm/string.hpp>
// #include <sqlite3.h>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <thread>
#include <chrono>
#include "../cryptogm/sha256.h"
#include "../cryptogm/cryptogm.h"
#include "../sqlite3pp/sqlite3pp.h"

using namespace std;
using namespace boost;
using namespace sqlite3pp;

int countMessages(string receiver) {
  database db("gee-mail.db");
  int count = 0;
  
  query qry(db, "SELECT count(*) FROM messages WHERE receiver = :user");
  qry.bind(":user", receiver, nocopy);
  for (auto v : qry) {
    string tmp = "";
    v.getter() >> tmp;
    count = stoi(tmp);
  }

  return count;
}

vector <string> getSenders(string receiver) {
  database db("gee-mail.db");
  vector <string> senders;

  query qry(db, "SELECT DISTINCT sender FROM messages WHERE receiver = :user");
  qry.bind(":user", receiver, nocopy);
  for (auto v : qry) {
    string sender = "";
    v.getter() >> sender;
    senders.push_back(sender);
  }

  return senders;
}

vector <string> getMessages(string receiver) {
  database db("gee-mail.db");
  vector <string> senders;

  query qry(db, "SELECT title, writetime FROM messages WHERE receiver = :user");
  qry.bind(":user", receiver, nocopy);
  for (auto v : qry) {
    string sender = "";
    v.getter() >> sender;
    senders.push_back(sender);
  }

  return senders;
}


string getTime() {
  time_t currentTime = time(0);
  string datetime = asctime(localtime(&currentTime));
  datetime.erase(remove(datetime.begin(), datetime.end(), '\n'), datetime.end());

  return datetime;
}

void writeMessage(string username, string receiver, string title, string message, string writetime, string readtime, string passphrase) {
  database db("gee-mail.db");
  string *cipherdata = new string[3];
  string ciphertext;
  string key;
  string iv;

  passphrase = secure_hash(passphrase, "┌∩┐(◣_◢)┌∩┐", 1000);
  cipherdata = encrypt(message, passphrase);
  ciphertext = cipherdata[2];
  key = cipherdata[1];
  iv = cipherdata[0];

  command cmd(db, "INSERT INTO messages (sender, receiver, title, message, writetime, readtime, passphrase) VALUES (:send, :rcv, :ttl, :msg, :write, :read, :pass)");
  cmd.bind(":send", username, nocopy);
  cmd.bind(":rcv", receiver, nocopy);
  cmd.bind(":ttl", title, nocopy);
  cmd.bind(":msg", iv+ciphertext, nocopy);
  cmd.bind(":write", writetime, nocopy);
  cmd.bind(":read", readtime, nocopy);
  cmd.bind(":pass", passphrase, nocopy);
  cmd.execute();
}

bool check_password(string pass){
  vector <string> passwords;
  ifstream passfile;
  string pw;

  passfile.open("cryptogm/top_1000000.txt");
  while (getline (passfile, pw)) {
    passwords.push_back(pw);
  }
    
  if (find(passwords.begin(), passwords.end(), pass) != passwords.end()) {
    cout << "common password, please use a unique password" << endl;
    return false;
  }
  if (pass.length() < 6) {
    cout << "password too short" << endl;
    return false;
  }
  return true;
}

int getChoice(){
  int x = 0;

  while(!(cin >> x)){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout << "Invalid input.  Try again: ";    
  }

  return x; 
}

bool userLogin(string username, string pass) {
  int attempts;
  string tmp = "";
  database db("gee-mail.db");
  
  query qry(db, "SELECT username, password FROM users WHERE username = :user and password = :pass");
  qry.bind(":user", username, nocopy);
  qry.bind(":pass", pass, nocopy);

  // if there is no response, then password failed
  // increment number of attempts for that user if that user exists in database
  if (qry.begin() == qry.end()) {
    cout << "bad credentials" << endl;
    query qry(db, "SELECT attempts FROM users WHERE username = :user");
    qry.bind(":user", username, nocopy);
          
    for (auto v : qry) {
      tmp = "";
      v.getter() >> tmp;
      attempts = stoi(tmp);
      attempts++;
      command cmd(db, "UPDATE users SET attempts = :attempt WHERE username = :user");
      cmd.bind(":attempt", to_string(attempts), nocopy);
      cmd.bind(":user", username, nocopy);
      cmd.execute();
    }          
  }
  // username and password match, check to make sure account is not locked
  else {
    query qry(db, "SELECT attempts FROM users WHERE username = :user and password = :pass");
    qry.bind(":user", username, nocopy);
    qry.bind(":pass", pass, nocopy);

    for (auto v : qry) {
      tmp = "";
      v.getter() >> tmp;
      attempts = stoi(tmp);
      if (attempts < 3) {
        command cmd(db, "UPDATE users SET attempts = :attempt WHERE username = :user");
        cmd.bind(":attempt", "0", nocopy);
        cmd.bind(":user", username, nocopy);
        cmd.execute();
        cout << "success..." << endl;
        this_thread::sleep_for (std::chrono::seconds(1));
        return true;
      } else {
        cout << "UserName: " << username << " is locked" << endl;
        cout << "Please contact the system administrator to unlock the account" << endl;
      }
    }
  }
  this_thread::sleep_for (std::chrono::seconds(3));
  return false;
}

int userRegister(string username, string password) {
  // return 0: success
  // return 1: username exists
  // return 2: password too weak
  bool check;
  database db("gee-mail.db");
  
  query qry(db, "SELECT username FROM users WHERE username = :user");
  qry.bind(":user", username, nocopy);
  if (qry.begin() != qry.end()) {
    cout << "## username is taken ##" << endl;
    return 1;
  }
      

  check = check_password(password);
  if (check == false) 
    return 2;

  password = secure_hash(password, "┌∩┐(◣_◢)┌∩┐", 10000);
  command cmd(db, "INSERT INTO users (username, password, attempts) VALUES (:username, :password, :attempts)");
  cmd.bind(":username", username, nocopy);
  cmd.bind(":password", password, nocopy);
  cmd.bind(":attempts", "0", nocopy);
  cmd.execute();
      
  cout << "user created!"<< endl;
  this_thread::sleep_for (std::chrono::seconds(1));
  return 0;
}

