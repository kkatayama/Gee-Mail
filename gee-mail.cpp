#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "GraphicEngine/GraphicEngine.h"
#include "GeeMail/geemail.h"

using namespace std;
using namespace boost;

int main (int argc, char* argv[]) {
  bool running = true;
  
  // Login or Register
  GraphicEngine gfx;
  string username = "";
  string password = "";
  string choice = "";
  string pass = "";
  bool logged_in;
  bool check;
  int checkRegister;

  // Read or Write Messages
  string sender     = "";
  string receiver   = "";
  string title      = "";
  string message    = "";
  string passphrase = "";
  string timestamp  = "";
  string messageid  = "";
  string plaintext = "";
  string status = "";
  string tmp = "";
  int msgChoice;
  int i;
  int writeCount;
  int messageCount = 0;
  bool checkPP = false;
  bool select = false;
  vector <string> senders;
  vector <string> messages;
  vector <string> msgData;
  vector <string> temp;

  while(running) {
    /********************************/
    /* Login or Register a New User */
    /********************************/  
    while(!logged_in) {
      if (!choice.compare("1")) { // User chooses to LOGIN
        gfx.clearScreen();
        cout << "+-------------------------------------------------------------------------------+" << endl;
        cout << "| GeeMail Messaging Platform: Login Page                                        |" << endl;
        cout << "+-------------------------------------------------------------------------------+" << endl;

        cout << "username: ";
        getline(cin, username);
        password = getpass("password: ");

        logged_in = userLogin(username, password);
        choice = "";
      
      } else if (!choice.compare("2")) { // User chooses to REGISTER
        // Register
        gfx.clearScreen();
        cout << "+-------------------------------------------------------------------------------+" << endl;
        cout << "| GeeMail Messaging Platform: Registration Page                                 |" << endl;
        cout << "+-------------------------------------------------------------------------------+" << endl;

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
      
      } else if (!choice.compare("3")) {
        running = false;
        break;
      } else {
        gfx.printIntro(); // Display Program Info
        cout << "+-------------------------------------------------------------------------------+" << endl;
        cout << "| GeeMail Messaging Platform: Welcome Page                                      |" << endl;
        cout << "+-------------------------------------------------------------------------------+" << endl;
        cout << "Would you like to login or register a new user?" << endl;
        cout << "[1] Login" << endl;
        cout << "[2] Register" << endl;
        cout << "[3] Quit" << endl;
        cout << ": ";
        getline(cin, choice);
      }
    }

    /***************************/
    /* Read and Write Messages */
    /***************************/
    choice = "";
  
    while(logged_in) {
      if(!choice.compare("1")) { // User chooses to READ MESSAGE
        senders = getSenders(username);
        gfx.clearScreen();

        check = false;
        while (check == false) {
          cout << "+-------------------------------------------------------------------------------+" << endl;
          cout << "| GeeMail Messaging Platform: Reading a message                                 |" << endl;
          cout << "+-------------------------------------------------------------------------------+" << endl;

          messageCount = countMessages(username);
          senders = getSenders(username);
          receiver = username;
          cout << "+--------------------------------------------------------------------------------------------------------------+" << endl;
          cout << "| [ID] |    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |" << endl;
          cout << "+--------------------------------------------------------------------------------------------------------------+" << endl;
          
          // messages = getMessages(sender, receiver);
          messages = getAllMessages(receiver);
        
          for (i = 0; i < messages.size(); i++) {
            split(temp, messages[i], is_any_of("\t"));
            if (temp[3].compare("0")) {
              // tmp = "read " + temp[3];
              tmp = temp[3];
              status = "read";
            } else {
              // tmp = "not read";
              tmp = "          -";
              status = "not read";
            }
            cout << "  [" << right << setw(2) << i+1 << "] | " << left <<  setw(12) << temp[1] << " | " << setw(24) << temp[2] << " | "<< setw(24) << tmp << " | " << setw(8) << status << " | " << setw(22) << temp[4] << right << "|" << endl;
          }
          
          select = false;
          while (select == false) {
            cout << "+--------------------------------------------------------------------------------------------------------------+" << endl;
            cout << "\nWhich message would you like to read?" << endl;
            cout << "ID: ";
            msgChoice = getChoice();
            
            if ((msgChoice <= messages.size()) && (msgChoice > 0)) 
              select = true;
          }

          message = messages[msgChoice-1];
          split(msgData, message, is_any_of("\t"));
          timestamp = msgData[2];
          sender = msgData[1];
          messageid = msgData[0];
          title = msgData[4];
          cout << "\nEnter the passphrase for this message" << endl;
          cin.ignore();
          cin.clear();
          cin.sync();
          passphrase = getpass(": ");
          
          checkPP = checkPassphrase(messageid, passphrase);
          if(checkPP) {
            plaintext = getMessage(messageid);
            cout << "   From: " << sender << endl;
            cout << "     To: " << receiver << endl;
            cout << "  Title: " << title << endl;
            cout << "Message: " << plaintext << endl;
            cout << "\nPress Enter to return to main menu...\n";
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            choice = "";
            check = true;
          } else {
            cout << "bad passphrase..." << endl;
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            choice = "";
            check = true;            
          }          
          // } else {
          // gfx.clearScreen();
          // }
        }
            
      } else if (!choice.compare("2")) { // User chooses to WRITE MESSAGE
        writeCount = 0;

        for (i = 0; i < 5; i++) {
          gfx.clearScreen();
          cout << "+-------------------------------------------------------------------------------+" << endl;
          cout << "| GeeMail Messaging Platform: Writing a message                                 |" << endl;
          cout << "+-------------------------------------------------------------------------------+" << endl;
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
            checkPP = false;
            while(checkPP == false) {
              cout << "Enter a passphrase: ";
              getline(cin, passphrase);
              if (passphrase.length() < 6) {
                cout << "passphrase must be at least 5 characters" << endl;
              } else {
                checkPP = true;
              }
            }
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
      } else if (!choice.compare("3")) { // User choses to delete a message
        senders = getSenders(username);
        gfx.clearScreen();

        check = false;
        while (check == false) {
          cout << "+-------------------------------------------------------------------------------+" << endl;
          cout << "| GeeMail Messaging Platform: Deleting a message                                |" << endl;
          cout << "+-------------------------------------------------------------------------------+" << endl;
          cout << "+--------------------------------------------------------------------------------------------------------------+" << endl;
          cout << "| [ID] |    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |" << endl;
          cout << "+--------------------------------------------------------------------------------------------------------------+" << endl;
          
          // messages = getMessages(sender, receiver);
          messages = getAllMessages(receiver);
        
          for (i = 0; i < messages.size(); i++) {
            split(temp, messages[i], is_any_of("\t"));
            if (temp[3].compare("0")) {
              // tmp = "read " + temp[3];
              tmp = temp[3];
              status = "read";
            } else {
              // tmp = "not read";
              tmp = "          -";
              status = "not read";
            }
            cout << "  [" << right << setw(2) << i+1 << "] | " << left <<  setw(12) << temp[1] << " | " << setw(24) << temp[2] << " | "<< setw(24) << tmp << " | " << setw(8) << status << " | " << setw(22) << temp[4] << right << "|" << endl;
          }
          
          select = false;
          while (select == false) {
            cout << "+-------------------------------------------------------------------------------------------------------+" << endl;
            cout << "\nWhich message would you like to delete?" << endl;
            cout << ": ";
            msgChoice = getChoice();
            
            if ((msgChoice <= messages.size()) && (msgChoice > 0)) 
              select = true;
          }
          
          message = messages[msgChoice-1];
          split(msgData, message, is_any_of("\t"));
          timestamp = msgData[2];
          sender = msgData[1];
          messageid = msgData[0];
          title = msgData[4];

          cout << "\nEnter the passphrase for this message" << endl;
          cin.ignore();
          cin.clear();
          cin.sync();
          passphrase = getpass(": ");
          
          checkPP = checkPassphrase(messageid, passphrase);
          if(checkPP) {
            plaintext = getMessage(messageid);
            cout << "   From: " << sender << endl;
            cout << "     To: " << receiver << endl;
            cout << "  Title: " << title << endl;
            cout << "Message: " << plaintext << endl;
            deleteMessage(messageid);
            
            cout << "Press Enter to return to main menu...\n";
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
            choice = "";
            check = true;
          } else {
            cout << "bad passphrase..." << endl;
            cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
              choice = "";
              check = true;            
          }          
          //} else {
          //gfx.clearScreen();
          // }
        }

      } else if (!choice.compare("4")){  // User chooses to log out
        logged_in = false;
        choice = "";
      }else {
        gfx.clearScreen();
        messageCount = countMessages(username);
        senders = getSenders(username);
        receiver = username;
        cout << "+--------------------------------------------------------------+" << endl;
        cout << "| GeeMail Messaging Platform: Main Menu                        |" << endl;
        cout << "+--------------------------------------------------------------+" << endl;    
        cout << "| Welcome " << username << ", ";
        cout << "you have " << messageCount << left << " messages " << right << setw(27)<< "|" << endl;
        cout << "+--------------------------------------------------------------+" << endl;    
        cout << "+-------------------------------------------------------------------------------------------------------+" << endl;
        cout << "|    SENDER    |  MESSAGE SENT DATE TIME  |  MESSAGE READ DATE TIME  |  STATUS  |     SUBJECT TITLE     |" << endl;
        cout << "+-------------------------------------------------------------------------------------------------------+" << endl;
                
        // messages = getMessages(sender, receiver);
        messages = getAllMessages(receiver);
        
        for (i = 0; i < messages.size(); i++) {
          split(temp, messages[i], is_any_of("\t"));
          if (temp[3].compare("0")) {
            // tmp = "read " + temp[3];
            tmp = temp[3];
            status = "read";
          } else {
            // tmp = "not read";
            tmp = "          -";
            status = "not read";
          }
          cout << left << "| " <<  setw(12) << temp[1] << " | " << setw(24) << temp[2] << " | "<< setw(24) << tmp << " | " << setw(8) << status << " | " << setw(22) << temp[4] << right << "|" << endl;
        }
        cout << "+-------------------------------------------------------------------------------------------------------+" << endl;
        cout << "\nWould you like to read or write a message?" << endl;
        cout << "[1] Read Message" << endl;
        cout << "[2] Write Message" << endl;
        cout << "[3] Delete Message" << endl;
        cout << "[4] Logout" << endl;
        cout << ": ";
        getline(cin, choice);

        if (!senders.size() && !choice.compare("1")) {
          choice = "";
          cout << "\nYou don't have any messages to read..." << endl;
          cin.ignore(std::numeric_limits<streamsize>::max(),'\n');
        }
      }
    }
  }
  
  return 0;  
}
