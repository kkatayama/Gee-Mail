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
#include "GraphicEngine/GraphicEngine.h"
#include "GeeMail/geemail.h"
#include "cryptogm/sha256.h"
#include "cryptogm/cryptogm.h"
#include "sqlite3pp/sqlite3pp.h"

using namespace std;
using namespace boost;
using namespace sqlite3pp;

int main (int argc, char* argv[]) {
  GraphicEngine gfx;
  string username = "";
  string password = "";
  string choice = "";
  string pass = "";
  bool logged_in;
  bool check;
  int checkRegister;

  /********************************/
  /* Login or Register a New User */
  /********************************/  
  logged_in = false;
  while(!logged_in) {
    if (!choice.compare("1")) { // User chooses to LOGIN
      gfx.clearScreen();
      cout << "Welcome to the Gee-Mail Login Page" << endl;

      cout << "username: ";
      getline(cin, username);
      password = getpass("password: ");

      logged_in = userLogin(username, password);
      choice = "";
      
    } else if (!choice.compare("2")) { // User chooses to REGISTER
      // Register
      gfx.clearScreen();
      cout << "Welcome to the Gee-Mail Registration Form" << endl;

      checkRegister = 1;
      while (checkRegister) {
        if (checkRegister < 2) {
          cout << "Enter a username: ";
          getline(cin, username);
        }
        password = getpass("Enter a password: ");
        checkRegister = userRegister(username, password);
      }
      choice = "";
      
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
  string sender     = "";
  string receiver   = "";
  string title      = "";
  string message    = "";
  string passphrase = "";
  string timestamp  = "";
  string messageid  = "";
  string plaintext = "";
  int senderChoice;
  int msgChoice;
  int i;
  int writeCount;
  int messageCount = 0;
  bool checkPP = false;
  vector <string> senders;
  vector <string> messages;
  vector <string> msgData;
  
  while(logged_in) {
    if(!choice.compare("1")) { // User chooses to READ MESSAGE
      senders = getSenders(username);
      gfx.clearScreen();

      check = false;
      while (check == false) {
        cout << "+-----------------------------------------------+" << endl;
        cout << "| GeeMail Messaging Platform: Reading a message |" << endl;
        cout << "+-----------------------------------------------+" << endl;
        for (i = 0; i < senders.size(); i++) {
          cout << " [" << i+1 << "] " << senders[i] << endl;
        }      
        cout << "+-----------------------------------------------+" << endl;
        cout << "Which user would you like to read a message from?" << endl;
        cout << ": ";
        // getline(cin, senderChoice);
        senderChoice = getChoice();

        if ((senderChoice <= senders.size()) && (senderChoice > 0)) {
          sender = senders[senderChoice-1];
          receiver = username;
          cout << "+-----------------------------------------------+" << endl;
          cout << " Messages from: " << sender << endl;
          cout << "+-----------------------------------------------+" << endl;
          messages = getMessages(sender, receiver);
          for (i = 0; i < messages.size(); i++) {
            cout << " [" << i+1 << "] " << messages[i] << endl;
          }
          cout << "+-----------------------------------------------+" << endl;
          cout << "Which message would you like to read?" << endl;
          cout << ": ";
          msgChoice = getChoice();

          if ((msgChoice <= messages.size()) && (msgChoice > 0)) {
            message = messages[msgChoice-1];
            boost::split(msgData, message, boost::is_any_of("\t"));
            timestamp = msgData[0];
            messageid = msgData[1];
            title = msgData[2];
            cout << "Enter the passphrase for this message" << endl;
            //passphrase = getpass("passphrase: ");
            cin.ignore();
            cin.clear();
            cin.sync();
            getline(cin, passphrase);

            checkPP = checkPassphrase(messageid, passphrase);
            if(checkPP) {
              plaintext = getMessage(messageid);
              cout << plaintext << endl;
              
            } else {
              cout << "bad passphrase..." << endl;
            }
          }
        } else {
          gfx.clearScreen();
        }
      }
      
      
    } else if (!choice.compare("2")) { // User chooses to WRITE MESSAGE
      writeCount = 0;

      for (i = 0; i < 5; i++) {
        gfx.clearScreen();
        cout << "+-----------------------------------------------+" << endl;
        cout << "| GeeMail Messaging Platform: Writing a message |" << endl;
        cout << "+-----------------------------------------------+" << endl;
        cout << "|     Sender: " << username << endl;
        if (i == 0) {
          cout << "Enter Recepient: ";
          getline(cin, receiver);
        } else if (i == 1) {
          cout << "|  Recepient: " << receiver << endl;
          cout << "Enter a title for your message: ";
          getline(cin, title);
        } else if (i == 2) {
          cout << "|  Recepient: " << receiver << endl;
          cout << "|      title: " << title << endl;
          cout << "Enter your message: ";
          getline(cin, message);
        } else if (i == 3){
          cout << "|  Recepient: " << receiver << endl;
          cout << "|      title: " << title << endl;
          cout << "|    message: " << message << endl;
          cout << "Enter a passphrase: ";
          getline(cin, passphrase);
        } else {
          timestamp = getTime();
          cout << "|  Recepient: " << receiver << endl;
          cout << "|      title: " << title << endl;
          cout << "|    message: " << message << endl;
          cout << "| passphrase: " << passphrase << endl;
          cout << "|  timestamp: " << timestamp << endl;

          writeMessage(username, receiver, title, message, timestamp, "0", passphrase);
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
        cout << "  " << senders[i] << endl;
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
