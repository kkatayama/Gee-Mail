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
#include "GraphicEngine.h"
#include "cryptogm/sha256.h"
#include "cryptogm/cryptogm.h"
#include "sqlite3pp/sqlite3pp.h"

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
string getTime() {
  time_t currentTime = time(0);
  string datetime = asctime(localtime(&currentTime));
  datetime.erase(remove(datetime.begin(), datetime.end(), '\n'), datetime.end());

  return datetime;
}

void writeMessage(string username, string receiver, string message, string timestamp, string passphrase) {
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

  command cmd(db, "INSERT INTO messages (sender, receiver, message, timestamp, passphrase) VALUES (:send, :rcv, :msg, :time, :pass)");
  cmd.bind(":send", username, nocopy);
  cmd.bind(":rcv", receiver, nocopy);
  cmd.bind(":msg", iv+ciphertext, nocopy);
  cmd.bind(":time", timestamp, nocopy);
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

int main (int argc, char* argv[]) {
  database db("gee-mail.db");
  GraphicEngine gfx;
  string username = "";
  string password = "";
  string choice = "";
  string pass = "";
  string tmp = "";
  bool logged_in;
  bool check;
  int attempts;
  int count;

  /********************************/
  /* Login or Register a New User */
  /********************************/  
  logged_in = false;
  while(!logged_in) {
    if (!choice.compare("1")) { // User chooses to LOGIN
      gfx.clearScreen();
      cout << "Welcome to the Gee-Mail Login Page" << endl;

      count = 0;
      check = false;
      while(!check) {
        cout << "username: ";
        getline(cin, username);
        password = getpass("password: ");
        pass = secure_hash(password, "┌∩┐(◣_◢)┌∩┐", 10000);

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
          count++;
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
              cout << "Logged in..." << endl;
              logged_in = true;
              check = true;
            } else {
              cout << "UserName: " << username << " is locked" << endl;
              cout << "Please contact the system administrator to unlock the account" << endl;
            }
          }
        }
        if (count > 2) {
          check = true;
          choice = "";
        }
      }
      
    } else if (!choice.compare("2")) { // User chooses to REGISTER
      // Register
      gfx.clearScreen();
      cout << "Welcome to the Gee-Mail Registration Form" << endl;
      
      check = false;
      while (check == false) {
        cout << "Enter a username: ";
        getline(cin, username);
        
        query qry(db, "SELECT username FROM users WHERE username = :user");
        qry.bind(":user", username, nocopy);
        if (qry.begin() == qry.end()) {
          check = true;
        } else {
          cout << "## username is taken ##" << endl; 
        }
      }
      
      check = false;
      while (check == false) {
        //cout << "Enter a password: ";
        //cin >> password;
        password = getpass("Enter a password: ");
        check = check_password(password);
        choice = "";
      }
      password = secure_hash(password, "┌∩┐(◣_◢)┌∩┐", 10000);
      command cmd(db, "INSERT INTO users (username, password, attempts) VALUES (:username, :password, :attempts)");
      cmd.bind(":username", username, nocopy);
      cmd.bind(":password", password, nocopy);
      cmd.bind(":attempts", "0", nocopy);
      cmd.execute();
      
      cout << "user created!"<< endl;
      
    } else {
      gfx.printIntro(); // Display Program Info
      cout << "Would you like to login or register a new user?" << endl;
      cout << "[1] Login" << endl;
      cout << "[2] Register" << endl;
      cout << ": ";
      getline(cin, choice);

    }
  }

  /***************************/
  /* Read and Write Messages */
  /***************************/
  choice = "";
  string receiver   = "";
  string message    = "";
  string passphrase = "";
  string timestamp  = "";
  int i;
  int writeCount;
  int messageCount = 0;
  vector <string> senders;
  
  while(logged_in) {
    if(!choice.compare("1")) { // User chooses to READ MESSAGE
      
    } else if (!choice.compare("2")) { // User chooses to WRITE MESSAGE
      writeCount = 0;

      for (i = 0; i < 4; i++) {
        gfx.clearScreen();
        cout << "+-----------------------------------------------+" << endl;
        cout << "| GeeMail Messaging Platform: Writing a message |" << endl;
        cout << "+-----------------------------------------------+" << endl;
        cout << "|     Sender: " << username << endl;
        if (i == 0) {
          cout << "Enter Recepient: ";
          getline(cin, receiver);
        } else if (i == 1) {
          cout << "|  Recepient: "<< receiver << endl;
          cout << "Enter your message: ";
          getline(cin, message);
        } else if (i == 2){
          cout << "|  Recepient: "<< receiver << endl;
          cout << "|    message: "<< message << endl;
          cout << "Enter a passphrase: ";
          getline(cin, passphrase);
        } else {
          timestamp = getTime();
          cout << "|  Recepient: " << receiver << endl;
          cout << "|    message: " << message << endl;
          cout << "| passphrase: " << passphrase << endl;
          cout << "|  timestamp: " << timestamp << endl;

          writeMessage(username, receiver, message, timestamp, passphrase);
          cout << "\nMessage successfully written." << endl;
          cout << "Please remember your passphrase." << endl;
          cout << "\nPress Enter to return to main menu...\n";
          cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
          choice = "";
        }
      }      
    } else {
      gfx.clearScreen();
      messageCount = countMessages(username);
      senders = getSenders(username);
    
      cout << "Welcome " << username << endl;
      cout << "You have " << messageCount << " messages from the following users" << endl;
      cout << "-----------------------" << endl;
      for (int i = 0; i < senders.size(); i++) {
        cout << "[" << (i+1) << "] " << senders[i] << endl;
      }    
      cout << "-----------------------" << endl;
      cout << "\nWould you like to read or write a message?" << endl;
      cout << "[1] Read Message" << endl;
      cout << "[2] Write Message" << endl;
      cout << ": ";
      getline(cin, choice);
    }
  }
  
  /*
  string *cipherdata = new string[3];
  string recovered;

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
  */
  
  return 0;  
}
